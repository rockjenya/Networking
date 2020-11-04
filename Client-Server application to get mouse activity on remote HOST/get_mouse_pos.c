#include "client.h"
//if it's WINDOWS OS
#ifdef _WIN32
//function to get mouse activity
void get_mouse_position(char* message, int len)
{
    POINT mouse;
    memset(message, 0, 100);
    GetCursorPos(&mouse);
    sprintf_s(message, len, "%dx%d ", mouse.x, mouse.y);
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        char button[] = "LKM";
        strcat_s(message, 100, button);
    }
    else if (GetAsyncKeyState(VK_RBUTTON))
    {
        char button[] = "RKM";
        strcat_s(message, 100, button);
    }
}
#endif
//if it's LINUX OS
#ifdef linux
//getting mouse position and saving it into buffer
int get_mouse_position(char* buffer, int size_buf)
{
    FILE* lsofFile_p = popen("xdotool getmouselocation", "r");
    int n = 0;
    if (!lsofFile_p)
    {
        return -1;
    }
    char* line_p = fgets(buffer, size_buf, lsofFile_p);
    pclose(lsofFile_p);
    printf("%s\n", buffer);
    for (int i = 0; buffer[i] != 's'; i++)
        n++;
    return n;
}
//formating mouse position to next senging to server
void format_to_send(char* buffer, char* message, int mssg_len)
{
    memset(message, 0, mssg_len);

    for (int i = 0, j = 0; i < (mssg_len - 1); i++)
    {
        if (isdigit(buffer[i]))
        {
            message[j] = buffer[i];
            j++;
        }
        if (isblank(buffer[i]))
        {
            message[j] = 'x';
            j++;
        }
    }
}
#endif
