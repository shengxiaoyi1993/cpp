

/*  @file updatedelete.cpp
@brief 本代码演示了如何访问 mongodb 并更新和删除文档

1. 本代码应该在 insertquery 项目运行之后运行，否则会运行出错
2. 演示了单文档更新和多文档更新方法，并输出对应结果
3. 演示了单文档删除和多文档删除方法，并输出对应结果
4. 演示了创建索引并输出对应结果
*/


//#include <cstdint>
//#include <iostream>
//#include <vector>
//#include <bsoncxx/json.hpp>
//#include <mongocxx/client.hpp>
//#include <mongocxx/stdx.hpp>
//#include <mongocxx/uri.hpp>
//// 官方文档中缺少以下语句
//#include <bsoncxx/builder/stream/document.hpp>
//#include <mongocxx/instance.hpp>

//using bsoncxx::builder::stream::close_array;
//using bsoncxx::builder::stream::close_document;
//using bsoncxx::builder::stream::document;
//using bsoncxx::builder::stream::finalize;
//using bsoncxx::builder::stream::open_array;
//using bsoncxx::builder::stream::open_document;

//int main(int, char**)
//{
//    mongocxx::instance instance{};      // This should be done only once.
//                                        // mongocxx::client client{ mongocxx::uri{} };
//                                        // 上面代码等同于:
//    mongocxx::uri uri("mongodb://localhost:27017");
//    mongocxx::client client(uri);

//    mongocxx::database db = client["mydb"];     // 访问数据库
//    mongocxx::collection coll = db["test"];     // 访问集合

//    // 最多更新一个文档
//    mongocxx::stdx::optional<mongocxx::result::update> updateOneRes = coll.update_one(document{} << "i" << 10 << finalize,
//        document{} << "$set" << open_document <<
//        "i" << 110 << close_document << finalize);
//    if (updateOneRes)
//    {
//        auto matchedCount = updateOneRes->matched_count();
//        auto modifiedCount = updateOneRes->modified_count();
//        std::cout << "update_one() method result:\n" <<
//            "matched count: " << matchedCount << ",modified count: " << modifiedCount << std::endl;
//        mongocxx::stdx::optional<bsoncxx::document::element> upId = updateOneRes->upserted_id();
//        if (upId)
//        {
//            auto idStr = upId->get_oid().value.to_string();
//            std::cout << "upserted id: " << idStr << std::endl;
//        }
//        else
//            std::cout << "no document has been inserted." << std::endl;
//    }

//    // 更新多个文档
//    mongocxx::stdx::optional<mongocxx::result::update> updateManyRes = coll.update_many(document{} << "i" << open_document <<
//        "$lt" << 100 << close_document << finalize,
//        document{} << "$inc" << open_document <<
//        "i" << 100 << close_document << finalize);
//    if (updateManyRes)
//    {
//        std::cout <<"update_many() method result:\nmodified count:" << updateManyRes->modified_count() << std::endl;
//    }

//    // 删除单个文档
//    mongocxx::stdx::optional<mongocxx::result::delete_result> delOneRes = coll.delete_one(document{} << "i" << 110 << finalize);
//    if (delOneRes)
//    {
//        std::cout << "delete_one() method result: " << delOneRes->deleted_count() << " document has been deleted." << std::endl;
//    }
//    // 删除多个文档
//    mongocxx::stdx::optional<mongocxx::result::delete_result> delManyRes = coll.delete_many(
//        document{} << "i" << open_document << "$gte" << 150 << close_document << finalize);
//    if (delManyRes)
//    {
//        std::cout << "delete_many() method result: " << delManyRes->deleted_count() << " documents has been deleted." << std::endl;
//    }

//    // 按照 i 字段升序的方式建立索引
//    auto index_specification = document{} << "i" << 1 << finalize;
//    bsoncxx::document::value  val = coll.create_index(std::move(index_specification));
//    std::cout << "create index result:" << std::endl;
//    std::cout << bsoncxx::to_json(val.view()) << std::endl;

//    system("pause");
//    return 0;
//}





//#include <chrono>
//#include <bsoncxx/builder/basic/array.hpp>
//#include <bsoncxx/builder/basic/document.hpp>
//#include <bsoncxx/builder/basic/kvp.hpp>
//#include <bsoncxx/types.hpp>
//#include <mongocxx/client.hpp>
//#include <mongocxx/instance.hpp>
//#include <mongocxx/uri.hpp>
//#include<time.h>
//#include<string>
//#include<iostream>

//using bsoncxx::builder::basic::kvp;
//using bsoncxx::builder::basic::make_array;
//using bsoncxx::builder::basic::make_document;

//int main(int, char**) {

//    mongocxx::instance inst{};
//    mongocxx::client conn{mongocxx::uri{}};

//    auto db = conn["test"];

//    // We choose to move in our document here, which transfers ownership to insert_one()
//    clock_t startTime = clock();
//    for(int i = 0; i <= 1000; ++i)
//    {
//        bsoncxx::document::value restaurant_doc = make_document(
//                    kvp("address",
//                        make_document(kvp("street", "2 Avenue"),
//                                      kvp("zipcode", 10075),
//                                      kvp("building", "1480"),
//                                      kvp("coord", make_array(-73.9557413, 40.7720266)))),
//                    kvp("borough", "Manhattan"),
//                    kvp("cuisine", "Italian"),
//                    kvp("grades",
//                        make_array(
//                            make_document(kvp("date", bsoncxx::types::b_date{std::chrono::milliseconds{12323}}),
//                                          kvp("grade", "A"),
//                                          kvp("score", 11)),
//                            make_document(
//                                kvp("date", bsoncxx::types::b_date{std::chrono::milliseconds{121212}}),
//                                kvp("grade", "B"),
//                                kvp("score", 17)))),
//                    kvp("name", "Vella"),
//                    kvp("restaurant_id", std::to_string(i)));
//        auto res = db["restaurants"].insert_one(std::move(restaurant_doc));
//    }

//    clock_t endTime = clock();
//    std::cout << " insert total time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << std::endl;
//    // @end: cpp-insert-a-document
//}










#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
// 官方文档中缺少以下语句
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

int main (){
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
    mongocxx::database db = client["mydb"];
    mongocxx::collection coll = db["test"];
    auto builder = bsoncxx::builder::stream::document{};

    bsoncxx::document::value doc_value = builder
      << "name" << "MongoDB"
      << "type" << "database"
      << "count" << 1
      << "versions" << bsoncxx::builder::stream::open_array
        << "v3.2" << "v3.0" << "v2.6"
      << close_array
      << "info" << bsoncxx::builder::stream::open_document
        << "x" << 203
        << "y" << 102
      << bsoncxx::builder::stream::close_document
      << bsoncxx::builder::stream::finalize;
    bsoncxx::document::view view = doc_value.view();

    bsoncxx::document::element element = view["name"];
    if(element.type() != bsoncxx::type::k_utf8) {
      // Error
    }
    auto res = coll.insert_one(std::move(doc_value));


    mongocxx::cursor cursor = coll.find({});
    for(auto doc : cursor) {
      std::cout << bsoncxx::to_json(doc) << "\n";
    }

}



