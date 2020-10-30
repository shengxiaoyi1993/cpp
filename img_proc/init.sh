#! /bin/bash
# Author: sxy                                  // 指定作者
# Date：2020-8-21                               // 指定日期
# Version：0.0.0                               // 指定版本
# Description： init project of image_converter ,copy basic lib to lib // 描述脚本的功能
# usage: bash -e init.sh

echo "//=======================INIT  START=========================//"

LIB_COPY="lib"
LIB_COPY_COMMON=${LIB_COPY}/common
LIB_COPY_PNM=${LIB_COPY}/pnm
LIB_COPY_RAW=${LIB_COPY}/raw
LIB_COPY_JPEG=${LIB_COPY}/jpeg
LIB_COPY_IMAGECONVERTER=${LIB_COPY}/imageconverter


# rm ${LIB_COPY} -rf
mkdir ${LIB_COPY} -p


mkdir ${LIB_COPY_COMMON} -p
cp ../common/src/cpp/string_manipulation.* ${LIB_COPY_COMMON}
echo "[succeed]:copy ${LIB_COPY_COMMON}"

mkdir ${LIB_COPY_PNM} -p
cp ../portableImage/src/pnm/pnm.* ${LIB_COPY_PNM}
echo "[succeed]:copy ${LIB_COPY_PNM}"


mkdir ${LIB_COPY_RAW} -p
cp ../rawImage/src/raw/raw.* ${LIB_COPY_RAW}
cp ../rawImage/src/raw/bayer_convert.* ${LIB_COPY_RAW}
echo "[succeed]:copy ${LIB_COPY_RAW}"

mkdir ${LIB_COPY_JPEG} -p
cp ../jpeg/lib/jpeg-compressor/jpgd.* ${LIB_COPY_JPEG}
cp ../jpeg/lib/jpeg-compressor/jpge.* ${LIB_COPY_JPEG}
echo "[succeed]:copy ${LIB_COPY_JPEG}"

mkdir ${LIB_COPY_IMAGECONVERTER} -p
cp ../image_converter/src/ImageConverter.* ${LIB_COPY_IMAGECONVERTER}
echo "[succeed]:copy ${LIB_COPY_IMAGECONVERTER}"


echo "[tree]   :"
tree ${LIB_COPY}

echo "//=======================INIT  END=========================//"
