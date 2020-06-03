# note

## 文件目录

```
.
├── benchmark  
├── build
├── CMakeLists.txt
├── CONTRIBUTING.md     //说明向这个项目贡献代码时，代码所希望遵循的规范
├── CREDITS.json        //记录贡献
├── data    
├── examples
├── LICENSE
├── README.md
├── src
└── THIRD-PARTY-NOTICES  //第三方库的说明
```

- 需要先运行mongod

```
 //下载相应系统和版本的mongo
 sudo mkdir /usr/local/mongodb/data -p
 sudo touch /usr/local/mongodb/logs
 sudo ./mongod --dbpath=/usr/local/mongodb/data --logpath=/usr/local/mongodb/logs  --port=27017

mkdir /home/sxy/mongodb/data -p
touch /home/sxy/mongodb/logs
sudo ./mongod --dbpath=/home/sxy/mongodb/data --logpath=/home/sxy/mongodb/logs  --port=27017


```
