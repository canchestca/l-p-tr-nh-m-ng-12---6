// Client2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <wS2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //phan giai n=ten mien
    addrinfo* info;
    SOCKADDR_IN addr;
    int result = getaddrinfo("hust.edu.vn", "http", NULL, &info);
    if (result != 0) {
        printf("khong phan giai ten mien");
        return 1;
    }
    //phan giai ten mien thanh cong
    memcpy(&addr , info->ai_addr, info->ai_addrlen);
    printf("dia chi IP : %s", inet_ntoa(addr.sin_addr));

    // ket noi den server

}

