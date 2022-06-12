#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)
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
    WSAEVENT newEvent = WSACreateEvent();
    WSAEventSelect(listener, newEvent, FD_ACCEPT);
    WSAEVENT events[64];
    SOCKET sockets[64];
    int numEvents = 0;
    events[numEvents] = newEvent;
    sockets[numEvents] = listener;
    numEvents++;
    while (1)
    {
        int ret = WSAWaitForMultipleEvents(numEvents, events, FALSE, 5000, FALSE);
        if (ret == WSA_WAIT_FAILED)
        {
            break;
        }
        if (ret == WSA_WAIT_TIMEOUT)
        {
            printf("Het gio!!!");
            continue;
        }
        int index = ret - WSA_WAIT_EVENT_0;
        for (int i = index; i < numEvents; i++)
        {
            ret = WSAWaitForMultipleEvents(1, &events[i], FALSE, 0, FALSE);
            if (ret == WSA_WAIT_FAILED)
            {
                continue;
            }
            if (ret == WSA_WAIT_TIMEOUT)
            {
                continue;
            }
            WSANETWORKEVENTS networkEvents;
            WSAEnumNetworkEvents(sockets[i], events[i], &networkEvents);
            WSAResetEvent(events[i]);
            if (networkEvents.lNetworkEvents & FD_ACCEPT)
            {
                if (networkEvents.iErrorCode[FD_ACCEPT_BIT])
                {
                    // Xu ly loi
                    // Chuyen sang kiem tra event tiep theo
                    continue;
                }
                SOCKET client = accept(sockets[i], NULL, NULL);
                printf("Co ket noi moi: %d\n", client);
                // Kiem tra so luong phan tu trong mang events
                if (numEvents == 64)
                {
                    printf("Da vuot qua so luong ket noi.\n");
                    closesocket(client);
                    continue;
                }
                newEvent = WSACreateEvent();
                WSAEventSelect(client, newEvent, FD_READ | FD_CLOSE);
                events[numEvents] = newEvent;
                sockets[numEvents] = client;
                numEvents++;
            }
            if (networkEvents.lNetworkEvents & FD_READ)
            {
                if (networkEvents.iErrorCode[FD_READ_BIT])
                {
                    // Xu ly loi
                    // Chuyen sang kiem tra event tiep theo
                    continue;
                }
                // Doc du lieu
                char buf[256];
                ret = recv(sockets[i], buf, sizeof(buf), 0);

                // In ra man hinh
                buf[ret] = 0;
                printf("Du lieu nhan duoc tu %d: %s\n", sockets[i], buf);

            }
            if (networkEvents.lNetworkEvents & FD_CLOSE)
            {
                if (networkEvents.iErrorCode[FD_CLOSE_BIT])
                {
                    // Xu ly loi
                    // Chuyen sang kiem tra event tiep theo
                    closesocket(sockets[i]);
                    continue;
                }
                printf("Ket noi %d bi dong.\n", sockets[i]);
                closesocket(sockets[i]);
            }
        }

    }
    closesocket(listener);
    WSACleanup();
}