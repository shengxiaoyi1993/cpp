#include <iostream>
#include<sys/time.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "uvss_label_distance_interface.hpp"
#include "../../../../opencv_cpp/learn/imagesort/src/record.h"
#include "../lib_copy/licenseGenerator/licensegenerator.h"
#include "mysql.h"
#include "../lib_copy/kmeans_cluster/kmeanscluster.h"

using namespace std;

long getTime(struct timeval v_t){
  return (v_t.tv_sec*1000000+v_t.tv_usec);
}

void addData();
void queryData();
void searchDataTest();
void searchSimilarImage(float* v_label,char* v_image,char& v_small);
void modifyDataEntries();
/**
 * @brief getDataFromDataBase 从数据库中获取样本数据
 * @param v_size              样本数量
 * @param flag_dif            是否要求取不重复的数据
 * @return
 */
vector<alg::PointEg> getDataFromDataBase(int v_size,bool flag_dif);

//使用分类器将数据分类
double test_clusteData(int v_capacity,int v_max_iterations,int v_num_test,int v_k_clusters );
void optimizeParams();

string getTime()
{
    time_t timep;
    time (&timep); //获取time_t类型的当前时间
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );//对日期和时间进行格式化
    return tmp;
}


int main()
{
  //  addData();

  //  queryData();
  //  modifyDataEntries();
  //  searchDataTest();

  //  vector<string> list;
  //  list.push_back("WHERE description='贵C*X7MMD'");
  //  cout<<mysql_uvss::getSelectQuery("*","tb_uvsslabel",list)<<endl;

  //  float labels[128];
  //  cout<<mysql_uvss::mkLabelQuery("*","tb_uvsslabel",labels)<<endl;

  try {
    optimizeParams();

  } catch (string msg) {
    cout<<"msg:"<<msg<<endl;
  }



  return 0;
}



void optimizeParams(){
  int capacitys[]={5000,10000,50000,100000};
  int max_iterations[]={100,500,1000,5000};
  int k_clusters_min=2;
  int k_clusters_max=1024;
  int num_test[]={100,500,1000};
  int k_clusters[]={2,4,8,16,32,64,128,256,512,1024};

//  验证测试
//  for(uint i=0;i<4;i++){
//    for(uint j=1;j<4;j++){
//      for(uint m=0;m<3;m++){
//        cout<<"capacitys:"<<capacitys[i]<<" max_iterations:"
//           <<max_iterations[j]<<" num_test:"<<num_test[m]<<" k_clusters:"<<64;
//        fflush(stdout);
//        double ret=test_clusteData(capacitys[i],max_iterations[j],num_test[m],64);
//        cout<<" result:"<<ret<<" "<<getTime()<<endl;
//      }
//    }
//  }
  int capacitys_set=5000;
  int max_iterations_set=50;
  int num_test_set=500;


  for(int n=0;n<=10;n++){
    cout<<"capacitys:"<<capacitys_set<<" max_iterations:"
       <<max_iterations_set<<" num_test:"<<num_test_set<<" k_clusters:"<<k_clusters[n];
    fflush(stdout);
    double ret=test_clusteData(capacitys_set,max_iterations_set,num_test_set,k_clusters[n]);
    cout<<" result:"<<ret<<" "<<getTime()<<endl;
  }


  //优化聚类中心数量
  for(int tmpk=k_clusters_min;tmpk<=k_clusters_max;k_clusters_max++){
    cout<<"capacitys:"<<capacitys_set<<" max_iterations:"
       <<max_iterations_set<<" num_test:"<<num_test_set<<" k_clusters:"<<tmpk;
    fflush(stdout);
    double ret=test_clusteData(capacitys_set,max_iterations_set,num_test_set,tmpk);
    cout<<" result:"<<" "<<getTime()<<ret<<endl;
  }

}


