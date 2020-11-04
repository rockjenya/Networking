#include "server.h"

int main(void)
{
//if it's WINDOWS OS
#ifdef _WIN32

    WSADATA wsaDATA;
    WORD ver = MAKEWORD(2, 2);
    WSAStartup(ver, &wsaDATA);

    //Declaration sokets
    SOCKET listen_sock, sock;

#endif
//if it's linux OS
#ifdef linux
    //Declaration sokets
    int listen_sock, sock;

#endif

    int con_count = 0; // for counting connection
    struct sockaddr_storage their_info; //save info about client
    socklen_t addr_size = sizeof(their_info);
    //creating socket, binding to potr
    if (start_serv(&listen_sock) == -1)
    {
        printf("Error: start_serv\n");
    }
    //listen for new client connection
    listen(listen_sock, SOMAXCONN);
    printf("Server waiting for new connection ... ... ...\n");
    while (1)
    {
        //create new soket if connection succesfull
        if ((sock = accept(listen_sock, (struct sockaddr*)&their_info, &addr_size)) == -1)
        {
            printf("Error: accept\n");
            continue;
        }
        con_count++;
        //creating new thread for new client
        thread_create(sock, con_count);
    }
//if it's WINDOWS OS
#ifdef _WIN32
    closesocket(listen_sock); //close listening socket
#endif
//if it's linux OS
#ifdef linux
    close(listen_sock); //close listening socket
#endif

    return 0;
}
