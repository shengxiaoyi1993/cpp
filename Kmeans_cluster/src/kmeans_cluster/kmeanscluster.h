#ifndef KMEANSCLUSTER_H
#define KMEANSCLUSTER_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>
#include "../../lib_copy/syslogger/syslogger.h"


using namespace std;
using namespace std::rel_ops;

namespace alg {


inline
uint getRandom(uint v_low,uint v_high){
  static int mnum=0;
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv,&tz);
  srand(tv.tv_sec*1000000 +tv.tv_usec+mnum);
  uint interval=v_high-v_low;
  uint num=random()%interval+v_low;
  mnum++;
  return num;
}

//template<typename T>
//inline T getrandomNum(const T &v_low,const T &v_high){
//  static int mnum=0;
//  struct timeval tv;
//  struct timezone tz;
//  gettimeofday(&tv,&tz);
//  srand(tv.tv_sec*1000000 +tv.tv_usec+mnum);
//  T interval=v_high-v_low;
//  T num=random()%interval+v_low;
//  mnum++;
//  return num;

//}


class PointEg{
private:
  vector<double> _list;
  string _name;

public:
  PointEg(int v_n){
    _list.resize(v_n);
    for(uint i=0;i<v_n;i++){
      _list[i]=0;
    }
  }
  PointEg(){

  }
  PointEg(const PointEg& v_p){
    _name=v_p._name;
    _list.resize(v_p._list.size());
    copy(v_p._list.begin(),v_p._list.end(),_list.begin());
  }

  PointEg(double* v_list,int v_num ){
    _list.resize(v_num);
    for(uint i=0;i<v_num;i++){
      _list[i]=v_list[i];
    }
  }
  template<typename T>
  PointEg(T* v_list,int v_num,const string v_name="" ){
    _name=v_name;
    _list.resize(v_num);
    for(uint i=0;i<v_num;i++){
      _list[i]=static_cast<double>(v_list[i]);
    }
  }

  string getName() const{
    return _name;
  }



  static double distance(const PointEg& v_p0,const PointEg& v_p1){
    double dis=0;
    for(uint i=0;i<v_p0._list.size();i++){
      dis+=(v_p0._list[i]-v_p1._list[i])*(v_p0._list[i]-v_p1._list[i]);
    }
    dis=pow(dis,2.0);
    return dis;
  }
  double at(uint v_num){
    return _list[v_num];
  }

  const PointEg operator+ (const PointEg& v_p0 ){
    PointEg sum(v_p0._list.size());
    for(uint i=0;i<_list.size();i++){
      sum._list[i]=(_list[i]+v_p0._list[i]);
    }
    return sum;
  }

  const PointEg operator/ (int v_div ){
    if(v_div == 0){
      throw string(__PRETTY_FUNCTION__)+"Error: v_div can not be 0!";
    }
    PointEg sum(_list.size());
    for(uint i=0;i<_list.size();i++){
      sum._list[i]=(_list[i]/v_div);
    }
    return sum;
  }

  bool  operator< (const PointEg& v_p0 ) const{
    PointEg sum(_list.size());
    for(uint i=0;i<_list.size();i++){
      if(_list[i]<v_p0._list[i]){
        return true;
      }
    }
    return false;
  }

  bool  operator== (const PointEg& v_p0 ) const{
    for(uint i=0;i<_list.size();i++){
      if(_list[i]!=v_p0._list[i]){
        return false;
      }
    }
    return true;
  }


  friend ostream & operator<<( ostream & os,const PointEg & v_p){
    for(uint i=0;i<v_p._list.size();i++){
      os<<v_p._list[i]<<" ";
    }
    return os;
  }

};


template <class T>
class Cluster{
private:
  vector<T> _list_point;
  T _cluster_center;
  bool _ready;

public:
  Cluster(const T &v_point){
    _ready=false;
    _cluster_center=v_point;
  }
  Cluster(){
    _ready=false;

  }

  ~Cluster(){

  }

  void updateClusterCenter(){
    T sum;
    for(uint i=0;i<_list_point.size();i++){
      sum=sum+_list_point[i];
    }
    _cluster_center=sum/_list_point.size();
    _ready=true;
  }

  void addPoint(const T& v_point){
    _list_point.push_back(v_point);
    _ready=false;
  }

  T getCentraPoint() const{
    return _cluster_center;
  }

  vector<T> getPoints() const{
    return _list_point;
  }


  friend ostream & operator<<( ostream & os,const Cluster & v_clu){
    os<<"center:"<<v_clu._cluster_center<<endl;
    os<<"list:"<<endl;
    for(uint i=0;i<v_clu._list_point.size();i++){
      os<<"["<<i<<"]:"<<v_clu._list_point[i]<<endl;
    }
    return os;
  }

  void clearList(){
    _list_point.clear();
    _ready=false;
  }

};


//typedef
//template <typename T>
//void(TRANSPORT)(Cluster<T> );

template <typename T>
class KmeansCluster
{

public:
  typedef void (*PFN_CALLBACK_OUTPUT_CLUSTERA)(const vector<Cluster<T> > &_list_cluster);

  KmeansCluster(int v_K,int v_max_iterations ,const vector<T> & v_list_point):
    _k(v_K),_max_interations(v_max_iterations),p_outputClusters(nullptr)
  {

    LOG_INFO("%s initialize ...",__FUNCTION__);
    _points.resize(v_list_point.size());
    copy(v_list_point.begin(),v_list_point.end(),_points.begin());
  }

  ~KmeansCluster(){
    LOG_INFO("%s end ...",__FUNCTION__);

  }

