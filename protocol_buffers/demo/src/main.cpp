#include <iostream>
#include <google/protobuf/util/time_util.h>
#include <fstream>

#include "resources/data.pb.h"


using google::protobuf::util::TimeUtil;

using namespace std;
int main(int argc, char const *argv[])
{
    SimpleData sdata;
//    sdata.clear_kry()
//    sdata.Clear();
    sdata.set_kry("name");
    sdata.set_value("sxy");

    std::cout<<"sdata:"<<std::endl;
    std::cout<<sdata.kry()<<std::endl;
    std::cout<<sdata.value()<<std::endl;

    fstream output("data.ba", ios::out | ios::trunc | ios::binary);
    if (!sdata.SerializeToOstream(&output)) {
      cerr << "Failed to write address book." << endl;
      return -1;
    }

    {
//      SimpleData data2;
//      data2.set_kry("animal");
//      data2.set_value("monkey");

//      sdata.MergeFrom(data2);
//      std::cout<<"MergeFrom:"<<std::endl;
//      std::cout<<sdata.kry()<<std::endl;
//      std::cout<<sdata.value()<<std::endl;
    }

    /// Swap
    {
//      SimpleData data2;
//      data2.set_kry("animal");
//      data2.set_value("monkey");

//      sdata.Swap(&data2);

//      std::cout<<"After Swap:"<<std::endl;

//      std::cout<<"sdata:"<<std::endl;
//      std::cout<<sdata.kry()<<std::endl;
//      std::cout<<sdata.value()<<std::endl;

//      std::cout<<"data2:"<<std::endl;
//      std::cout<<data2.kry()<<std::endl;
//      std::cout<<data2.value()<<std::endl;

    }


//    sdata.UnsafeArenaSwap();





    SimpleData* p=sdata.New();

    return 0;
}



///void SimpleData::CopyFrom(const SimpleData& from);
/// 复制
///
/// void SimpleData::Clear();
/// 清空
///
///void SimpleData::MergeFrom(const SimpleData& from);
/// 原来的数据被覆盖
///
/// void SimpleData::InternalSwap(SimpleData* other);
/// 数据交换
///
///
/// https://blog.csdn.net/zhuaizi888/article/details/105752582
