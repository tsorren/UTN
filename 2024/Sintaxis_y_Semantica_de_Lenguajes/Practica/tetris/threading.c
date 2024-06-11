#include <stdio.h>
#include <pthread.h>

#include <windows.h>

void *waitFunc(void *condition)
{
    unsigned int *ptr = (unsigned int *)condition;

    while(*(unsigned int *)condition)
    {
        Sleep(1000);
        printf("%d\n", *ptr);
    }
    return NULL;
}

void *modifyFunc(void *condition)
{
    unsigned int *ptr = (unsigned int *)condition;
    Sleep(3000);
    *ptr = 0;

    return NULL;
}

int main(void)
{
    pthread_t wait_thread;
    pthread_t modify_thread;
    int condition = 1;


    pthread_create(&wait_thread, NULL, waitFunc, (void*) &condition);
    pthread_create(&modify_thread, NULL, modifyFunc, (void*) &condition);


    pthread_join(wait_thread, NULL);
    pthread_join(modify_thread, NULL);
    return 0;
}