//初始化数据库
//访问数据表
//取出所有搜索结果
//  解析数据
//返回数据
vector<alg::PointEg> getDataFromDataBase(int v_size,bool flag_dif){
  mysql_uvss::mysql_init();
  const string tb_name="tb_uvsslabel";
  MYSQL_RES* sql_res=mysql_uvss::mysql_QueryOneEntry(tb_name);

  vector<alg::PointEg> points;

  if(sql_res != nullptr){

    unsigned int numFields = mysql_num_fields(sql_res);
    unsigned long long  numRows = mysql_num_rows(sql_res);

    //    cout<<"numRows: "<<numRows<<endl;

    MYSQL_ROW row;

    float label_tmp[128];
    int count=0;

    //对于每项数据，只要数据条目与源数据编号不同
    while( (row = mysql_fetch_row(sql_res)) != NULL &&count<v_size)
    {

      for(unsigned int j=4; j<numFields-1; j++)
      {
        sscanf(row[j],"%f",&label_tmp[j-4]);
      }

      char tmp[128];
      memset(tmp,0,128*sizeof (char));
      strcpy(tmp,row[1]);

      if(find(points.begin(),points.end(),alg::PointEg(label_tmp,128,string(tmp)))==points.end()
         ){
        points.push_back(alg::PointEg(label_tmp,128,string(tmp)));
        count++;
      }

    }

    mysql_free_result(sql_res);
  }


  mysql_uvss::mysql_close();
  return points;


}





void searchDataTest(){
  struct timeval tv_record;
  struct timezone tz_record;
  struct timeval tv_current;
  struct timezone tz_current;

  mysql_uvss::mysql_init();
  const string tb_name="tb_uvsslabel";

  //query 100000 entries
  gettimeofday(&tv_record,&tz_record);
  MYSQL_RES* sql_res=mysql_uvss::mysql_QueryOneEntry(tb_name,"贵F*99HKW");
  gettimeofday(&tv_current,&tz_current);
  long time_interval=getTime(tv_current)-getTime(tv_record);
  cout<<"get timecost : "<<time_interval<<" us"<<endl;

  if(sql_res != nullptr){
    unsigned long long numFields = mysql_num_rows(sql_res);
    cout<<"numFields: "<<numFields<<endl;
  }


  //query 10000 entries
  gettimeofday(&tv_record,&tz_record);
  MYSQL_RES* sql_res_10000=mysql_uvss::mysql_QueryOneEntry(tb_name,"贵C*X7MMD");
  gettimeofday(&tv_current,&tz_current);
  time_interval=getTime(tv_current)-getTime(tv_record);
  cout<<"get timecost : "<<time_interval<<" us"<<endl;

  if(sql_res != nullptr){
    unsigned long long  numFields = mysql_num_rows(sql_res_10000);
    cout<<"numFields: "<<numFields<<endl;
    cout<<"sql_res->field_count: "<<sql_res->row_count<<endl;

  }

  //query 10000 entries
  gettimeofday(&tv_record,&tz_record);
  MYSQL_RES* sql_res_1000=mysql_uvss::mysql_QueryOneEntry(tb_name,"皖M*SCCMB");
  gettimeofday(&tv_current,&tz_current);
  time_interval=getTime(tv_current)-getTime(tv_record);
  cout<<"get timecost : "<<time_interval<<" us"<<endl;
  if(sql_res != nullptr){
    unsigned long long  numFields = mysql_num_rows(sql_res_1000);
    cout<<"numFields: "<<numFields<<endl;
  }


  //query 110000 entries
  gettimeofday(&tv_record,&tz_record);
  MYSQL_RES* sql_res_110000=mysql_uvss::mysql_QueryOneEntry(tb_name,"贵F*99HKW' OR description='贵C*X7MMD");
  gettimeofday(&tv_current,&tz_current);
  time_interval=getTime(tv_current)-getTime(tv_record);
  cout<<"get timecost : "<<time_interval<<" us"<<endl;
  if(sql_res != nullptr){
    unsigned long long  numFields = mysql_num_rows(sql_res_110000);
    cout<<"numFields: "<<numFields<<endl;
  }

  //query 110000 entries
  gettimeofday(&tv_record,&tz_record);
  MYSQL_RES* sql_res_100000=mysql_uvss::mysql_QueryOneEntry(tb_name,"贵F*99HKW' AND description!='贵C*X7MMD");
  gettimeofday(&tv_current,&tz_current);
  time_interval=getTime(tv_current)-getTime(tv_record);
  cout<<"get timecost : "<<time_interval<<" us"<<endl;
  if(sql_res != nullptr){
    cout<<"---two description---"<<endl;
    unsigned long long  numFields = mysql_num_rows(sql_res_100000);
    cout<<"numFields: "<<numFields<<endl;
  }

  //query 110000 entries
  gettimeofday(&tv_record,&tz_record);
  MYSQL_RES* sql_res_2=mysql_uvss::mysql_QueryOneEntry(tb_name,"贵F*99HKW' AND small!='/run/media/sxy/Extend/Data/output/2017-09-21-19.44.54_45_sm");
  gettimeofday(&tv_current,&tz_current);
  time_interval=getTime(tv_current)-getTime(tv_record);
  cout<<"get timecost : "<<time_interval<<" us"<<endl;
  if(sql_res_2 != nullptr){
    unsigned long long  numFields = mysql_num_rows(sql_res_2);
    cout<<"---two conditions---"<<endl;
    cout<<"numFields: "<<numFields<<endl;
  }


  //query 110000 entries
  gettimeofday(&tv_record,&tz_record);
  MYSQL_RES* sql_res_111000=mysql_uvss::mysql_QueryOneEntry(tb_name,"贵F*99HKW' OR description='贵C*X7MMD' OR description='皖M*SCCMB" );
  gettimeofday(&tv_current,&tz_current);
  time_interval=getTime(tv_current)-getTime(tv_record);
  cout<<"get timecost : "<<time_interval<<" us"<<endl;
  if(sql_res_111000 != nullptr){
    unsigned long long  numFields = mysql_num_rows(sql_res_111000);
    cout<<"numFields: "<<numFields<<endl;
  }

  mysql_uvss::mysql_close();
}



