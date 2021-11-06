#include <glog/logging.h>
#include <string>

///可以设置的项
/// - log输出地址
/// - 是否输出到stdout
/// -
void test_commonset(int argc,char*  argv[]);

/// 功能
/// - 分为4个等级 INFO WARNING ERROR FATAL
/// - 检查条件
/// - 设置间隔多少次输出一次
/// - 设置输出最开始的几条
void test_condition(int argc,char*  argv[]);

/// 功能
/// - 只在debug版本有效，非debug版本无效，方便release版本的发布
/// - 同LOG，但没有只输出前几条的功能
void test_condition_debug(int argc,char*  argv[]);

/// 功能
/// - 条件不满足就会退出
void test_check(int argc,char*  argv[]);

/// vlog
/// - 自定义程序输出的log级别
void test_VLOG(int argc,char*  argv[]);

/// pcheck
/// - 检查到错误，退出程序，并输出当前的系统错误
void test_PCHECK(int argc,char*  argv[]);

/// syslog输出到syslog
void test_syslog(int argc,char*  argv[]);

/// 指定自动删除log文件的天数
void test_autorm(int argc,char*  argv[]);


int main(int argc, char* argv[]) {
//   test_commonset(argc,argv);
  test_condition(argc,argv);
//    test_condition_debug(argc,argv);
//    test_check(argc,argv);
//    test_VLOG(argc,argv);
//    test_PCHECK(argc,argv);
//    test_syslog(argc,argv);

}

void test_commonset(int argc,char*  argv[]){
  //FLAGS_log_dir = "/home/sxy/Github/cpp/glog_test/build/build/log";
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "file";
  // Most flags work immediately after updating values.
  FLAGS_logtostderr = 1;
  FLAGS_minloglevel=google::GLOG_INFO;

  LOG(INFO) << "stderr";
  FLAGS_logtostderr = 0;
  // This won’t change the log destination. If you want to set this
  // value, you should do this before google::InitGoogleLogging .
  //FLAGS_log_dir = "/some/log/directory";
  LOG(INFO) << "the same file";

}

void test_condition(int argc,char*  argv[]){
  //  FLAGS_log_dir = "/home/root"  ;



  /// log文件输出路径，若路径错误则报错
  /// 若不指定输出文件夹，则输出到/tmp
//  FLAGS_log_dir = "./"  ;
  FLAGS_log_dir = "/home/sxy/Github/cpp/glog_test/build/build"  ;
//FLAGS_alsologtostderr

  /// 1. 该语句只在InitGoogleLogging使用后生效
  /// 2. 默认false状态，即不输出到标准输出
  /// 3. 对于LOG(ERROR) 的信息总是会显示，不受log的影响
  /// 4. 设置FLAGS_logtostderr = true后，不会保存导本地文件
  ///
//  FLAGS_logtostderr = true;

  /// 1. 设置后会输出标准错误输出。不影响输出到本地
  FLAGS_alsologtostderr=true;

//  FLAGS_minloglevel=google::GLOG_INFO;

//  /// 1. 不同等级的log为显示不同的颜色
//  FLAGS_colorlogtostderr = true;


  /// 1. 当该语句注释后，会打印到标准输出,不产生log文件
  /// 2. 当该语句使用后，不输出到标准输出
  google::InitGoogleLogging(argv[0]);


  int num_cookies=1;
  LOG_IF(INFO, num_cookies > 10) <<"num_cookies:"<<num_cookies<< " Got lots of cookies";
  num_cookies=100;
  LOG_IF(INFO, num_cookies > 10) <<"num_cookies:"<<num_cookies<< " Got lots of cookies";


  for (int times=0;times<100;times++) {
    /// log every some times
    LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
    LOG_EVERY_N(INFO, 5) << "Got the " << google::COUNTER << "th cookie";

    LOG(INFO)  << "Got the " << google::COUNTER << "th cookie";
    LOG(INFO)  << "Got the " << "th cookie";

  }


  /// log first some times
  LOG(INFO) << "===log first some times start===";
  for (int times=0;times<100;times++) {
    LOG_FIRST_N(INFO, 20) << "Got the " << google::COUNTER << "th cookie";
  }
  LOG(INFO) << "===log first some times end===";

  /// LOG_IF_EVERY_N
  LOG(INFO) << "===LOG_IF_EVERY_N start===";

  for (int times=0;times<100;times++) {
    /// log every some times
    LOG_IF_EVERY_N(INFO, (times*100 > 1024), 10) << "Got the " << google::COUNTER
                                                 << "th big cookie>"
                                                 <<"times:"<<times;

  }
  LOG(ERROR) << "===LOG_IF_EVERY_N end===";

  google::ShutdownGoogleLogging();


}

