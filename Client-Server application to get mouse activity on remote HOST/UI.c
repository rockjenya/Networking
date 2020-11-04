#include "client.h"

void menu()
{
    printf("\t\tMenu:\n");
    printf("1.Set default number of sending mouse activity\n"
        "2.Set connection address and port other than default(127.0.0.1 and 4411)\n"
        "3.Connect to server\n"
        "4.Quit\n");
}
#ifdef _WIN32
void UI(SOCKET* sock)
#endif
#ifdef linux
void UI(int *sock)
#endif
{
    int choise = 0;
    int max_count = 50;
    char default_p[] = "4411";
    char default_a[] = "127.0.0.1";

    char address[14];
    memset(address, 0, 14);
    snprintf(address, 14, "%s", default_a);

    char PORT[8];
    memset(PORT, 0, 8);
    snprintf(PORT, 8, "%s", default_p);
    while (choise != 4)
    {
        menu();
        printf(">:");
        scanf("%d", &choise);
        while (getchar() != '\n')
            ;
#ifdef _WIN32
        system("cls");
#endif

#ifdef linux
        system("clear");
#endif

        switch (choise)
        {
        case 1:
            printf("Set default number of sending mouse activity\n");
            printf(">:");
            scanf("%d", &max_count);
            while (getchar() != '\n')
                ;
#ifdef _WIN32
            system("cls");
#endif

#ifdef linux
            system("clear");
#endif

            break;
        case 2:
            printf("Where do you want to connect?\n");
            printf("Write address: ");

            memset(address, 0, 20);
            scanf("%s", address);
            while (getchar() != '\n')
                ;
            printf("Write connection port: ");
            memset(PORT, 0, 8);
            scanf("%s", PORT);
            while (getchar() != '\n')
                ;
#ifdef _WIN32
            system("cls");
#endif

#ifdef linux
            system("clear");
#endif

            break;
        case 3:
            if (connect_to_serv(sock, address, PORT) == -1)
            {
                printf("Error: connect to server\n");
            }
            send_mouse_position(sock, max_count);

#ifdef _WIN32
            system("cls");
#endif

#ifdef linux
            system("clear");
#endif

            //if it's WINDOWS OS
#ifdef _WIN32
            closesocket(*sock); //close socket
#endif
//if it's LINUX OS
#ifdef linux
            close(*sock); //close socket
#endif
            break;
        case 4:
            exit(1);
            break;
        default:
            exit(1);
            break;
        }
    }
}
