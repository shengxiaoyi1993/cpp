# build


## init env
- `image_converter` is main project.there is some basic project is provided as well:`portableImage`,`rawImage`,`outputFile`,`JPEG`,`common`.
- run the `init.sh` in project `image_converter` to copy the lib from basic project to main project
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
