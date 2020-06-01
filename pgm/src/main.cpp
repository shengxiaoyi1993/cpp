#include<iostream>
#include <string>
#include "pgm.h"

using namespace std;

static const string path_file="../../resources/test.pgm";
static const string path_targetfile="../../resources/target.pgm";
static const string path_targetfile2="../../resources/target2.pgm";


int main() {
    IMAGE* image=img_open((char*)path_file.c_str());
    if(nullptr != image){
        cout<<"name:"<<image->name<<endl;
        cout<<"cols:"<<image->cols<<endl;
        cout<<"rows:"<<image->rows<<endl;
    }
    else{
        cout<<"fail to open image"<<endl;
    }

    img_write(image,(char*)path_targetfile.c_str());

    IMAGE* image2=img_open((char*)path_targetfile.c_str());
    if(nullptr != image2){
        cout<<"name:"<<image2->name<<endl;
        cout<<"cols:"<<image2->cols<<endl;
        cout<<"rows:"<<image2->rows<<endl;
    }
    else{
        cout<<"fail to open image"<<endl;
    }
    img_write(image2,(char*)path_targetfile2.c_str());


    return 0;
}
