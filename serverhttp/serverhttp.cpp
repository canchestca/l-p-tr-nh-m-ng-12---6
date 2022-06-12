// Tao ung dung server theo giao thuc TCP nhan cau chao tu client
// Sau do nhap du lieu tu ban phim va gui cho client

#include <stdio.h>

#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);


    while (true)
    {
        SOCKET client = accept(listener, NULL, NULL);
        char buf[2048];
        int r = recv(client, buf, sizeof(buf), 0);
        printf("DATA: \n%s\n" , buf);

        ////tra lai hello world
        //const char* http = "HTTP/1.1 200 OK\nContent-type: text/html\n\n<html><body><h1>Hello world</h1></body></htm>";
        //send(client, http, strlen(http), 0);
        //closesocket(client);
        //const char* header = "HTTP/1.1 200 OK\nContent-type: image/jpeg\n\n";
        //send(client , header , strlen (header) , 0);
        //// gửi dữ liệu file ảnh

    }
    return 0;

}

