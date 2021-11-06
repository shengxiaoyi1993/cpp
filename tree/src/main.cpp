    #include <cstdio>
    #include <ext/pb_ds/tree_policy.hpp>
    #include <ext/pb_ds/assoc_container.hpp>
    using namespace std;
    using namespace __gnu_pbds;

//null_node_update


    tree<double, null_type, greater<double>, rb_tree_tag, tree_order_statistics_node_update> T;
    int main()
    {
    	//freopen("3369.in", "r", stdin);
    	//freopen("3369.out", "w", stdout);
    	int q, opt, x;
    	scanf("%d", &q);
    	for (int i = 1; i <= q; ++ i)
    	{
    		scanf("%d%d", &opt, &x);
    		if(opt == 1)
    			T.insert(x + i * 1e-6);
    		//插入一个数
    		if(opt == 2)
    			T.erase(T.lower_bound(x));
    		//删除一个数
    		if(opt == 3)
    			printf("%d\n", (int)T.order_of_key(x) + 1);
    		//查询一个数的排名
    		if(opt == 4)
    			printf("%d\n", (int)*T.find_by_order(x - 1));
    		//查询第k小的数 返回的是一个迭代器 这里k是从0开始算的，意思是最小的数是第0小的
    		if(opt == 5)
    			printf("%d\n", (int)round(*(-- T.lower_bound(x))));
    		//查询一个数的前驱
    		if(opt == 6)
    			printf("%d\n", (int)round(*T.lower_bound(x + 1)));
    		//查询一个数的后继
    	}
    	return 0;
    }
