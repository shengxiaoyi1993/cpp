#include "bs_cxx_driver_export.h"
#include "bs_cxx_driver.h"
#include "mongocxx/exception/bulk_write_exception.hpp"
#include "../../lib/cjsonobject/CJsonObject.hpp"
#include <thread>
#include <mutex>

static std::mutex _bson_cxx_obj_id_mutex;

char *NewObjectId() {
    _bson_cxx_obj_id_mutex.lock();
    bsoncxx::oid oid;
    _bson_cxx_obj_id_mutex.unlock();

    char *id_str = static_cast<char *>(malloc(25));
    memset(id_str, 0, 25);

    std::string oid_hex = oid.to_string();

    strcpy(id_str, oid_hex.data());
    return id_str;
}

char *Str2Char(std::string &str) {
    char *data = static_cast<char *>(malloc(str.length() + 1));
    memset(data,0,str.length() + 1);
    strcpy(data, str.data());
    return data;

}

char *Obj2Char(neb::CJsonObject &obj) {
    std::string result_str = obj.ToFormattedString();
    return Str2Char(result_str);
}

char *EmptyObjectJson() {
    char *data = static_cast<char *>(malloc(3));
    strcpy(data,"{}");
    return data;
}

char *EmptyArrayJson(){
    char *data = static_cast<char *>(malloc(3));
    strcpy(data,"[]");
    return data;
}

namespace mongo {
    static mongocxx::instance instance{};
    static mongocxx::pool *pool = nullptr ;//= mongocxx::pool{mongocxx::uri{}};
    static pthread_mutex_t mutex;
    const int kLimit = 20;
         mongocxx::client conn = mongocxx::get_client();

    const std::string kDatabaseName = "uvss_database";
}


void mongo::Init() {
    pthread_mutex_lock(&mutex);
    if(pool == nullptr) {
        pool = new mongocxx::pool(mongocxx::uri{});
    }
    pthread_mutex_unlock(&mutex);
}

void mongo::Cleanup() {
    pthread_mutex_lock(&mutex);
    delete pool;
    pool = nullptr;
    pthread_mutex_unlock(&mutex);
}



//func Add(in *C.char, table *C.char) *C.char

/**
 * @brief ParseDataId2Oid  获取id，转换成json对象
 * @param in
 * @param _id
 * @param parse_new_id
 * @return
 */
neb::CJsonObject ParseDataId2Oid(char *in, std::string &_id, bool parse_new_id) {
    std::string in_str = "{}";
    if(in != nullptr) {
        in_str = in;
    }

    neb::CJsonObject obj(in_str);
    _id = "";

    char *_id_char = nullptr;
    neb::CJsonObject obj_id;

    if(obj.IsEmpty()) {
        obj = neb::CJsonObject("{}");
    }

    obj.Get("_id", _id);

    if(_id == "") {
        if(parse_new_id) {
            _id_char = NewObjectId();
            _id = _id_char;
            free(_id_char);

            obj_id.Add("$oid", _id);
            obj.Delete("_id");
            obj.Add("_id", obj_id);
        }
    } else {
        obj_id.Add("$oid", _id);
        obj.Delete("_id");
        obj.Add("_id", obj_id);
    }

    return obj;
}

/**
 * @brief Add 在table_name col中添加doc in
 * @param in
 * @param table_name
 * @return
 */
char *Add(char *in, char *table_name) {
    if(mongo::pool == nullptr || in == nullptr) {
        std::cout << "null pool" << std::endl;
        return nullptr;
    }

    std::string new_id = "";
    neb::CJsonObject obj = ParseDataId2Oid(in, new_id, true);

    std::string doc_result = obj.ToString();

    auto client = mongo::pool->acquire();
    mongocxx::collection collection = (*client)[mongo::kDatabaseName][std::string(table_name)];


    bsoncxx::document::value v = bsoncxx::from_json(doc_result);
    bsoncxx::document::view_or_value view_or_value(v);
    std::cout << "Add one data" << std::endl;
    try {
        collection.insert_one(view_or_value);
    } catch (
      mongocxx::bulk_write_exception e) {
      std::cout << "Fail to insert: " << e.what() << std::endl;
      return nullptr;
    }

    std::cout << "Insert status:" << new_id << std::endl;

    return Str2Char(new_id);
}

neb::CJsonObject Find(char *cond, int skip, int limit, char *table_name) {
    if(mongo::pool == nullptr) {
        return neb::CJsonObject("[]");
    }

    std::string _id;
    neb::CJsonObject cond_obj = ParseDataId2Oid(cond, _id, false);
    std::string cond_str = cond_obj.ToString();

    bsoncxx::document::value cond_value = bsoncxx::from_json(cond_str);
    bsoncxx::document::view_or_value cond_view_or_value(cond_value);

    auto client = mongo::pool->acquire();
    mongocxx::collection collection = (*client)[mongo::kDatabaseName][std::string(table_name)];

    mongocxx::options::find options;
    options.skip(skip);
    options.limit(limit);
    bsoncxx::document::view_or_value sort = bsoncxx::from_json("{\"_id\":-1}");
    options.sort(sort);

    mongocxx::cursor cursor = collection.find(cond_view_or_value, options);

    std::string tmp_str;
    neb::CJsonObject result;
    neb::CJsonObject tmp_result;
    std::string oid_string;

    for(auto doc : cursor) {
        oid_string = doc["_id"].get_oid().value.to_string();
        tmp_str = bsoncxx::to_json(doc);
        tmp_result = neb::CJsonObject(tmp_str);

        tmp_result.Replace("_id", oid_string);
        result.Add(tmp_result);

    }

    return result;

}

