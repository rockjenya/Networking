#include"server.h"
//if it's windows OS
#ifdef _WIN32
//fuction to create new thread
void thread_create(SOCKET sock, int con_count)
{
    forclient* arg = (forclient*)malloc(sizeof(forclient));
    arg->con_count = con_count;
    arg->sock = sock;
    //creating new thread
    HANDLE thread = CreateThread(NULL, 0, save_mouse_pos, arg, 0, 0);
    if (thread == NULL)
    {
        printf("Error: CreateThread()\n");
        ExitProcess(3);
    }
}
#endif
//if it's linux OS
#ifdef linux
//fuction to create new thread
void thread_create(int sock, int con_count)
{
    forclient* arg = (forclient*)malloc(sizeof(forclient));
    arg->con_count = con_count;
    arg->sock = sock;

    pthread_t thrd;
    //create new thread
    if (pthread_create(&thrd, NULL, save_mouse_pos, arg))
    {
        printf("Error: creating thread\n");
        free(arg);
        return;
    }
    if (pthread_detach(thrd))
    {
        printf("Error: getach thread\n");
        return;
    }
}
#endif
