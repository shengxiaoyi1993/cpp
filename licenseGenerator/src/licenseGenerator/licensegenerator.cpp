#include "licensegenerator.h"

const vector<char> LicenseGenerator::_list_charactor=
{'0','1','2','3','4','5','6','7','8','9','A','B','C',
 'D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V','W','X','Y','Z'};

const vector<string> LicenseGenerator::_list_prefix={
  "京A","京C","京E","京F","京H","京G","京B","津A","津B", "津C", "津E",
  "沪A", "沪B", "沪D", "沪C","渝A", "渝B", "渝C", "渝G", "渝H","冀A",
  "冀B", "冀C", "冀D", "冀E", "冀F", "冀G", "冀H", "冀J", "冀R", "冀T",
  "豫A", "豫B", "豫C", "豫D", "豫E", "豫F","豫G","豫H","豫J","豫K","豫L",
  "豫M","豫N","豫P","豫Q","豫R","豫S","豫U","云A", "云C", "云D", "云E", "云F",
  "云G","云H","云J","云K","云L","云M","云N","云P","云Q","云R ","云S",
  "辽A", "辽B", "辽C", "辽D", "辽E", "辽F","辽G","辽H","辽J","辽K","辽L","辽M",
  "辽N","辽P","辽V","黑A", "黑B", "黑C", "黑D", "黑E", "黑F","黑G","黑H","黑J","黑K",
  "黑L","黑M","黑N","黑P","黑R","湘A", "湘B", "湘C", "湘D", "湘E", "湘F","湘G","湘H","湘J",
  "湘K","湘L","湘M","湘N","湘U","湘S","皖A", "皖B", "皖C", "皖D", "皖E", "皖F","皖G","皖H","皖J",
  "皖K","皖L","皖M","皖N","皖P","皖Q","皖R","皖S","鲁A", "鲁B", "鲁C", "鲁D", "鲁E", "鲁F","鲁G",
  "鲁H","鲁J","鲁K","鲁L","鲁M","鲁N","鲁P","鲁Q","鲁R","鲁S","鲁U","鲁V","鲁Y","新A", "新B", "新C",
  "新D", "新E", "新F","新G","新H","新J","新K","新L","新M","新N","新P","新Q","新R","苏A", "苏B", "苏C",
  "苏D", "苏E", "苏F","苏G","苏H","苏J","苏K","苏L","苏M","苏N","浙A", "浙B", "浙C", "浙D", "浙E", "浙F",
  "浙G","浙H","浙J","浙K ","浙L","赣A","赣B","赣C","赣D","赣E","赣F","赣G","赣H","赣J","赣K","赣L","赣M","鄂A",
  "鄂B","鄂C","鄂D","鄂E","鄂F","鄂G","鄂H","鄂J","鄂K" ,"鄂L","鄂M","鄂N","鄂P","鄂Q","鄂R","鄂S","桂A","桂B",
  "桂C","桂D","桂E","桂F","桂G","桂H","桂J","桂K","桂L","桂M","桂N","桂P" ,"桂R","甘A","甘B","甘C","甘D","甘E",
  "甘F","甘G","甘H","甘J","甘K","甘L","甘M" ,"甘N","甘P","晋A" ,"晋B","晋C","晋D","晋E","晋F","晋H","晋J","晋K",
  "晋L","晋M","蒙A","蒙B","蒙C","蒙D","蒙E","蒙F","蒙G","蒙H","蒙J","蒙K","蒙L","蒙M","陕A","陕B","陕C","陕D","陕E",
  "陕F","陕G","陕H","陕J","陕K","陕U","陕V","吉A","吉B","吉C","吉D","吉E","吉F","吉G","吉H","吉J","闽A","闽B","闽C",
  "闽D","闽E","闽F" ,"闽G","闽H","闽J","闽K","贵A","贵B" ,"贵C","贵D","贵E" ,"贵F","贵G","贵H","贵J","粤A","粤B","粤C",
  "粤D","粤E","粤F","粤G","粤H","粤J","粤K","粤L","粤M","粤N","粤P","粤Q","粤R","粤S","粤T","粤U","粤V","粤W","粤X","粤Y",
  "粤Z","青A","青B","青C","青D","青E","青F","青G","青H","藏A","藏B","藏C","藏D","藏E","藏F","藏G","藏H" ,"藏J","川A","川B",
  "川C","川D","川E","川F","川H","川J","川K","川L","川M","川Q","川R","川S","川T","川U","川V","川W","川X","川Y","川Z","宁A",
  "宁B","宁C","宁D","琼A","琼B","琼C","琼D","琼E"
};


