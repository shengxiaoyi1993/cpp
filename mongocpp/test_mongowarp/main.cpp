#include "bs_cxx_driver_export.h"
#include <iostream>


using namespace std;


int main(int argc, char *argv[])
{
    mongo::Init();
    //    char * newid=NewObjectId();
    //    cout<<"newid:"<<newid<<endl;
    //    char * newid1=NewObjectId();
    //    cout<<"newid1:"<<newid1<<endl;
    //    char * newid2=NewObjectId();
    //    cout<<"newid2:"<<newid2<<endl;

    char ptable[]="sxy";
    char* pdata_intable=FindAll(ptable);
    cout<<"pdata_intable:"<<pdata_intable<<endl;
    free(pdata_intable);
    pdata_intable=nullptr;


    char pdoc0[]="{\"name\":\"sxy\"}";
    char* pid_insert= Add(pdoc0,ptable);
    cout<<"pid_insert:"<<pid_insert<<endl;

    pdata_intable=FindAll(ptable);
    cout<<"pdata_intable:"<<pdata_intable<<endl;
    free(pdata_intable);
    pdata_intable=nullptr;

    //    cout<<">>find by id:"<<endl;
    //    char * pid_find=FindOneById(pid_insert ,  ptable);
    //    cout<<"pid_find:"<<pid_find<<endl;

    //    cout<<">>find by conition:"<<endl;
    //    char con[]="{\"name\":\"sxy\"}";
    //    char * pid_findbycon=FindOne(con ,  ptable);
    //    cout<<"pid_findbycon:"<<pid_findbycon<<endl;

    //    cout<<">>findmany by conition:"<<endl;
    //    char* pmany=FindMany(con,1,20,ptable);
    //    cout<<"pmany:"<<pmany<<endl;

    //    cout<<">>DeleteById:"<<endl;
    //    bool flag_detlete=DeleteById(pid_insert,ptable);
    //    cout<<"flag_detlete:"<<flag_detlete<<endl;

    //    cout<<">>FindAll:"<<endl;
    //    pdata_intable=FindAll(ptable);
    //    cout<<"pdata_intable:"<<pdata_intable<<endl;
    //    free(pdata_intable);
    //    pdata_intable=nullptr;

    //    char doc_new[]="{\"name\":\"lli\"}";
    //    bool flag_update=UpdateById(pid_insert,doc_new,ptable);
    //    cout<<"flag_update:"<<flag_update<<endl;

    //    cout<<">>FindAll:"<<endl;
    //    pdata_intable=FindAll(ptable);
    //    cout<<"pdata_intable:"<<pdata_intable<<endl;
    //    free(pdata_intable);
    //    pdata_intable=nullptr;

    char con[]="{\"name\":\"sxy\"}";
    cout<<">>Count:"<<endl;
    int cout_coll=Count(con,ptable);
    cout<<"cout_coll:"<<cout_coll<<endl;


    mongo::Cleanup();
    return 0;
}
