//#include "opencv2/opencv.hpp"
//#include <WinSock2.h>
//#include <Windows.h>
//#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
//#pragma warning(disable : 4996)
//
////待传输图像默认大小为 640*480，可修改
//#define IMG_WIDTH 640	// 需传输图像的宽
//#define IMG_HEIGHT 480	// 需传输图像的高
////默认格式为CV_8UC3
//#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/32 
//using namespace cv;
//
//
//struct sentbuf {
//	char buf[BUFFER_SIZE];
//	int flag;
//};
//sentbuf data;
//void sendMat(SOCKET sockClient, Mat image);
//
//int main(int, char**)
//{
//	VideoCapture cap(0); // open the default camera
//	if (!cap.isOpened())  // check if we succeeded
//		return -1;
//	Mat frame;
//	//初始化 DLL
//	WSADATA wsaData;
//	::WSAStartup(MAKEWORD(2, 0), &wsaData);
//	//创建套接字
//	SOCKET servSock = ::socket(AF_INET, SOCK_STREAM, 0);
//
//	//绑定套接字
//	sockaddr_in sockAddr;
//	sockAddr.sin_family = AF_INET;
//	sockAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");
//	sockAddr.sin_port = htons(1234);
//	::bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
//	//进入监听状态
//	listen(servSock, 5);
//	//接收客户端请求
//	SOCKADDR clntAddr;
//	int nSize = sizeof(SOCKADDR);
//	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
//	std::cout << "linked\n";
//	for (;;)
//	{
//		cap >> frame; // get a new frame from camera
//		sendMat(clntSock, frame);
//	}
//	// the camera will be deinitialized automatically in VideoCapture destructor
//
//	//关闭套接字
//	closesocket(clntSock);
//	closesocket(servSock);
//
//	//终止 DLL 的使用
//	WSACleanup();
//	return 0;
//}
//void sendMat(SOCKET sockClient, Mat image) {
//	for (int k = 0; k < 32; k++) {
//		int num1 = IMG_HEIGHT / 32 * k;
//		for (int i = 0; i < IMG_HEIGHT / 32; i++) {
//			int num2 = i * IMG_WIDTH * 3;
//			uchar* ucdata = image.ptr<uchar>(i + num1);
//			for (int j = 0; j < IMG_WIDTH * 3; j++) {
//				data.buf[num2 + j] = ucdata[j];
//			}
//		}
//		if (k == 31)
//			data.flag = 2;
//		else
//			data.flag = 1;
//		send(sockClient, (char *)(&data), sizeof(data), 0);
//	}
//}




//reference:https://blog.csdn.net/bulreed/article/details/19161103?utm_source=blogxgwz9

////UDP
//#include<stdio.h>
//#include<WinSock2.h>
//#include <WS2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")
//
//void main()
//{
//	SOCKET uiFdSocket;
//	WSADATA wsaData;
//	char szbuffer[1024] = "\0";
//	struct sockaddr_in stServerAddr;
//	struct sockaddr_in stClientAddr;
//	int iAddrlen = sizeof(sockaddr_in);
//
//	/* 调用Windows Sockets DLL,成功后才能使用socket系列函数 */
//	if (0 != WSAStartup(MAKEWORD(2, 1), &wsaData))
//	{
//		printf("Winsock init failed!\r\n");
//		WSACleanup();
//		return;
//	}
//
//	memset(&stServerAddr, 0, sizeof(stServerAddr));
//	memset(&stClientAddr, 0, sizeof(stClientAddr));
//
//	/* 服务器地址 */
//	stServerAddr.sin_family = AF_INET;
//
//	/* 监听端口 */
//	stServerAddr.sin_port = htons(6000);
//	stServerAddr.sin_addr.s_addr = INADDR_ANY;
//
//	/* 服务器端创建socket, 报文模式(UDP)*/
//	uiFdSocket = socket(AF_INET, SOCK_DGRAM, 0);
//
//	/* 绑定端口号 */
//	bind(uiFdSocket, (struct sockaddr*)&stServerAddr, sizeof(sockaddr_in));
//
//	while (true)
//	{
//		printf("waiting client send msg now...\r\n");
//
//		if (SOCKET_ERROR != recvfrom(uiFdSocket, szbuffer, sizeof(szbuffer), 0, (struct  sockaddr*)&stClientAddr, &iAddrlen))
//		{
//			printf("Received datagram from %s--%s\n", inet_ntoa(stClientAddr.sin_addr), szbuffer);
//			sendto(uiFdSocket, szbuffer, sizeof(szbuffer), 0, (struct sockaddr*)&stClientAddr, iAddrlen);
//		}
//
//	}
//
//	closesocket(uiFdSocket);
//	return ;
//}




//TCP
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
	////判断是否输入了端口号
	//if (argc != 2) {
	//	printf("Usage: %s PortNumber\n", argv[0]);
	//	exit(-1);
	//}

	//把端口号转化成整数
	short port = 6000;
	//if ((port = atoi(argv[1])) == 0) {
	//	printf("端口号有误\n");
	//	exit(-1);
	//}

	WSADATA wsa;
	//初始化套接字DLL
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("套接字初始化失败!\n");
		exit(-1);
	}

	//创建套接字
	SOCKET serverSocket;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printf("创建套接字失败!\n");
		exit(-1);
	}
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	//绑定
	if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		printf("套接字绑定到端口失败! 端口: %d\n", port);
		exit(-1);
	}

	//进入侦听状态
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("侦听失败!");
		exit(-1);
	}
	printf("Server %d is listening......\n", port);
	SOCKET clientSocket;//用来和客户端通信的套接字
	struct sockaddr_in clientAddress;//用来和客户端通信的套接字地址
	memset(&clientAddress, 0, sizeof(clientAddress));
	int addrlen = sizeof(clientAddress);

	//接受连接
	if ((clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &addrlen)) == INVALID_SOCKET) {
		printf("接受客户端连接失败！");
		exit(-1);
	}
	printf("Accept connection from %s\n", inet_ntoa(clientAddress.sin_addr));

	char buf[4096];
	while (1) {
		//接收数据
		memset(buf, 0x00, sizeof(buf));
		int bytes;
		if ((bytes = recv(clientSocket, buf, sizeof(buf), 0)) == SOCKET_ERROR) {
			printf("接收数据失败!\n");
			exit(-1);
		}
		buf[bytes] = '\0';
		printf("Message from %s: %s\n", inet_ntoa(clientAddress.sin_addr), buf);
		if (send(clientSocket, buf, bytes, 0) == SOCKET_ERROR) {
			printf("发送数据失败!");
			exit(-1);
		}
	}
	//清理套接字占用的资源
	WSACleanup();

	return 0;
}