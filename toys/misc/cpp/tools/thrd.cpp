#include <pthread.h>
#include <iostream>

using std::cout;

void* doit(void *arg)
{
    while (1) cout << "wusup\n";
    return NULL;
}

pthread_t id;
int main()
{
    void *status;

    pthread_create(&id, 0, doit, NULL);
    if (pthread_join(id, &status)) {
        pthread_cancel(id);
    }
    return 0;
}
