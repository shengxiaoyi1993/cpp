#ifndef LICENSEGENERATOR_H
#define LICENSEGENERATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/time.h>

using namespace std;
class LicenseGenerator
{
private:
  static const vector<char> _list_charactor;
  static const vector<string> _list_prefix;

  vector<string> _list_plate_type;
  vector<string> _list_platebufferlist;
  map<string,int> _list_plate_distribution;
  uint _types;
  uint _size;
  vector<int> _list_distri;


public:
  LicenseGenerator(uint v_types, uint v_size, const vector<int>& v_list_distri);

  ~LicenseGenerator();
  /**
   * @brief generatorRandomLicense 生成一个随即的车牌号
   * @return
   */
  static string generatorRandomLicense();
  /**
   * @brief getRandom 返回一个在v_low～v_high 之间的随机数
   * @param v_low
   * @param v_high
   * @return
   */
  static uint getRandom(uint v_low,uint v_high);

  void print();
  /**
   * @brief getOnePlateAndRm get one plate and rm it from _list_platebufferlist
   * @return
   */
  string getOnePlateAndRm();

  map<string,int> getDefinedList();




};

#endif // LICENSEGENERATOR_H
