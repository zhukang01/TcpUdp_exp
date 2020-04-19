//#include "opencv2/opencv.hpp"
//#include <WinSock2.h>
//#include <Windows.h>
//#pragma comment (lib, "ws2_32.lib")
//#pragma warning(disable : 4996)
//using namespace cv;
//
////待传输图像默认大小为 640*480，可修改
//#define IMG_WIDTH 640	// 需传输图像的宽
//#define IMG_HEIGHT 480	// 需传输图像的高
////默认格式为CV_8UC3
//#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/32 
//struct recvbuf
//{
//	char buf[BUFFER_SIZE];
//	int flag;
//};
//recvbuf data_recv;
//Mat recieveMat(SOCKET sockServer);
//int main() {
//
//	//初始化 DLL
//	WSADATA data;
//	WORD w = MAKEWORD(2, 0);
//	::WSAStartup(w, &data);
//	// 创建套接字
//	SOCKET s;
//	s = ::socket(AF_INET, SOCK_STREAM, 0);
//
//	// 构造ip地址
//	sockaddr_in addr;
//	addr.sin_family = AF_INET;
//	addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");
//	addr.sin_port = htons(1234);
//	std::cout << "connecting\n";
//	::connect(s, (sockaddr*)&addr, sizeof(addr));
//	std::cout << "linked\n";
//	while (true) {
//		Mat frame = recieveMat(s);
//		if (frame.data) imshow("Camera", frame);
//		if (waitKey(1) >= 0)break;
//	}
//	::closesocket(s);
//	::WSACleanup();
//
//}
//
//
//Mat recieveMat(SOCKET sockServer) {
//	Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));
//	int needRecv = sizeof(recvbuf);
//	int count = 0;
//	for (int i = 0; i < 32; i++) {
//		int pos = 0;
//		int len0 = 0;
//		while (pos < needRecv) {
//			len0 = recv(sockServer, (char*)(&data_recv) + pos, needRecv - pos, 0);
//			pos += len0;
//		}
//		count = count + data_recv.flag;
//		int num1 = IMG_HEIGHT / 32 * i;
//		for (int j = 0; j < IMG_HEIGHT / 32; j++) {
//			int num2 = j * IMG_WIDTH * 3;
//			uchar* ucdata = img.ptr<uchar>(j + num1);
//			for (int k = 0; k < IMG_WIDTH * 3; k++) {
//				ucdata[k] = data_recv.buf[num2 + k];
//			}
//		}
//		if (data_recv.flag == 2) {
//			if (count == 33) {
//				return img;
//			}
//			else {
//				count = 0;
//				i = 0;
//			}
//		}
//	}
//}




////UDP
//#include <stdio.h>
///* Windows socket头文件 */
//#include <Winsock2.h>
///* 网络API的动态链接库 */
//#pragma comment(lib, "ws2_32.lib")
//
//
//void main()
//{
//
//	SOCKET uiFdsocket;
//	WSADATA wsaData;
//	struct sockaddr_in stServerAddr;
//	int iAddrlen = sizeof(sockaddr_in);
//	char szbuffer[1024] = "\0";
//
//	if (0 != WSAStartup(MAKEWORD(2, 1), &wsaData))
//	{
//		printf("Winsock init faied!\r\n");
//		WSACleanup();
//		return;
//	}
//
//	/* 服务器监听的端口和地址 */
//
//	memset(&stServerAddr, 0, sizeof(stServerAddr));
//	stServerAddr.sin_family = AF_INET;
//	stServerAddr.sin_port = htons(6000);
//	stServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//
//	printf("Now connecting the server...\r\n");
//
//	uiFdsocket = socket(AF_INET, SOCK_DGRAM, 0);
//
//	while (true)
//	{
//		printf("Input message here...\r\n");
//        scanf("%s", szbuffer);
//		//gets(szbuffer);
//		if (strcmp(szbuffer, "bye") == 0)
//		{
//			printf("exit\r\n");
//			Sleep(100);
//			closesocket(uiFdsocket);
//			break;
//		}
//
//		if (SOCKET_ERROR != sendto(uiFdsocket, szbuffer, sizeof(szbuffer), 0, (struct  sockaddr*)&stServerAddr, iAddrlen))
//		{
//			Sleep(100);
//			if (SOCKET_ERROR != recvfrom(uiFdsocket, szbuffer, sizeof(szbuffer), 0, (struct sockaddr*)&stServerAddr, &iAddrlen))
//			{
//				printf("recive from server:%s\r\n", szbuffer);
//			}
//		}
//	}
//
//	closesocket(uiFdsocket);
//	return;
//}



//TCP
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
	////判断是否输入了IP地址和端口号
	//if (argc != 3) {
	//	printf("Usage: %s IPAddress PortNumber\n", argv[0]);
	//	exit(-1);
	//}

	//把字符串的IP地址转化为u_long
	unsigned long ip;
	ip = inet_addr("127.0.0.1");
	//if ((ip = inet_addr(argv[1])) == INADDR_NONE) {
	//	printf("不合法的IP地址：%s", argv[1]);
	//	exit(-1);
	//}

	//把端口号转化成整数
	short port = 6000;
	//if ((port = atoi(argv[2])) == 0) {
	//	printf("端口号有误!");
	//	exit(-1);
	//}
	printf("Connecting to %s:%d......\n", inet_ntoa(*(in_addr*)&ip), port);

	WSADATA wsa;
	//初始化套接字DLL
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("套接字初始化失败!");
		exit(-1);
	}

	//创建套接字
	SOCKET sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printf("创建套接字失败!");
		exit(-1);
	}
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = ip;
	serverAddress.sin_port = htons(port);

	//建立和服务器的连接
	if (connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		printf("建立连接失败!");
		exit(-1);
	}

	char buf[4096];
	while (1) {
		printf(">");

		//从控制台读取一行数据
		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);
		//gets(buf);
		buf[strlen(buf)] = '\0';

		//发送给服务器
		if (send(sock, buf, strlen(buf), 0) == SOCKET_ERROR) {
			printf("发送数据失败!\n");
			exit(-1);
		}
		int bytes;
		if ((bytes = recv(sock, buf, strlen(buf), 0)) == SOCKET_ERROR) {
			printf("接收数据失败!\n");
			exit(-1);
		}
		buf[bytes] = '\0';
		printf("Message from %s: %s\n", inet_ntoa(serverAddress.sin_addr), buf);
	}

	//清理套接字占用的资源
	WSACleanup();

	return 0;
}