void test_condition_debug(int argc,char*  argv[]){
  //FLAGS_log_dir = "/home/sxy/Github/cpp/glog_test/build/build/log";
  FLAGS_logtostderr = 1;

  google::InitGoogleLogging(argv[0]);

  int num_cookies=1;
  DLOG_IF(INFO, num_cookies > 10) <<"num_cookies:"<<num_cookies<< " Got lots of cookies";
  num_cookies=100;
  DLOG_IF(INFO, num_cookies > 10) <<"num_cookies:"<<num_cookies<< " Got lots of cookies";


  for (int times=0;times<100;times++) {
    /// DLOG every some times
    DLOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
    DLOG_EVERY_N(INFO, 5) << "Got the " << google::COUNTER << "th cookie";

    DLOG(INFO)  << "Got the " << google::COUNTER << "th cookie";
    DLOG(INFO)  << "Got the " << "th cookie";

  }
  //DLOG

  //  /// DLOG first some times
  //  DLOG(INFO) << "===DLOG first some times start===";
  //  for (int times=0;times<100;times++) {
  //    DLOG_FIRST_N(INFO, 20) << "Got the " << google::COUNTER << "th cookie";
  //  }
  //  DLOG(INFO) << "===DLOG first some times end===";

  /// DLOG_IF_EVERY_N
  DLOG(INFO) << "===DLOG_IF_EVERY_N start===";

  for (int times=0;times<100;times++) {
    /// DLOG every some times
    DLOG_IF_EVERY_N(INFO, (times*100 > 1024), 10) << "Got the " << google::COUNTER
                                                  << "th big cookie>"
                                                  <<"times:"<<times;
  }
  DLOG(INFO) << "===DLOG_IF_EVERY_N end===";

}

void test_check(int argc,char*  argv[]){
  //FLAGS_log_dir = "/home/sxy/Github/cpp/glog_test/build/build/log";
  FLAGS_logtostderr = 1;

  google::InitGoogleLogging(argv[0]);

  //  /// 不成立就会退出
  //  CHECK(1 == 4) << "Write failed!";

  //  /// 为true就会退出
  //  /// 1, 2不退出
  //  /// 2, 2退出
  //  CHECK_NE(2, 2) << ": The world must be ending!";

  //  /// 不相等就会退出
  //  /// std::string("abc")[1], 'b' 不退出
  //  /// std::string("abc")[0], 'b'
  //  CHECK_EQ(std::string("abc")[0], 'b');

  /// 在进行指针的判断时，需要static_cast<>()进行类型的强制转换
  //  CHECK_EQ(some_ptr, static_cast<SomeType*>(NULL));

  void* some_ptr=NULL;
  CHECK_NOTNULL(some_ptr);
  //  some_ptr->DoSomething()

}

void test_VLOG(int argc,char*  argv[]){
  //FLAGS_log_dir = "/home/sxy/Github/cpp/glog_test/build/build/log";
  FLAGS_logtostderr = 1;

  google::InitGoogleLogging(argv[0]);

  VLOG(1) << "I’m printed when you run the program with --v=1 or higher";
  VLOG(2) << "I’m printed when you run the program with --v=2 or higher";
  //Verbose level condition macros VLOG_IF, VLOG_EVERY_N and VLOG_IF_EVERY_N behave analogous to LOG_IF, LOG_EVERY_N, LOF_IF_EVERY, but accept a numeric verbosity level as opposed to a severity level.
  if (VLOG_IS_ON(2)) {
    // do some logging preparation and logging
    // that can’t be accomplished with just VLOG(2) << ...;

  }
}


void test_PCHECK(int argc,char*  argv[]){
  //FLAGS_log_dir = "/home/sxy/Github/cpp/glog_test/build/build/log";
  FLAGS_logtostderr = 1;

  google::InitGoogleLogging(argv[0]);
  ///同时输出error的原因 类perror
  PCHECK(write(1, NULL, 2) >= 0) << "Write NULL failed";

}

void test_syslog(int argc,char*  argv[]){
  SYSLOG(INFO)<<"INFO GLOG SYSLOG";
  SYSLOG_IF(INFO,true)<<"INFO GLOG SYSLOG";

  for (int times=0;times<100;times++) {
    /// log every some times
    SYSLOG_EVERY_N(INFO,10)<<"INFO GLOG SYSLOG_EVERY_N:"<<"times>"<<times;

  }

}

void test_autorm(int argc,char*  argv[]){
  // google::EnableLogCleaner(3); // keep your logs for 3 days
  //
  // google::DisableLogCleaner();

}