void searchSimilarImage(float* v_label,char* v_image,char*v_small,
                        float* v_label_target,char* v_image_target,char*v_small_target
                        ){

  //  cout<<"\n--------------------searchSimilarImage--------------------\n";

  const string tb_name="tb_uvsslabel";
  struct timeval tv_record;
  struct timezone tz_record;
  struct timeval tv_current;
  struct timezone tz_current;
  gettimeofday(&tv_record,&tz_record);

  mysql_uvss::mysql_init();



  //获取所有数据
  MYSQL_RES* sql_res=mysql_uvss::mysql_QueryOneEntry(tb_name);

  //  //限定label值
  //  string query=mysql_uvss::mkLabelQuery("*",tb_name,v_label);
  //  cout<<"query:"<<query<<endl;
  //  MYSQL_RES* sql_res=mysql_uvss::mysql_Query(query);

  gettimeofday(&tv_current,&tz_current);
  long time_interval=getTime(tv_current)-getTime(tv_record);
  //  cout<<"LABEL RANGE timecost : "<<time_interval<<" us"<<endl;
  gettimeofday(&tv_record,&tz_record);


  if(sql_res != nullptr){

    unsigned int numFields = mysql_num_fields(sql_res);


    MYSQL_ROW row;

    float min_label=9999;

    memset(v_image_target,0,128*sizeof (char));
    memset(v_small_target,0,128*sizeof (char));
    float label_temp[128];


    //对于每项数据，只要数据条目与源数据编号不同
    while( (row = mysql_fetch_row(sql_res)) != NULL )
    {
      //      cout<<"inwhile ! "<<endl;

      for(unsigned int j=4; j<numFields-1; j++)
      {
        sscanf(row[j],"%f",&label_temp[j-4]);
      }

      char tmp[128];
      memset(tmp,0,128*sizeof (char));

      strcpy(tmp,row[1]);
      if(strcmp(tmp,v_image)== 0){
        continue;
      }

      float tmplabel=uvsslabeldistance::uld_Distance(v_label,label_temp);
      if(min_label>tmplabel){
        min_label =tmplabel ;
        strcpy(v_image_target,row[1]);
        strcpy(v_small_target,row[3]);
        for(uint i=0;i<128;i++){
          v_label_target[i]=label_temp[i];
        }

      }
    }
    gettimeofday(&tv_current,&tz_current);
    time_interval=getTime(tv_current)-getTime(tv_record);

    mysql_free_result(sql_res);

  }

  mysql_uvss::mysql_close();
  //  cout<<"\n------------------searchSimilarImage end------------------\n";

}


