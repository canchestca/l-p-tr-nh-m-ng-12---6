// SimpleServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>


#pragma comment(lib , "ws2_32.lib")
 //Ví dụ ứng dụng server đơn giản
typedef struct {
	int mssv;
	char hoten[32];
	char lop[8];
	float diemthi;
} SINHVIEN;
int main()
{
	//khai báo thư viện winsock
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//tạo đối tượng socket
	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//khai báo địa chỉ server
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8000);

	// gán địa chỉ vào socket 
	bind(listener, (SOCKADDR*)&addr, sizeof(addr));

	// chuyển sang trạng thái kết nối 
	listen(listener, 5);
	printf("dang cho ket noi ... \n");

	// chờ kết nối đến server
	//TH1 : không quan tâm đến địa chỉ client

	//SOCKET client = accept(listener, NULL, NULL);
	//printf("chap nhan ket noi mơi : %d", client);
	//TH2 cần biết địa chỉ của client
	SOCKADDR_IN clientAddr;
	int clientAddrLen =sizeof(clientAddr);
	SOCKET client = accept(listener, (SOCKADDR*)&clientAddr, &clientAddrLen);
	printf("chap nhan ket noi mơi : %d", client);
	printf("dia chi client : %s \n", inet_ntoa(clientAddr.sin_addr));

	////gửi chuoi kí tự
	//const char* str = "Hello World";
	//int r = send(client, str, strlen(str), 0);
	//printf("Result : %s \n", r);
	//if (r ==SOCKET_ERROR)
	//{
	//	r = WSAGetLastError();
	//	printf("Error code : %d\n" , r);
	//}


	//gửi buffer chứa dữ liệu
	/*char buf[256];
	for (int i = 0; i < 10; i++)
	
		buf[i] = i + 1;

	
	///*send(client, buf, 10, 0);*/
	//float f = 3.1415926 ;
	//send(client, (char*)&f, sizeof(f) , 0);*/
	

	/*SINHVIEN sv;
	send(client, (char*)&sv, sizeof(sv), 0);*/

	//hàm recv nhận dữ liệu
	printf("dang chp du lieu\n");
	char buf[256];
	int r;
	while (true)
	{
		int r = recv(client, buf, sizeof(buf), 0);
		printf("Result : %d \n", r);
		if (r<=0)
			break;
		
		if (r < sizeof(buf))
			buf[r] = 0;
		

		
		//them kí tự kết thúc xau
		//buf[r] = 0;
		printf("Data: %f\n", buf);

	}
	
	
	return 0;
}

