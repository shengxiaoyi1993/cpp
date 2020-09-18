#ifndef BS_CXX_DRIVER_EXPORT_H
#define BS_CXX_DRIVER_EXPORT_H

//内建一个数据库
//可创建不同名的集合
//集合中可插入、删除、搜索、更新等操作




/**
 * @brief NewObjectId  create new id, which is unique
 * @return            :id of new obj
 */
char *NewObjectId();
/**
 * @brief Add         :在集合中插入一条文档
 * @param in          :content in doc
 * @param table_name  :name of collection
 * @return return     :dataid
 */
char *Add(char *in, char *table_name);
/**
 * @brief FindOne     :find one doc
 * @param cond        :conditions
 * @param table_name  :name of collection
 * @return            :centent of one doc, if many entries match this condition,
 *                     most newly doc will be returned
 * @note              :any condition will return a doc,it's strange
 */
char *FindOne(char *cond, char *table_name);

/**
 * @brief FindOneById :as func
 * @param _id         :
 * @param table_name  :name of condition
 * @return            :centent of one doc
 * @note              :if _id don't match, will throw error
 */
char *FindOneById(char *_id, char *table_name);

/**
 * @brief FindMany    :as func ,start with most newly data
 * @param cond
 * @param skip        :skip some most newly docs
 * @param limit       :total quentity of return list,if match docs is lower, real list will be shorter
 * @param table_name
 * @return
 */
char *FindMany(char *cond, int skip, int limit, char *table_name);
/**
 * @brief FindAll     :return all data in collection
 * @param table_name
 * @return
 */
char *FindAll(char *table_name);
/**
 * @brief DeleteById  as func
 * @param _id
 * @param table_name
 * @return
 */
bool DeleteById(char *_id, char *table_name);
/**
 * @brief UpdateById  :update doc of id
 * @param _id
 * @param new_data    :content
 * @param table_name
 * @return
 * @note              :if doc contain entry has same key with new_data, change the value
 *                     if not ,add new_data in old doc
 */
bool UpdateById(char *_id, char *new_data, char *table_name);
/**
 * @brief Count       :count quentity of doc in coll
 * @param cond
 * @param table_name
 * @return
 */
int Count(char *cond, char *table_name);

namespace mongo {
    void Init();
    void Cleanup();
}

#endif // BS_CXX_DRIVER_EXPORT_H
