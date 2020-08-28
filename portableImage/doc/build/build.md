# build


## init env
```
cd image_converter
bash -e init.sh
```
- Note:for the consistence,It is not suggested to modify the code in `lib` directly.It is suggested to modify in basic project and then copy to main project by running the script

## compile

```shell
cd build
mkdir build
cd build
cmake ../
make
```
