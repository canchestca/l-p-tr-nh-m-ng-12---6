#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)
DWORD WINAPI ClientThread(LPVOID lpParam)
{
    SOCKET client = *(SOCKET*)lpParam;
    OVERLAPPED overlapped;
    WSAEVENT newEvent = WSACreateEvent();
    overlapped.hEvent = newEvent;
    WSABUF databuf;
    char buf[256];
    databuf.buf = buf;
    databuf.len = sizeof(buf);
    DWORD bytesReceived, flags = 0;
    int ret;
    while (1)
    {
        ret = WSARecv(client, &databuf, 1, &bytesReceived,
            &flags, &overlapped, NULL);
        if (ret == SOCKET_ERROR)
        {
            ret = WSAGetLastError();
            if (ret != WSA_IO_PENDING)
            {
                // Loi khac, khong phai dang cho du lieu
                break;
            }
        }
        ret = WSAWaitForMultipleEvents(1, &newEvent, FALSE, WSA_INFINITE, FALSE);
        if (ret == WSA_WAIT_FAILED)
        {
            break;
        }
        WSAResetEvent(newEvent);
        WSAGetOverlappedResult(client, &overlapped, &bytesReceived, FALSE, &flags);
        if (bytesReceived == 0)
        {
            break;
        }
        buf[bytesReceived] = 0;
        printf("Du lieu nhan duoc: %s\n", buf);
    }
}
int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);
    while (1)
    {
        SOCKET client = accept(listener, NULL, NULL);
        printf("New client: %d\n", client);
        CreateThread(0, 0, ClientThread, &client, 0, 0);
    }

}