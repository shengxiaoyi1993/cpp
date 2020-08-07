#include <iostream>
#include<sys/time.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "uvss_label_distance_interface.hpp"
#include "../../../../opencv_cpp/learn/imagesort/src/record.h"
#include "mysql.h"

using namespace std;

long getTime(struct timeval v_t){
  return (v_t.tv_sec*1000000+v_t.tv_usec);
}

void addData();
void queryData();

void searchSimilarImage(float* v_label,char* v_image,char& v_small);


int main()
{

  queryData();
  return 0;
}


void searchSimilarImage(float* v_label,char* v_image,char*v_small){

  cout<<"\n--------------------searchSimilarImage--------------------\n";

  const string tb_name="tb_uvsslabel";
  float label_tmp[128];
  struct timeval tv_record;
  struct timezone tz_record;
  struct timeval tv_current;
  struct timezone tz_current;
  gettimeofday(&tv_record,&tz_record);

  mysql_uvss::mysql_init();

  MYSQL_RES* sql_res=mysql_uvss::mysql_QueryOneEntry(tb_name);

  if(sql_res != nullptr){

    unsigned int numFields = mysql_num_fields(sql_res);
    cout<<"numFields: "<<numFields<<endl;

    MYSQL_ROW row;

    float min_label=9999;
    char min_image[128];
    char min_small[128];

    memset(min_image,0,128*sizeof (char));
    memset(min_small,0,128*sizeof (char));



    while( (row = mysql_fetch_row(sql_res)) != NULL )
    {
//      cout<<"inwhile ! "<<endl;

      for(unsigned int j=5; j<numFields-1; j++)
      {
        sscanf(row[j],"%f",&label_tmp[j-5]);
//        cout<<label_tmp[j-5]<<" ";
      }

        char tmp[128];
        memset(tmp,0,128*sizeof (char));

        strcpy(tmp,row[1]);
        if(strcmp(tmp,v_image)== 0){
          continue;
        }

        float tmplabel=uvsslabeldistance::uld_Distance(v_label,label_tmp);
//        cout<<"tmplabel:"<<tmplabel<<endl;
        if(min_label>tmplabel){
          min_label =tmplabel ;
          strcpy(min_image,row[1]);
          strcpy(min_small,row[3]);

//          cout<<"gjg:"<<min_image<<endl;
        }

    }

    cout<<"v_image  : "<<v_image<<endl;
    cout<<"similar  : "<<min_image<<endl;

//    cv::imshow("");

    mysql_free_result(sql_res);
    gettimeofday(&tv_current,&tz_current);
    long time_interval=getTime(tv_current)-getTime(tv_record);
    cout<<"timecost : "<<time_interval<<" us"<<endl;
    gettimeofday(&tv_record,&tz_record);

    //display
    string image_init=string(v_image)+"/"+string(v_small);
    string image_similar=string(min_image)+"/"+string(min_small);
//    cout<<"image_init:"<<image_init<<endl;
//    cout<<"image_similar:"<<image_similar<<endl;

    cv::Mat mat_init=cv::imread(image_init);
    cv::Mat mat_simi=cv::imread(image_similar);
//    mat_init.resize(1080,512);
//    mat_simi.resize(1080,512);
    cv::resize(mat_init, mat_init, cv::Size(mat_init.cols*0.5,mat_init.rows*0.3));
    cv::resize(mat_simi, mat_simi, cv::Size(mat_init.cols,mat_init.rows));

    cv::imshow("mat_init",mat_init);
    cv::imshow("mat_simi",mat_simi);
    cv::waitKey();

  }

  mysql_uvss::mysql_close();
  cout<<"\n------------------searchSimilarImage end------------------\n";

}


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

      for(unsigned int j=5; j<numFields-1; j++)
      {
        sscanf(row[j],"%f",&label_tmp[j-5]);
      }
      strcpy(tmp_image,row[1]);
      strcpy(v_small,row[3]);


      searchSimilarImage(label_tmp,tmp_image,v_small);
    }

    mysql_free_result(sql_res);


  }

  mysql_uvss::mysql_close();
}


void addData(){
  const string tb_name="tb_uvsslabel";
  mysql_uvss::mysql_init();
  mysql_uvss::mysql_createtable(tb_name);

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
                                     label,i+178831);
      }
      gettimeofday(&tv_current,&tz_current);
      num_record=num_current;
      tv_record=tv_current;
      tz_record=tz_current;
    }

  }



  mysql_uvss::mysql_close();
}
