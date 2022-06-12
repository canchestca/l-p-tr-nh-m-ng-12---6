// C winsock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>


#pragma comment(lib , "ws2_32.lib")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    //khai báo địa chỉ server cần kết nối
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);
    //phân giải tên miền
    addrinfo* info;
    int result = getaddrinfo("hust.edu.vn", "http", NULL, &info);
    if (result == 0) {
        SOCKADDR_IN addr;
        memcpy(&addr, info->ai_addr, info->ai_addrlen);
        printf("Dia chi IP ; %s", inet_ntoa(addr.sin_addr));
    }
    else
    {
        printf("khong phan giai duoc ten mien");
    }


    WSACleanup();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
