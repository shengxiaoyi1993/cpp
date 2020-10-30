#! /bin/bash
# Author: sxy                                  // 指定作者
# Date：2020-8-31                               // 指定日期
# Version：0.0.0                               // 指定版本
# Description： init project of portableimage ,copy basic lib to lib // 描述脚本的功能
# usage: bash -e init.sh

echo "//=======================INIT  START=========================//"

LIB_COPY="lib_copy"
LIB_COPY_licenseGenerator=${LIB_COPY}"/licenseGenerator"
LIB_COPY_kmeans_cluster=${LIB_COPY}"/kmeans_cluster"


rm ${LIB_COPY} -rf
mkdir ${LIB_COPY}

mkdir ${LIB_COPY_kmeans_cluster}
cp ../../Kmeans_cluster/src/kmeans_cluster/kmeanscluster.* ${LIB_COPY_kmeans_cluster}
echo "[succeed]:copy ${LIB_COPY_kmeans_cluster}"

mkdir ${LIB_COPY_licenseGenerator}
cp ../../licenseGenerator/src/licenseGenerator/licensegenerator.* ${LIB_COPY_licenseGenerator}
echo "[succeed]:copy ${LIB_COPY_licenseGenerator}"



echo "[tree]   :"
tree ${LIB_COPY}

echo "//=======================INIT  END=========================//"
