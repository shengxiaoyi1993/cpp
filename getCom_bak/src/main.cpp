#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <tchar.h>
#include <iostream>

using namespace std;

bool cmp(string s1, string s2)
{
	if (atoi(s1.substr(3).c_str()) < atoi(s2.substr(3).c_str()))//升序
		return true;
	else
		return false;
}

//获取串口号
void GetComList_Reg(std::vector<string>& comList)
{
	HKEY hkey;
	int result;
	int i = 0;

	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		_T("Hardware\\DeviceMap\\SerialComm"),
		NULL,
		KEY_READ,
		&hkey);

	if (ERROR_SUCCESS == result)   //   打开串口注册表
	{
		TCHAR portName[0x100], commName[0x100];
		DWORD dwLong, dwSize;
		do
		{
			dwSize = sizeof(portName) / sizeof(TCHAR);
			dwLong = dwSize;
			result = RegEnumValue(hkey, i, portName, &dwLong, NULL, NULL, (LPBYTE)commName, &dwSize);
			if (ERROR_NO_MORE_ITEMS == result)
			{
				//   枚举串口
				break;   //   commName就是串口名字"COM4"
			}

			comList.push_back(commName);
			i++;
		} while (1);

		RegCloseKey(hkey);
	}
}

int main(void) {

	vector<string> comList;
	GetComList_Reg(comList);
	sort(comList.begin(), comList.end(), cmp);
	for (int i = 0; i < comList.size(); i++)
	{
		cout << comList[i] << endl;
	}

	system("pause");
	return 0;
}
