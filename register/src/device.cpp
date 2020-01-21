#include "device.h"
#include "basic.h"


#define MAP_REG_SIZE 0x10000
#define MAP_PB_SIZE 0x07f00000

using namespace std;

DeviceIO::DeviceIO(const string & path_register_info , const char *fn):_uio(fn),
    _mmap_regs(_uio,0,MAP_REG_SIZE){
    char* buffer;
    if(0 == basic::getStringFromFile(path_register_info,&buffer)){
        cout<<"succeed to open file: "<<path_register_info<<endl;
        cJSON* v_obj=cJSON_Parse(buffer);

        if(v_obj!= nullptr){
            cJSON *array=cJSON_GetObjectItem(v_obj,"list");
            if(cJSON_IsArray(array)){
                int num_array = cJSON_GetArraySize(array);
                cJSON* subitem;
                for(int i=0;i<num_array;i++){
                    subitem=cJSON_GetArrayItem(array,i);
                    _list_register.push_back(Register::loadFromJsonObj(subitem));
                }
            }
        }
    }
    else{
        cout<<"can not open file: "<<path_register_info<<endl;
    }

    //!test
    cout<<"load register list: "<<endl;;
    cout<<"size:"<<_list_register.size()<<endl;
    for(uint i=0;i<_list_register.size();i++){
        cout<<"i: "<<i<<
              " name: "<<_list_register[i].vname();
        cout<<" addr: "<<_list_register[i].vaddr();
        cout<<" mask: "<<_list_register[i].vmask();
        cout<<" shift: "<<_list_register[i].vshift();
        cout<<" signed: "<<_list_register[i].vsigned()<<endl;
    }

}



int DeviceIO::writeReg(const string& name_reg,unsigned wr_word){
    Register register_target;
    if(findRegister(name_reg,register_target)){
        uint32_t value =(wr_word<<register_target.vshift())&register_target.vmask();
        uint32_t value_read =_mmap_regs.read_word(static_cast<int>(register_target.vaddr()));
        value_read=value&register_target.vmask();
         uint32_t value_write=value_read|value;
         _mmap_regs.write_word(static_cast<int>(register_target.vaddr()),value_write);

         cout<<"succeed to write register:"<<"reg <- "<<value<<endl;

        return 0;
    }
    else{
        cout<<"fail to write register"<<endl;
        return -1;
    }
}

int DeviceIO::readReg(const string& name_reg) {
    Register register_target;
    if(findRegister(name_reg,register_target)){
        uint32_t value = _mmap_regs.read_word(static_cast<int>(register_target.vaddr()));
        value=(value&register_target.vmask())>>register_target.vshift();
        cout<<"succeed to read register: "<<"reg -> "<<value<<endl;
        return 0;
    }
    else{
        cout<<"fail to read register"<<endl;
        return -1;
    }



}

bool DeviceIO::findRegister(const string & name_reg,Register& v_register) const{

    for(uint i=0;i<_list_register.size();i++){
        if(_list_register[i].vname()==name_reg){
            v_register=_list_register[i];
            return true;
        }
    }
    cout<<"fail to find register: "<<name_reg<<endl;
    return false;
}



