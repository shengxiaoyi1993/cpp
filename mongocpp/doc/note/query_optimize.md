
# query_optimize
## source_link

https://docs.mongodb.com/v4.0/core/query-plans/

## translate

### plan cash
- 搜索会根据搜索策略进行
- 最优的搜索策略将会保留
- 发起搜索请求后，先检查现有策略是否匹配，优先使用现有的，否则从备选中寻找最优项

- 一些目录操作如删除索引或集合会导致刷新
- 数据库重启后搜索策略会丢失

- 可以使用索引过滤器来选择需要的索引

## optimization
- 建立索引
-
