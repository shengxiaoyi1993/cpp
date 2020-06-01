#include <iostream>
#include <mysql/mysql.h>

using namespace std;

int main(int argc,char *argv[])
{
    MYSQL conn;
    int res;
    mysql_init(&conn);
    //222555yq为数据库的进入密码，yg_sql为数据库名
    if(mysql_real_connect(&conn,"localhost","root","123456","mysql",0,NULL,CLIENT_FOUND_ROWS))
    {
         cout << "connect success!" << endl;
         //将数据库yg_user_images表中字段id为1所对应字段score的数据修改为100
         // res=mysql_query(&conn,"update yg_user_images set score = '100' where id = '1'");
         //判断是否读取成功
         // if(res)
         //     cout << "error" << endl;
         // else
         //     cout << "OK" << endl
         std::cout << "mysql test" << '\n';
         mysql_close(&conn);
    }
    return 0;
}
