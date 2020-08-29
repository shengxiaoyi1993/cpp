#ifndef LICENSEGENERATOR_H
#define LICENSEGENERATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sys/time.h>

using namespace std;
class LicenseGenerator
{
private:
  static const vector<char> _list_charactor;
  static const vector<string> _list_prefix;
public:
  LicenseGenerator();
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





};

#endif // LICENSEGENERATOR_H
