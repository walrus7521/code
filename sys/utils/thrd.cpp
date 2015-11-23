#include <iostream>
#include <cstdlib>
#include <pthread.h>

// http://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm
// g++ thrd.cpp -lpthread

using namespace std;

#define NUM_THREADS     5
pthread_mutex_t myMutex;

void *PrintHello(void *threadid)
{
   pthread_mutex_lock(&myMutex);   
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_mutex_unlock(&myMutex);   
   pthread_exit(NULL);
}

int main ()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   pthread_mutex_init(&myMutex,0);

   for( i=0; i < NUM_THREADS; i++ ){
      pthread_mutex_lock(&myMutex);   
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
      pthread_mutex_unlock(&myMutex);   
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   for( i=0; i < NUM_THREADS; i++ ){
       //pthread_join(threads[i], NULL);
   }

   pthread_mutex_destroy(&myMutex);   
   pthread_exit(NULL);
}