//func FindOne(cond *C.char, table *C.char) *C.char {

char *FindOne(char *cond, char *table_name) {

    if(mongo::pool == nullptr) {
        return nullptr;
    }

    std::string _id;
    neb::CJsonObject cond_obj = ParseDataId2Oid(cond, _id, false);
    std::string cond_str = cond_obj.ToString();

    bsoncxx::document::value cond_value = bsoncxx::from_json(cond_str);
    bsoncxx::document::view_or_value cond_view_or_value(cond_value);

    auto client = mongo::pool->acquire();
    mongocxx::collection collection = (*client)[mongo::kDatabaseName][std::string(table_name)];

    mongocxx::options::find options;
    options.skip(0);
    options.limit(1);
    bsoncxx::document::view_or_value sort = bsoncxx::from_json("{\"_id\":-1}");
    options.sort(sort);


    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result = collection.find_one(cond_view_or_value, options);

    if(!maybe_result) {
        return nullptr;
    }

    std::string tmp_str = bsoncxx::to_json(*maybe_result);
    neb::CJsonObject tmp_result(tmp_str);
    std::string oid_string = maybe_result.value().view()["_id"].get_oid().value.to_string();

    tmp_result.Replace("_id", oid_string);

    return Obj2Char(tmp_result);
}

neb::CJsonObject Id2CondObj(char *_id) {
    neb::CJsonObject id_obj;
    std::string id_string = _id;
    if(id_string == "") {
        _id = NewObjectId();
        id_string = _id;
        free(_id);
    }

    id_obj.Add("$oid", id_string);
    neb::CJsonObject cond_obj;
    cond_obj.Add("_id", id_obj);
    return cond_obj;
}

char *FindOneById(char *_id, char *table_name) {
    if(_id == nullptr) {
        return nullptr;
    }
    neb::CJsonObject cond_obj = Id2CondObj(_id);

    char *cond_str = Obj2Char(cond_obj);

    char *result = FindOne(cond_str, table_name);

    free(cond_str);

    return result;
}

char *FindMany(char *cond, int skip, int limit, char *table_name) {
    neb::CJsonObject result = Find(cond, skip, limit, table_name);
    return Obj2Char(result);
}

char *FindAll(char *table_name) {
    int limit = 20;
    int skip = 0;
    int count = limit;
    neb::CJsonObject result;

    while(count == limit) {
        neb::CJsonObject tmp = Find(nullptr,skip, limit, table_name);
        count = tmp.GetArraySize();
        skip += count;
        for(int i = 0;i < count; i++) {
            result.Add(tmp[static_cast<unsigned int>(i)]);
        }
    }

    return Obj2Char(result);
}

bool DeleteById(char *_id, char *table_name) {

    if(mongo::pool == nullptr) {
        return false;
    }

    neb::CJsonObject cond_obj = Id2CondObj(_id);
    bsoncxx::document::view_or_value cond_view_or_value = bsoncxx::from_json(cond_obj.ToString());

    auto client = mongo::pool->acquire();
    mongocxx::collection collection = (*client)[mongo::kDatabaseName][std::string(table_name)];


    bsoncxx::stdx::optional<mongocxx::result::delete_result> result = collection.delete_one(cond_view_or_value);
    if(result) {
        return true;
    }

    return false;
}

bool UpdateById(char *_id, char* new_data, char* table_name) {
    if(mongo::pool == nullptr) {
        return false;
    }

    neb::CJsonObject cond_obj = Id2CondObj(_id);
    bsoncxx::document::view_or_value cond_view_or_value = bsoncxx::from_json(cond_obj.ToString());

    auto client = mongo::pool->acquire();
    mongocxx::collection collection = (*client)[mongo::kDatabaseName][std::string(table_name)];

    std::string id_str = "";
    neb::CJsonObject new_data_obj = ParseDataId2Oid(new_data, id_str, false);
    new_data_obj.Delete("_id");
    neb::CJsonObject new_data_with_set;

    new_data_with_set.Add("$set", new_data_obj);
    std::string new_data_str = new_data_with_set.ToString();

    bsoncxx::document::view_or_value new_data_view_or_value = bsoncxx::from_json(new_data_str);

    bsoncxx::stdx::optional<mongocxx::result::update> result = collection.update_one(cond_view_or_value, new_data_view_or_value);

    if(result) {
        return true;
    }

    return false;
}

int Count(char *cond, char* table_name) {

    if(mongo::pool == nullptr) {
        return 0;
    }

    std::string _id;
    neb::CJsonObject cond_obj = ParseDataId2Oid(cond, _id, false);
    std::string cond_str = cond_obj.ToString();

    bsoncxx::document::value cond_value = bsoncxx::from_json(cond_str);
    bsoncxx::document::view_or_value cond_view_or_value(cond_value);

    auto client = mongo::pool->acquire();
    mongocxx::collection collection = (*client)[mongo::kDatabaseName][std::string(table_name)];


    std::int64_t number = collection.count_documents(cond_view_or_value);

    return static_cast<int>(number);
}
