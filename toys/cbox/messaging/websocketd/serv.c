#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

// clang -pthread -o serv serv.c

//std::mutex msg_mutex;
//std::string msg;
bool got_msg = false;
static char msg[256];

void *read(void *ptr)
{
  while (true) {
    scanf("%s", msg);
    //std::lock_guard<std::mutex> lock{msg_mutex};
    printf("got message: %s\n", msg);
    got_msg = true;
  }
}

void *write(void *ptr)
{
  while (true) {
    //std::lock_guard<std::mutex> lock{msg_mutex};
    //if (msg.length() > 0) {
    if (got_msg == true) {
        printf("got message: %s\n", msg);
        got_msg = false;
    }
  }
}

int main()
{
    pthread_t reader;
    pthread_t writer;

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    if (pthread_create(&reader, NULL, read, NULL)) {
        fprintf(stderr, "Error creating reader thread\n");
        return 1;
    }
    
    if (pthread_create(&writer, NULL, write, NULL)) {
        fprintf(stderr, "Error creating writer thread\n");
        return 1;
    }
    

    pthread_join(reader, NULL);
    pthread_join(writer, NULL);
    
    return 0;
}

