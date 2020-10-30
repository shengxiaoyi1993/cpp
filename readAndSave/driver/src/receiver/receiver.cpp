#include <iostream>
#include "../../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.h"
using namespace std;

ImageBufferChannel *g_customer;
void getMsg(ImageBufferInArm v_data,void* pdata){
    cout<<ImageBufferInArm::getString(v_data)<<endl;;
    // g_customer->addNewImageBufferInArm(v_data);
    fflush(stdout);
}

int main(int argc, char const *argv[]) {
    g_customer=new ImageBufferChannel(MsgChannel_Mode::customer,
                                ImageBufferChannel_TYPE_Display,
                                getMsg,nullptr
                                );

                                // ImageBufferInArm v_data;
                                // v_data._mode=0;
                                // g_customer->addNewImageBufferInArm(v_data);
                                // v_data._mode=1;
                                // g_customer->addNewImageBufferInArm(v_data);
                                // v_data._mode=2;
                                // g_customer->addNewImageBufferInArm(v_data);
                                // v_data._mode=3;
                                // g_customer->addNewImageBufferInArm(v_data);
    cout<<"hello"<<endl;

    getchar();

  /* code */
  return 0;
}