LicenseGenerator::LicenseGenerator(uint v_types,uint v_size,const vector<int>& v_list_distri):
  _types(v_types),_size(v_size)
{
  _list_distri.clear();
  for(uint i=0;i<v_list_distri.size();i++){
    _list_distri.push_back(v_list_distri[i]);
  }

  //check
  int num_userdefine=0;
  for(uint i=0;i<v_list_distri.size();i++){
    num_userdefine+=v_list_distri[i];
  }
  if(num_userdefine<0||num_userdefine>v_size){
    throw string(__func__)+" para error !";
  }

  for(uint i=0;i<v_types;i++){
    _list_plate_type.push_back(generatorRandomLicense());
  }

  //init _list_plate_distribution
  int size_remain=v_size;
  for(uint i=0;i<v_list_distri.size();i++){
    _list_plate_distribution[_list_plate_type[i]]=v_list_distri[i];
    size_remain-=v_list_distri[i];
  }

  int types_remain=static_cast<int>(v_types-v_list_distri.size());
  int num_align=size_remain/types_remain;
  int num_remaun=num_align+size_remain%types_remain;
//  cout<<"v_size:"<<v_size<<endl;
//  cout<<"v_list_distri.size():"<<v_list_distri.size()<<endl;
//  cout<<"num_align:"<<num_align<<endl;
//  cout<<"num_remaun:"<<num_remaun<<endl;

  for(uint i=v_list_distri.size();i<_list_plate_type.size()-1;i++){
    _list_plate_distribution[_list_plate_type[i]]=num_align;
  }
  _list_plate_distribution[_list_plate_type[_list_plate_type.size()-1]]=num_remaun;


  _list_platebufferlist.clear();
  //  for(uint i=0;i<_list_plate_distribution.size();i++){
  //    _list_platebufferlist.push_back(_list_plate_distribution[]);
  //  }
  for(auto &it : _list_plate_distribution){
    for(int i=0;i<it.second;i++){
      _list_platebufferlist.push_back(it.first);
    }
  }

}

LicenseGenerator::~LicenseGenerator(){

}

string LicenseGenerator::getOnePlateAndRm(){
  if(_list_platebufferlist.size() == 0){
    throw string(__func__)+"Error:no element remains!";
  }
  uint seq=getRandom(0,_list_platebufferlist.size());
  string ret=_list_platebufferlist[seq];
  _list_platebufferlist.erase(_list_platebufferlist.begin()+seq);
  return ret;
}



string LicenseGenerator::generatorRandomLicense(){

  string ret_license;
  ret_license+=_list_prefix[getRandom(0,_list_prefix.size())];
  ret_license.push_back('*');
  for(uint i=0;i<5;i++){
    ret_license.push_back(_list_charactor[getRandom(0,_list_charactor.size())]);
  }
  return ret_license;
}

uint LicenseGenerator::getRandom(uint v_low,uint v_high){
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv,&tz);
  srand(tv.tv_sec*1000000 +tv.tv_usec);
  uint interval=v_high-v_low;
  uint num=random()%interval+v_low;
  return num;
}


void LicenseGenerator::print(){

  for(auto &it : _list_plate_distribution){
    cout<<it.first<<": "<<it.second<<endl;
  }
  cout<<"_list_platebufferlist.size："<<_list_platebufferlist.size()<<endl;
  for(uint i=0;i<_list_distri.size();i++){
    cout<<_list_distri[i]<<":"<<_list_plate_type[i]<<endl;
  }

}


map<string,int> LicenseGenerator::getDefinedList(){
  map<string,int> v_list;
  for(uint i=0;i<_list_distri.size();i++){
    v_list[_list_plate_type[i]]=_list_distri[i];
  }
  return v_list;
}
