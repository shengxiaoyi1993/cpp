cp ../../../build/build_lib/bin/lib/libencrypt.so .
export LD_LIBRARY_PATH=/home/sxy/Github/cpp/encrypt/build/build_lib/bin/lib:$LD_LIBRARY_PATH
./encrypt_test
