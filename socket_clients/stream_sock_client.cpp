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

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;

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
    int sock;
    char buf[MAXLEN];
    
    int numbites;
    struct addrinfo hints, *servinfo, *p;
    char s[INET6_ADDRSTRLEN];

    //Set up struck info
    memset(&hints,0,sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    //Use getaddrinfo
    if((getaddrinfo("127.0.0.1",PORT,&hints,&servinfo))!= 0)
    {
        cerr << "Error: getaddrinfo()" << endl;
        return -1;
    }
    //For loop
    for(p = servinfo; p != nullptr; p = p->ai_next)
    {
        //Create socket
        if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            cerr << "Error: soket()" << endl;
            continue;
        }
        //Connect
        if((connect(sock,p->ai_addr,p->ai_addrlen)) == -1)
        {
            cerr << "Error: connect" << endl;
            continue;
        }
        break;
    }
    if(p==nullptr)
    {
        cout << "Error: can`t connect" << endl;
        return 3;
    }
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr*)p->ai_addr), s, sizeof(s));
    cout << "Client connected to " << s << endl;

    //Do-While loop
    while(true)
    {
        memset(buf, 0, MAXLEN);
        char mssg[MAXLEN];
        //recieve massage
        if((numbites = recv(sock,buf,MAXLEN,0))==-1)
        {
            cerr << "Error: recv()" << endl;
            continue;
        }
        //buf[numbites] = '\0';
        cout << "Server> " << string(buf, numbites) << endl;
        //send massage
        cout << "> ";
        cin.getline(mssg,MAXLEN);
        if((send(sock,mssg, strlen(mssg)+1,0))==-1)
        {
            cerr << "Error: send()" << endl;
            continue;
        }
    };

    //close socket
    close(sock);
    return 0;
}
