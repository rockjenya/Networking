#include "client.h"
//if it's WINDOWS OS
#ifdef _WIN32
//func for making socket and connecting to server
int connect_to_serv(SOCKET* sock, const char* addr, const char* PORT)
{
    struct addrinfo hint, * servinfo = NULL;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(addr, PORT, &hint, &servinfo) == -1)
    {
        printf("Error: getaddrinfo()\n");
        return -1;
    }
    if ((*sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        printf("Error: socket()\n");
        return -1;
    }
    if (connect(*sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        printf("Error: connect()\n");
        return -1;
    }
    freeaddrinfo(servinfo);
    return 0;
}
//func for getting mouse activity and saving it for next sending
void send_mouse_position(SOCKET* sock, int max_count)
{
    int count = 0;
    char answer;
    char message[MAXLEN];
    while (count <= max_count)
    {

        get_mouse_position(message, MAXLEN);//getting mouse activity into message for sending
        //sending mouse activity to server
        if ((send(*sock, message, strlen(message) + 1, 0)) == -1)
        {
            printf("Error: send()\n");
            return;
        }
        Sleep(500);
        if (count == max_count)
        {
            answer = '\0';
            printf("Keep?(y to keep, other to stop)\n>:");
            scanf("%c", &answer);
            while (getchar() != '\n')
                ;
            if (answer == 'y' || answer == 'Y')
                count = 0;
        }
        count++;
    }
}
#endif
//if it's LINUX OS
#ifdef linux
//func for making socket and connecting to server
int connect_to_serv(int* sock, const char* addr, const char* PORT)
{
    struct addrinfo hint, * servinfo = NULL;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(addr, PORT, &hint, &servinfo) != 0)
    {
        printf("Error: getaddrinfo()\n");
    }
    if ((*sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        printf("Error: socket()\n");
    }

    if (connect(*sock, servinfo->ai_addr, servinfo->ai_addrlen))
    {
        printf("Error: connect()\n");
        close(*sock);
        return -1;
    }
    freeaddrinfo(servinfo);
    return 0;
}
//func for getting mouse position and saving it for next sending
void send_mouse_position(int* sock, int max_count)
{
    char buffer[1024];
    int count = 0;
    char answer;

    while (count <= max_count)
    {
        int n = get_mouse_position(buffer, sizeof(buffer)); //getting mouse position to buffer

        char message[n];
        //prepare mouse position into messagefor sending
        format_to_send(buffer, message, n);

        printf("Message > %s\n", message);
        //sending mouse position to server
        if (send(*sock, message, strlen(message), 0) == -1)
        {
            printf("Error: send()\n");
        }
        usleep(500000);
        if (count == max_count)
        {
            answer = '\0';
            printf("Keep?(y to keep, other to stop)\n>:");
            scanf("%c", &answer);
            while (getchar() != '\n')
                ;
            if (answer == 'y' || answer == 'Y')
                count = 0;
        }
        count++;
    }
}
#endif
