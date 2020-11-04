#include "client.h"

int main()
{
    //if it's WINDOWS OS
#ifdef _WIN32
    WSADATA wsDATA;
    WORD ver = MAKEWORD(2, 2);
    WSAStartup(ver, &wsDATA);
    //Declaration socket
    SOCKET sock;
#endif
    //if it's LINUX OS
#ifdef linux
    int sock; //Declaration socket
#endif

    UI(&sock);

    return 0;
}
