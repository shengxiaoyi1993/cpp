# readme 

```shell
 1002  make
 1003  ls
 1004  ./main
 1005  gcov main.c
 1006  gcov test.c
 1007  ls
#  1008  genhtml -o result main_test.info
 1009  sudo yum install lcov.noarch 
 1010  genhtml -o result main_test.info
 1011  lcov 
 1012  lcov -d . -t 'Main Test' -o 'main_test.info' -b . -c
 1013  ls
 1014  genhtml -o result main_test.info
 1015  ls
 1016  cd result/
 1017  ls
 1018  firefox index.html 
 
 ```