//获取某一数据库文档中的所有数据项
//对于每一项数据均进行以下操作：searchSimilarImage
void queryData(){
  const string tb_name="tb_uvsslabel";
  float label_tmp[128];


  mysql_uvss::mysql_init();

  MYSQL_RES* sql_res=mysql_uvss::mysql_QueryOneEntry(tb_name);

  if(sql_res != nullptr){
    unsigned int numFields = mysql_num_fields(sql_res);
    MYSQL_ROW row;

    char tmp_image[128];
    char v_small[128];
    memset(tmp_image,0,128*sizeof (char));
    memset(v_small,0,128*sizeof (char));


    while( (row = mysql_fetch_row(sql_res)) != NULL )
    {

      for(unsigned int j=4; j<numFields-1; j++)
      {
        sscanf(row[j],"%f",&label_tmp[j-4]);
      }
      strcpy(tmp_image,row[1]);
      strcpy(v_small,row[3]);

      float label_target[128];
      char dir_image[128];
      char file_small[128];
      searchSimilarImage(label_tmp,tmp_image,v_small,label_target,dir_image,file_small);


    }

    mysql_free_result(sql_res);
  }


  mysql_uvss::mysql_close();
}


void addData(){
  const string tb_name="tb_uvsslabel";
  mysql_uvss::mysql_init();
  int flag_create =mysql_uvss::mysql_createtable(tb_name);
  cout<<"flag_create:"<<flag_create<<endl;

  ulong num_record=0;
  struct timeval tv_record;
  struct timezone tz_record;
  struct timeval tv_current;
  struct timezone tz_current;
  long interval_time=1000000000;


  string dir_output="/run/media/sxy/Extend/Data/output";
  string file_record=dir_output+"/record.txt";

  RecordBuf recbuf;
  gettimeofday(&tv_record,&tz_record);
  gettimeofday(&tv_current,&tz_current);

  while(getTime(tv_current)-getTime(tv_record)<=interval_time){

    bool flag=RecordBuf::loadFromFile(file_record,recbuf);
    if(!flag){
      cout<<"fail to load RecordBuf"<<endl;
      return ;
    }
    ulong num_current =recbuf.list_Record.size();
    if(num_current<=num_record){
      //            continue;
      gettimeofday(&tv_current,&tz_current);
    }
    else{
      for(ulong i=num_record;i<recbuf.list_Record.size();i++){
        cout<<"dir  :"<<recbuf.list_Record[i].dir<<endl;
        cout<<"small:"<<recbuf.list_Record[i].imagename_small<<endl;
        cout<<"big  :"<<recbuf.list_Record[i].imagename_big<<endl;


        string path_image=recbuf.list_Record[i].dir+"/"+recbuf.list_Record[i].imagename_small;
        float label[128];
        uvsslabeldistance::uld_CalculateLabel(path_image.c_str(),label);
        mysql_uvss::mysql_insertData(tb_name,recbuf.list_Record[i].dir,
                                     recbuf.list_Record[i].imagename_big,
                                     recbuf.list_Record[i].imagename_small,
                                     label,i);
      }
      gettimeofday(&tv_current,&tz_current);
      num_record=num_current;
      tv_record=tv_current;
      tz_record=tz_current;
    }
  }

  mysql_uvss::mysql_close();
}

