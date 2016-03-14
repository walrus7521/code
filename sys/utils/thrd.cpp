#include <iostream>
#include <cstdlib>
#include <pthread.h>

// http://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm
// g++ thrd.cpp -lpthread

using namespace std;

class MutexLocker
{
    pthread_mutex_t &mutex;
    public:
    MutexLocker(pthread_mutex_t &mutex):mutex(mutex)
    {
        //pthread_mutex_lock(&this->mutex);
        if(pthread_mutex_lock(&this->mutex)!=0)
            throw std::runtime_error("mutex locking filed");
    }
    ~MutexLocker(void)
    {
        //pthread_mutex_unlock(&this->mutex);
        if(pthread_mutex_unlock(&this->mutex)!=0)
            throw std::runtime_error("mutex unlocking filed");
    }
};

class DataCenter
{
public:    
    DataCenter(){}
    ~DataCenter(){}
    DataCenter* getInstance()
    {
        //MutexLocker locker(DataCenter::mutex_);
        if (!instance_flag_) {
            cout << "data center...\n";
            pthread_mutex_init(&mutex_,0);
            MutexLocker locker(DataCenter::mutex_);
            instance_ = new DataCenter();
            instance_flag_ = true;
        }
        return instance_;
    }
private:
    DataCenter *instance_;
    pthread_mutex_t mutex_;
    bool instance_flag_;
};

#if 0
class Singleton 
{
    static Singleton *single;
    static bool instanceFlag;
    Singleton() {}
    static pthread_mutex_t m_;

  public:

    static Singleton* getInstance()
    {
        //std::lock_guard<std::mutex> lock(m_);
        //pthread_mutex_lock(&m_);   
        if(!instanceFlag)
        {
            single = new Singleton();
            instanceFlag = true;
        }
        return single;
    }
    ~Singleton() {
        instanceFlag = false;
    }
};

Singleton* Singleton::single = NULL;
bool Singleton::instanceFlag = false;
pthread_mutex_init(&Singleton::m_,0);

class Singleton2
{
private:
    //Singleton();
    static pthread_mutex_t mutex_;

public:
    Singleton(){  
        cout << "ctor\n"; 
    }
    ~Singleton(){ 
        cout << "dtor\n"; 
    }
    static Singleton& instance()
    {
        static Singleton INSTANCE;
        cout << "singleton\n";
        return INSTANCE;
    }
};
#endif

class Guard {
public:
    Guard() {
        cout << "guard up\n";
        //pthread_mutex_init(&mutex,0);
        //pthread_mutex_lock(&mutex);   
    }
    ~Guard() {
        cout << "guard down\n";
        //pthread_mutex_unlock(&mutex);   
    }
private:
    pthread_mutex_t mutex;
};

Guard g;
#define NUM_THREADS     5
static pthread_mutex_t myMutex;

void *PrintHello2(void *threadid)
{
   //Guard g;
   //Singleton *s;
   //s = Singleton::getInstance();
   //Singleton::getSingletonInstance();
   //DataCenter c;
   //c.getInstance();
   //c.getInstance();
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
   return NULL;
}

void *PrintHello(void *threadid)
{
   pthread_mutex_lock(&myMutex);   
   Guard g;
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_mutex_unlock(&myMutex);   
   pthread_exit(NULL);
}

int main ()
{
   pthread_t threads[NUM_THREADS];
   int rc, i;
   pthread_mutex_init(&myMutex,0);
   for( i=0; i < NUM_THREADS; i++ ){
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   for( i=0; i < NUM_THREADS; i++ ){
       pthread_join(threads[i], NULL);
   }
   pthread_mutex_destroy(&myMutex);   
   pthread_exit(NULL);
}
