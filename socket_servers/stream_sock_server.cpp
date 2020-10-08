#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include <string>

#define PORT "53000"
#define MAXLEN 100
#define BACKLOG 10

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;

void *get_in_addr(struct sockaddr *sa)
{
 if (sa->sa_family == AF_INET) {
 return &(((struct sockaddr_in*)sa)->sin_addr);
 }
 return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main()
{
    //Variables
    int listen_sock, sock;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];

    char buf[MAXLEN];
    int numbites;

    //Fill struckt data
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((getaddrinfo(NULL,PORT,&hints,&servinfo))!=0)
    {
        cerr << "Error: getaddrinfo()" << endl;
        return 2;
    }
    //For loop
    
    for(p = servinfo; p != nullptr; p = p->ai_next)
    {
        //Create socket
        if((listen_sock = socket(p->ai_family,p->ai_socktype, p->ai_protocol)) ==-1)
        {
            cerr << "Error: can create socket" << endl;
        }
        if(setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            cerr << "Error: setsockopt" << endl;
            exit(1);
        }
        //Bind socket
        if((bind(listen_sock,p->ai_addr, p->ai_addrlen)) == -1)
        {
            close(listen_sock);
            cerr << "Error: bind()" << endl;
            continue;
        }
    }
    freeaddrinfo(servinfo);
    //Listen socket
    if((listen(listen_sock,BACKLOG)) == -1)
    {
        cerr << "Error: listen()" << endl;
        exit(1);
    }
    cout << "Sever is waiting for connection... ... ..." << endl;
    //While loop
    //Accept connection
    sin_size = sizeof(their_addr);
    if((sock = accept(listen_sock, (struct sockaddr*)&their_addr,&sin_size)) == -1)
    {
        cerr << "Error: accept()" << endl;
        return -3;
    }
    //Show our connection
    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr*)&their_addr), s, sizeof(s));
    cout << "Server connected with " << s << endl;

    while(true)
    {
        memset(buf,0,MAXLEN);
        char mssg[MAXLEN];
        cout << "> ";
        cin.getline(mssg, MAXLEN);
        
        //Send massage
        if(send(sock,mssg,strlen(mssg)+1,0) == -1)
        {
            cerr << "Error : send()" << endl;
            continue;
        }
        //Recieve massage
        
        if((numbites = recv(sock,buf,MAXLEN,0)) == -1)
        {
            cerr << "Error: recv()" << endl;
            continue;
        }
        //buf[numbites] = '\0';
        if(numbites == 0)
        {
            cout << "Clietn disconected!" << endl;
        }
        cout << "Clien> " << string(buf, numbites) << endl;
    }
    //Close soket
    close(sock);
    return 0;
}