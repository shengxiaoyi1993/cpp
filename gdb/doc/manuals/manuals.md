# manuals

## cmake setting

```
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
```

## before run exe
```
ulimit  -c unlimited
```

## build & run
```
cd build
mkdir build
cd build
cmake ../
make
./example
```
