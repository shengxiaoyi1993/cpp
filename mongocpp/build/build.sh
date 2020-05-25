cd ../mongodb_driver/
make linux -j1
cd ../
wget ftp://pub:9900@192.168.1.238/software/src/mongodb/centos.zip
mkdir MongoDB_Bin -p
unzip -o -d MongoDB_Bin/ centos.zip
chmod +x -R MongoDB_Bin/linux/*
rm centos.zip 
#启动mongo服务器
#运行项目