  //获取初始聚类中心值
  //进入循环，直至聚类中心稳定或者计算次数超出最大迭代次数
  //  将数据逐个添加到聚类中心
  //  重新计算每个聚类的聚类中心
  void run(){
    LOG_INFO("%s start ...",__FUNCTION__);

    vector<T> centrapoints=predictCentraPointsByPP(_points);
    LOG_INFO("%s predictCentraPointsByPP finish",__FUNCTION__);


    _list_cluster.reserve(_k);
    for(int i=0;i<_k;i++){
      _list_cluster.push_back(Cluster<T>(centrapoints[i]));
    }
    LOG_INFO("%s set CentraPoints for clusters finish",__FUNCTION__);


    int num_iterations=0;
    bool done=false;
    while (done==false && num_iterations<_max_interations) {
      num_iterations++;
      done=true;

      for(int i=0;i<_k;i++){
        _list_cluster[i].clearList();
      }

      //add points to clusters
      //for every point
      for(uint i=0;i<_points.size();i++){
        int seq_cluster_min=0;
        double distance_cluster_min=0;
        for(uint j=0;j<_list_cluster.size();j++){
          double  dis_tmp=T::distance(_points[i],_list_cluster[j].getCentraPoint());
          if(distance_cluster_min>dis_tmp||j==0){
            distance_cluster_min = dis_tmp;
            seq_cluster_min=j;
          }
        }
        _list_cluster[seq_cluster_min].addPoint(_points[i]);
      }

      //update and check
      for(uint i=0;i<_list_cluster.size();i++){
        T centrpoint_tmp=_list_cluster[i].getCentraPoint();
        _list_cluster[i].updateClusterCenter();
        if(centrpoint_tmp != _list_cluster[i].getCentraPoint()){
          done=false;
          break;
        }
      }
      //      cout<<"num_iterations:"<<num_iterations<<endl;

      if(p_outputClusters != nullptr){
        p_outputClusters(_list_cluster);
      }

      LOG_INFO("%s clusters iteratortion num %d",__FUNCTION__,num_iterations);
    }
    LOG_INFO("%s clusters iteratortion finish",__FUNCTION__);


    LOG_INFO("%s end ...",__FUNCTION__);

  }

  void appendData(const vector<T> &v_list_point){

  }

  int tryToClusters(const T& v_point) const{
    int seq_cluster_min=0;
    double distance_cluster_min=0;
    for(uint j=0;j<_list_cluster.size();j++){
      T point_tmp=_list_cluster[j].getCentraPoint();
      double  dis_tmp=T::distance(v_point,point_tmp);
      if(distance_cluster_min>dis_tmp||j==0){
        distance_cluster_min = dis_tmp;
        seq_cluster_min=j;
      }
    }
    return seq_cluster_min;
  }

  vector<T> getCentraPoints(){
    vector<T> list(_list_cluster.size());
    for(uint i=0;i<_list_cluster.size();i++){
      list[i]=_list_cluster[i].getCentraPoint();
    }
    return list;
  }

  vector<Cluster<T> > getClusters(){
    vector<Cluster<T> > list(_list_cluster.size());
    copy(_list_cluster.begin(),_list_cluster.end(),list.begin());
    return list;
  }


  //kmeans ++
  vector<T> predictCentraPointsByPP(const vector<T>& v_points){
    if(_k>v_points.size()){
      throw string(__PRETTY_FUNCTION__)+"Error:no enough point";
    }
    //随机选择一点
    //进入循环，直至所有点都被选出
    //  计算每个点到每个已选出点的距离，保存最端距离，选择最短距离最长的点作为下一个聚类中心
    vector<T> points_centra;
    int index_point = rand() % v_points.size();
    points_centra.push_back(v_points[index_point]);

    for(uint m=0;m<_k;m++){
      double dis_max=0;
      int index_max=0;
      for(uint i=0;i<v_points.size();i++){
        double dis_min=0;
        int index_min=0;
        for(uint j=0;j<points_centra.size();j++){
          double dis_tmp= T::distance(points_centra[j],v_points[i]);
          if((j==0)||(dis_min>dis_tmp)){
            dis_min=dis_tmp;
            index_min=j;
          }
        }
        if(i==0||(dis_min>dis_max)){
          dis_max=dis_min;
          index_max=i;
        }
      }
      points_centra.push_back(v_points[index_max]);
    }

    return points_centra;
  }

  //随机生成K个数，截取在数据点数范围内的点
  //

  vector<T> predictCentraPointsByRandom(vector<T> v_points){
    //    cout<<"v_points:"<<v_points.size()<<endl;

    vector<T> points;
    vector<int> nums;

    for(int i = 0; i < _k; i++)
    {
      while(true)
      {
        int index_point = rand() % v_points.size();

        if(find(nums.begin(), nums.end(),
                index_point) == nums.end())
        {
          nums.push_back(i);
          break;
        }
      }
    }

    points.reserve(_k);
    for(int i = 0; i < _k; i++){
      points.push_back(v_points[i]);
    }

    return points;
  }

  void setOutputClustersFunc( PFN_CALLBACK_OUTPUT_CLUSTERA v_cv){
    p_outputClusters=v_cv;
  }


private:
  vector<Cluster<T> > _list_cluster;
  vector<T>      _points;
  int _k;
  int _max_interations;
  bool _ready;
  //用于输出每次迭代的结果
  PFN_CALLBACK_OUTPUT_CLUSTERA p_outputClusters;

};


}






#endif // KMEANSCLUSTER_H
