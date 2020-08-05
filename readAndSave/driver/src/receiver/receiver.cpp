#include <iostream>
#include "../../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.h"
using namespace std;


void getMsg(ImageBufferInArm v_data){
    cout<<ImageBufferInArm::getString(v_data);
}

int main(int argc, char const *argv[]) {
    ImageBufferChannel customer(MsgChannel_Mode::customer,
                                ImageBufferChannel_TYPE_Display,
                                getMsg
                                );
    cout<<"hello"<<endl;

    getchar();

  /* code */
  return 0;
}
