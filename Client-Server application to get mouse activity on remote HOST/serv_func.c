#include "server.h"
//if it's windows OS
#ifdef _WIN32
//creating socket and binding
int start_serv(SOCKET* listen_sock)
{
    struct addrinfo hint, * servinfo = NULL;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(NULL, "4411", &hint, &servinfo) == -1)
    {
        printf("Error: getaddrinfo()\n");
        return -1;
    }

    if ((*listen_sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        printf("Error: socket()\n");
        return -1;
    }

    if (bind(*listen_sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        printf("Error: bind()\n");
        closesocket(*listen_sock);
        return -1;
    }

    freeaddrinfo(servinfo);
    return 0;
}
//reciving massage from clietn and saving mouse activity into file
DWORD WINAPI save_mouse_pos(void* arg)
{
    forclient* ptr = (forclient*)arg;
    char buf[1000];
    int num;

    char file_name[18];
    memset(file_name, 0, 18);

    sprintf_s(file_name, 18, "client_%d.txt", ptr->con_count);
    FILE* buffer = fopen(file_name, "w"); //open file

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        // reciving massage
        if ((num = recv(ptr->sock, buf, sizeof(buf), 0)) <= 0)
        {
            printf("Client disconected!\n");
            printf("Server waiting for new connection ... ... ...\n");
            break;
        }

        printf("%s\n", buf);
        fprintf(buffer, "%s\n", buf); // saving into file
    }

    fclose(buffer); //close file
    closesocket(ptr->sock); // close socket
    free(arg);

    return 0;
}
#endif
//if it's linux os
#ifdef linux
//creating socket and binding
int start_serv(int* listen_sock)
{
    struct addrinfo hint, * servinfo;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, "4411", &hint, &servinfo) != 0)
    {
        printf("Error: getaddrinfo()\n");
        exit(1);
    }

    if ((*listen_sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        printf("Error: socket()\n");
    }

    int yes = 1;
    if (setsockopt(*listen_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        printf("Error: setsockopt\n");
        exit(1);
    }

    if (bind(*listen_sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        printf("Error: bind\n");
        close(*listen_sock);
        return -1;
    }

    freeaddrinfo(servinfo);
    return 0;
}
//reciving massage from clietn and saving mouse position into file
void* save_mouse_pos(void* arg)
{
    forclient* ptr = (forclient*)arg;
    char buf[1000];
    int num;

    char file_name[18];
    memset(file_name, 0, 18);

    snprintf(file_name, 18, "client_%d.txt", ptr->con_count);

    FILE* buffer = fopen(file_name, "w");//open file

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        //reciving massage from client
        if ((num = recv(ptr->sock, buf, sizeof(buf), 0)) <= 0)
        {
            printf("Client disconected!\n");
            printf("Server waiting for new connection ... ... ...\n");
            break;
        }
        printf("%s\n", buf);
        fprintf(buffer, "%s\n", buf);//saving mouse position into file
    }

    fclose(buffer); //close file
    close(ptr->sock); //close socket

    free(arg);
    return NULL;
}

#endif
