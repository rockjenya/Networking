#define _CRT_SECURE_NO_WARNINGS
#ifndef _SERVER_H_
#define _SERVER_H_
//if it's WINDOWS OS
#ifdef _WIN32
	#include <ws2tcpip.h>
	#include <WinSock2.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>
	#pragma comment (lib, "ws2_32.lib")

	#define PORT "4411"
	#define MAXLEN 100
	//to give new thread information
	typedef struct
	{
		SOCKET sock;
		int con_count;
	}forclient;
	//func for creating socket and binding it to port
	int start_serv(SOCKET* listen_sock);
	//fuction for new thread where i saving mouse activiti into file
	DWORD WINAPI save_mouse_pos(void* arg);
	//fuction for creating new thread
	void thread_create(SOCKET sock, int con_count);
#endif
//if it's linux os
#ifdef linux
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <string.h>
	#include <netdb.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <pthread.h>
	//to give new thread information
	typedef struct
	{
		int sock;
		int con_count;
	}forclient;
	//func for creating socket and binding it to port
	int start_serv(int* listen_sock);
	//fuction for new thread where i saving mouse activiti into file
	void* save_mouse_pos(void* arg);
	//fuction for creating new thread
	void thread_create(int sock, int con_count);
#endif

#endif