//修改表中的数据description为相应的车牌号
void modifyDataEntries(){

  int a[]={100000,10000,1000};
  int nums=3;
  vector<int> list;
  for(int i=0;i<nums;i++){
    list.push_back(a[i]);
  }
  LicenseGenerator generator(1000,1000000,list);
  map<string,int>  list_defined= generator.getDefinedList();
  //  generator.print();
  for(auto &it : list_defined){
    cout<<it.first<<": "<<it.second<<endl;
  }

  mysql_uvss::mysql_init();
  const string tb_name="tb_uvsslabel";

  for (uint i=1;i<=1000000;i++) {
    string plate_tmp=generator.getOnePlateAndRm();
    mysql_uvss::mysql_updateData_Description(tb_name,i,plate_tmp);
  }

  mysql_uvss::mysql_close();

  for(auto &it : list_defined){
    cout<<it.first<<": "<<it.second<<endl;
  }

}

double test_clusteData(int v_capacity,int v_max_iterations,int v_num_test,int v_k_clusters ){
  //  cout<<"=================Data Cluste Start================="<<endl;

  //init para
  //  int capacity=10000;
  //  int max_iterations=1000;
  //  int num_test=10000;
  //  int k_clusters=64;

  int capacity=v_capacity;
  int max_iterations=v_max_iterations;
  int num_test=v_num_test;
  int k_clusters=v_k_clusters;


  int dimensions=128;



  //  cout<<"capacity      :"<<capacity<<endl;
  //  cout<<"dimensions    :"<<dimensions<<endl;
  //  cout<<"k_clusters    :"<<k_clusters<<endl;
  //  cout<<"max_iterations:"<<max_iterations<<endl;


  //get samples from database
  vector<alg::PointEg> list= getDataFromDataBase(capacity,false);
  //  cout<<"listsize:"<<list.size()<<endl;
  //  cout<<"[finish]:getDataFromDataBase "<<endl;

  //init cluster
  alg::KmeansCluster<alg::PointEg> classfier(k_clusters,max_iterations,list);
  //  cout<<"[finish]:classfier initailize "<<endl;

  //run
  classfier.run();
  //  cout<<"[finish]:classfier run"<<endl;


  vector<alg::PointEg> list_centrapoint= classfier.getCentraPoints();
  //  cout<<"list_centrapoint:"<<list_centrapoint.size()<<endl;
  //  for(uint i=0;i<list_centrapoint.size();i++){
  //    cout<<"["<<i<<"]:"<<list_centrapoint[i]<<endl;
  //  }

  //分析测试的准确性
  //  某一条数据遍历数据库找到的相似图片，两张图片是否能归类到同一个类中
  //   cluster 添加接口：尝试添加条数据，查看该数据的聚类归属

  vector<alg::PointEg> list_test= getDataFromDataBase(num_test,false);

  int num_total=0;
  int num_match=0;
  for(uint i=0;i<list_test.size();i++){
    float label_src[128];
    char imagedir_src[128];
    char imagesmall_src[128];
    for(uint j=0;j<128;j++){
      label_src[j]=static_cast<float>(list_test[i].at(j));
    }
    memcpy(imagedir_src,list_test[i].getName().c_str(),list_test[i].getName().size()+1);


    float label_target[128];
    char imagedir_target[128];
    char imagesmall_target[128];

    searchSimilarImage(label_src,imagedir_src,imagesmall_src,
                       label_target,imagedir_target,imagesmall_target);
    //    cout<<"imagedir_src:"<<imagedir_src<<endl;
    //    cout<<"imagedir_target:"<<imagedir_target<<endl;

    //    cout<<"label_target:"<<endl;
    //    for(uint j=0;j<128;j++){
    //      cout<<j<<": "<<label_target[j]<<endl;
    //    }



    int seq_src=classfier.tryToClusters(alg::PointEg(label_src,128));
    int seq_target=classfier.tryToClusters(alg::PointEg(label_target,128));

    //    cout<<"seq_src:"<<seq_src<<endl;
    //    cout<<"seq_target:"<<seq_target<<endl;
    if(seq_src == seq_target){
      num_match++;
    }
    num_total++;
    //    cout<<"num_match:"<<num_match<<endl;
    //    cout<<"num_total:"<<num_total<<endl;

  }

  if(num_total == 0){
    return 0;
  }
  else{
    return num_match*1.0/num_total;

  }




  //  cout<<"=================Data Cluste End================="<<endl;
}


