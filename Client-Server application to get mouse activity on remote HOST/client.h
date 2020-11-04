#define _CRT_SECURE_NO_WARNINGS
#ifndef _CLIENT_H_
#define _CLIENT_H_

#ifdef _WIN32
	#include <ws2tcpip.h>
	#include <WinSock2.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <Windows.h>
	#include <errno.h>

	#pragma comment (lib, "ws2_32.lib")

	#define MAXLEN 100

	//func for making socket and connecting to server
	int connect_to_serv(SOCKET* sock, const char* addr, const char* PORT);
	//func for getting mouse activity and saving it for next sending
	void get_mouse_position(char* message, int len);
	//func for sending mouse activity to server
	void send_mouse_position(SOCKET* sock, int max_count);
	//User interface
	void UI(SOCKET *sock);
#endif

#ifdef linux
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <netdb.h>
	#include <string.h>
	#include <ctype.h>

	//func making socket and connecting to clieng
	int connect_to_serv(int* sock, const char* addr, const char* PORT);
	//func for getting mouse position and save it on buffer
	int get_mouse_position(char* buffer, int size_buf);
	//funcion send already-formated mouse position
	void send_mouse_position(int* sock, int max_count);
	//func to format mouse position from buffer to messag to next sending
	void format_to_send(char* buf, char* mssg, int mssg_len);
	//User interface
	void UI(int* sock);
#endif

#endif
