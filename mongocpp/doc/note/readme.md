# README
## test_result
```
| total | times | quentity | cost |
| 10000 | 1 | 1000 | 7527942 |
| 10000 | 1 | 1000 | 7410727 |
| 10000 | 1 | 1000 | 7528044 |

| 100000 | 1 | 1000 | 77926172 |
| 100000 | 1 | 1000 | 80863424 |
| 100000 | 1 | 1000 | 78811535 |

| 500000 | 1 | 1000 | 406222675 |
| 500000 | 1 | 1000 | 404461564 |
| 500000 | 1 | 1000 | 410168738 |

| 1000000 | 1 | 1000 | 820261802 |

```

## 性能调优

### 原始数据
```
| total | times | quentity | cost |
| 5000000 | 1 | 10 | 61672761 |
| 5000000 | 1 | 10 | 53834142 |
| 5000000 | 1 | 10 | 55456255 |

```
### 创建索引后
```
> db.tb_5m.createIndex({"condi":1})
{
	"createdCollectionAutomatically" : false,
	"numIndexesBefore" : 1,
	"numIndexesAfter" : 2,
	"ok" : 1
}

```
```
| total | times | quentity | cost |
| 5000000 | 1 | 10 | 18912 |
| 5000000 | 1 | 10 | 4492 |
| 5000000 | 1 | 10 | 5451 |
```

- 删除索引后重新搜索

```
> db.tb_5m.getIndexes()
[
	{
		"v" : 2,
		"key" : {
			"_id" : 1
		},
		"name" : "_id_",
		"ns" : "uvss_database.tb_5m"
	},
	{
		"v" : 2,
		"key" : {
			"condi" : 1
		},
		"name" : "condi_1",
		"ns" : "uvss_database.tb_5m"
	}
]
> db.tb_5m.dropIndex("condi_1")
{ "nIndexesWas" : 2, "ok" : 1 }
> db.tb_5m.getIndexes()
[
	{
		"v" : 2,
		"key" : {
			"_id" : 1
		},
		"name" : "_id_",
		"ns" : "uvss_database.tb_5m"
	}
]
>

```

```
| total | times | quentity | cost |
| 5000000 | 1 | 10 | 47988952 |
| 5000000 | 1 | 10 | 54189369 |
| 5000000 | 1 | 10 | 54374804 |
```
- 接着再次查询
```
| total | times | quentity | cost |
| 5000000 | 1 | 10 | 50965335 |
| 5000000 | 1 | 10 | 54606802 |
| 5000000 | 1 | 10 | 55279202 |
```
### 创建

- 将数据置于内存
- 创建索引
- 合理的结构
