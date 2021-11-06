#include <regex>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include <netdb.h>
#include <malloc.h>
#include <string.h>


#include "cpp/string_manipulation.hpp"


using namespace common::string_manipulation;

void test_BinaryData_input();
void test_BinaryData_output();
int regtest ();

int ip_reg();



int main() {
  //  bool flag=false;
  //  bool flagsec=true;


  //  if (flag)
  //    switch (0) case 0: default:
  //      if (flagsec) {
  //        cout<<"161"<<endl;
  //      }
  //      else
  //        cout<<"zzz"<<endl;

  //  regtest();
  ip_reg();


  return 0;
}


void test_BinaryData_input(){
  BinaryData bdata(64,BinaryData::BinaryDataDirection_left);
  bdata.print();
  try {
    bdata.appendData<unsigned>(65535,1);
    bdata.print();

    bdata.appendData<unsigned>(65535,8);
    bdata.print();

    bdata.appendData<unsigned>(65535,8);
    bdata.print();

    bdata.endAppend(true);
    bdata.print();



  } catch (const char * msg) {
    cout<<"msg:"<<msg<<endl;

  }
  bdata.print();
  //   unsigned int tmp= bdata.getSheld<unsigned>(7,9,true);
}

void test_BinaryData_output(){

}




int regtest ()
{

  if (std::regex_match ("subject", std::regex("(sub)(.*)") ))
    std::cout << "string literal matched\n";

  const char cstr[] = "subject";
  std::string s ("subject");
  std::regex e ("(sub)(.*)");

  if (std::regex_match (s,e))
    std::cout << "string object matched\n";

  if ( std::regex_match ( s.begin(), s.end(), e ) )
    std::cout << "range matched\n";

  std::cmatch cm;    // same as std::match_results<const char*> cm;
  std::regex_match (cstr,cm,e);
  std::cout << "string literal with " << cm.size() << " matches\n";

  std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
  std::regex_match (s,sm,e);
  std::cout << "string object with " << sm.size() << " matches\n";

  std::regex_match ( s.cbegin(), s.cend(), sm, e);
  std::cout << "range with " << sm.size() << " matches\n";

  // using explicit flags:
  std::regex_match ( cstr, cm, e, std::regex_constants::match_default );

  std::cout << "the matches were: ";
  for (unsigned i=0; i<cm.size(); ++i) {
    std::cout << "[" << cm[i] << "] ";
  }

  std::cout << std::endl;

  return 0;
}

char *strdup(char *s)
{
    char *retval;

    retval = (char *) malloc(strlen(s) + 1);
    if (retval == NULL) {
        perror("boa: out of memory in strdup");
        exit(1);
    }
    return strcpy(retval, s);
}


int ip_reg(){
  //  regex ipPattern("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9]))",std::regex::basic);


  //  string ip("192.168.1.126");

  //  regex ipPattern("25[0-5]|2[0-4][0-9]",std::regex::extended);

  //  string ip("236");


  //  cout<<"regex_match:"<< std::regex_match(ip, ipPattern);


//  regex reg_ecma(
////        "(25[012345])",
//        "(\\d{4})[- ](\\d{2})[- ](\\d{2})",
//        std::regex::ECMAScript);

//  string match("254");

//  cout<<"regex_match:"<< std::regex_match(match, reg_ecma);

//  string data = "1994-06-25\n"
//                "2015-09-13\n"
//                "2015 09 13\n";
//  smatch m;
//  regex reg("(\\d{4})[- ](\\d{2})[- ](\\d{2})");
  //sregex_iterator pos(data.cbegin(),data.cend(),regex("(\\d{4})[- ](\\d{2})[- ](\\d{2})"));
//  sregex_iterator pos(data.cbegin(),data.cend(),reg);
//  sregex_iterator end;
//      for( ; pos!=end ;pos++){
//          cout << pos->str() << " ";
//          cout << pos->str(1) << " " <<pos->str(2) <<" " << pos->str(3) << endl;
//      }

  // basic_regex constructors
  // note: using regex, a standard alias of basic_regex<char>

//    std::string pattern = "^.*$";

//    std::regex first;                                        // default
//    std::regex second = first;                               // copy
//    std::regex third (pattern);                              // string object initialization
//    std::regex fourth ("<[^>]>");                            // string literal initialization
//    std::regex fifth (pattern.begin(),pattern.end());        // range initialization
//    std::regex sixth {'.','+'};                              // initializer_list initialization

//    std::regex seventh ("[0-9A-Z]+", std::regex::ECMAScript);// with syntax option

//    using namespace std::regex_constants;                    // introducing constants namespace
//    std::regex eighth ("[0-9A-Z]+", ECMAScript);             // same as seventh

//    std::regex ninth ("\\bd\\w+", ECMAScript | icase );      // multiple flags

//    std::string subject = "Duddy the duck";
//    std::string replacement = "yup";

////    std::cout << std::regex_replace (subject, ninth, replacement);
//    std::cout << std::endl;

/// 切换根目录/工作目录
{
//    chdir("/home/sxy");
    struct hostent *he;
    char temp_name[100];

    if (gethostname(temp_name, 100) == -1) {
        perror("gethostname:");
        exit(1);
    }

    he = gethostbyname(temp_name);
    if (he == NULL) {
        perror("gethostbyname:");
        exit(1);
    }

    printf("temp_name:%s\n",temp_name);
//    printf("temp_name:%s\n",temp_name)
    char*  server_name = strdup(he->h_name);

    printf("server_name:%s\n",server_name);
    free(server_name);
    server_name=nullptr;



  }

  return 0;
}

