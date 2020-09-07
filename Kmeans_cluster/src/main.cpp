#include<iostream>
//#include "kmeans_cluster/kmeans.h"
#include "kmeans_cluster/kmeanscluster.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <random>
#include <ctime>


// 编写符合要求的类
// 生成数据
// 调用类进行计算 初始化，运行输出
void test_KmeansCluster();

//输出各个群
int getClustersDisplay( cv::Mat& v_mat,
                        const vector<alg::Cluster<alg::PointEg> > v_clusters,
                        const vector<cv::Scalar> &v_colors
                        );

//Scalar
vector<cv::Scalar> getColorList(int v_num){
  vector<cv::Scalar> list_module={cv::Scalar(255,102,102),
                                  cv::Scalar(255,255,0),
                                  cv::Scalar(0,102,153),
                                  cv::Scalar(255,153,102),
                                  cv::Scalar(51,153,51),
                                  cv::Scalar(255,104,51),
                                  cv::Scalar(153,204,51),
                                  cv::Scalar(255,255,255),
                                  cv::Scalar(153,204,204),
                                  cv::Scalar(255,0,51),
                                  cv::Scalar(255,102,102),

                                 };
  if(list_module.size()<v_num){
    throw string(__PRETTY_FUNCTION__)+"Error:no enough color!";
  }

  vector<cv::Scalar> list(v_num);
  copy(list_module.begin(),list_module.begin()+v_num,list.begin());
  return list;

}



int main() {

  test_KmeansCluster();
  return 0;

}

void printClusters(const vector<alg::Cluster<alg::PointEg> > &_list_cluster){
  //  for(uint i=0;i<_list_cluster.size();i++){
  //    cout<<"i:"<<i<<endl;
  //    cout<<_list_cluster[i]<<endl;
  //  }

  int size =1000;
  int v_k=10;
  cv::Mat mat_ret(size,size,CV_8UC3,cv::Scalar(255,255,255));
  vector<cv::Scalar> v_colors=getColorList(v_k);
  getClustersDisplay(mat_ret,_list_cluster,v_colors);
  cv::imshow("result",mat_ret);
  cv::waitKey(1);

}


//分类器基本调试
//1. 基本功能测试
//  - 输入参数，测试运行过程，
//  - 输出结果是否大体上符合预期
//2. 算法测试：分类效果是否达到预期
//   1. 输出点阵分布，点阵分布中标出聚群中心
//   2. 迭代的效果更新图（使用opencv实现）

void test_KmeansCluster(){
  try {
    int d=2;
    int v_k=10;
    int size=1000;
    vector<alg::PointEg> list;
    for (int i=0;i<1000;i++) {
      double *nums_tmp=new double[d];
      for(int j=0;j<d;j++){
        nums_tmp[j]=alg::getRandom(0,999);
      }
      //      cout<<alg::PointEg(nums_tmp,d)<<endl;
      list.push_back(alg::PointEg(nums_tmp,d));
      delete [] nums_tmp;
    }

    alg::KmeansCluster<alg::PointEg> classfier(v_k,9999,list);
    classfier.setOutputClustersFunc(printClusters);
    classfier.run();

    vector<alg::PointEg> list_centrapoint= classfier.getCentraPoints();

    cv::Mat mat_ret(size,size,CV_8UC3,cv::Scalar(255,255,255));
    cout<<"cols"<<mat_ret.cols<<endl;
    cout<<"rows"<<mat_ret.rows<<endl;


    vector<cv::Scalar> v_colors=getColorList(v_k);
    cout<<"getColorList"<<endl;
    for(uint  i=0;i<v_colors.size();i++){
      cout<<i<<":"<<v_colors[i]<<endl;
    }


    getClustersDisplay(mat_ret,classfier.getClusters(),v_colors);
    cout<<"getClustersDisplay"<<endl;
    cv::imwrite("ret.bmp",mat_ret);

    //    cv::resize(mat_ret,mat_ret,cv::Size(1024,1024));
    //    cv::imshow("result",mat_ret);
    //    cv::waitKey();



    //    cout<<"list_centrapoint:"<<list_centrapoint.size()<<endl;
    //    for(uint i=0;i<list_centrapoint.size();i++){
    //      cout<<"["<<"i]:"<<list_centrapoint[i]<<endl;
    //    }

    //    cout<<"list_clusters:"<<endl;
    //    vector<alg::Cluster<alg::PointEg> > list_clusters=classfier.getClusters();
    //    for(uint i=0;i<list_clusters.size();i++){
    //      cout<<"i:"<<list_clusters[i]<<endl;
    //    }


  } catch (string msg) {
    cout<<"msg:"<<msg<<endl;
  }

}

//假设输出数据均能落在图片尺寸内
//  - 对于非整数，四舍5入成为整数


int getClustersDisplay( cv::Mat& v_mat,
                        const vector<alg::Cluster<alg::PointEg> > v_clusters,
                        const vector<cv::Scalar> &v_colors
                        ){
  //  v_colors[0].;

  for(uint i=0;i<v_clusters.size();i++){
    vector<alg::PointEg> points_tmp= v_clusters[i].getPoints();
    for (uint j=0;j<points_tmp.size();j++) {
      //      cout<<"i:"<<i<<" j:"<<j<<endl;
      //      cout<<points_tmp[j]<<endl;

      v_mat.at<cv::Vec3b>(points_tmp[j].at(0),points_tmp[j].at(1))=
          cv::Vec3b(v_colors[i][0],v_colors[i][1],v_colors[i][2]);

    }
  }
  return 0;

}
