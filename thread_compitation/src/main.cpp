#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>

std::mutex __mutex;

void thread_to_do_something(int v_val);

void test_thread_compitation();

/// 多个线程共用同一各线程线程所
/// 测试是否是先被锁住的线程先抢占该锁的所有权


void test_atomic();
class ThreadFunc
{
public:
    void start()
    {
        mydo = true;
        std::cout << "线程函数被启动" << std::endl;
        mT = new std::thread(&ThreadFunc::doT,this,15);
    }
    void stop ()
    {
        std::cout << "线程函数被停止" << std::endl;
        mydo = false;
        mT->join();
    }
    void doT(int a)
    {
        while(mydo)
        {
                    std::cout<<"a:"<<a--<<std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout<<"线程exit"<<std::endl;
    }

private:
  std::thread* mT;
  bool mydo = true;

};

int main(int argc, char* argv[])
{
//  test_thread_compitation();
  test_atomic();

}

void test_atomic()
{
  std::atomic<int> atom_val;
  atom_val.store(1);
  std::cout<<"atom_val:"<<atom_val.load()<<std::endl;
  atom_val++;

  std::cout<<"after atom_val:"<<atom_val.load()<<std::endl;


}



void test_thread_compitation()
{

  std::vector<std::thread*> list_thread;
  int  count_thread=10;
  for(int i=0;i<count_thread;i++)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread *tempthread=new std::thread(thread_to_do_something,i);
    list_thread.push_back(tempthread);
  }

  for (int i=0;i<count_thread;i++) {
    (*list_thread[i]).join();
  }
}

void thread_to_do_something(int v_val)
{
  {
    std::cout<<">"<<v_val<<std::endl;
    std::unique_lock<std::mutex>tmp_lck(__mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"<"<<v_val<<std::endl;
  }

  if (v_val == 0) {
    int  count_thread=10;
    int  count_thread_end=20;

    std::this_thread::sleep_for(std::chrono::microseconds(1));
    std::unique_lock<std::mutex>tmp_lck(__mutex);
    for(int i=count_thread;i<count_thread_end;i++)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout<<"<"<<i<<std::endl;
    }

  }

}
