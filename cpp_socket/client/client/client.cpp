#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
using namespace std;

int main() {
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("114.242.62.15");
	sockAddr.sin_port = htons(61245);
	//connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//接收服务器传回的数据
	char szBuffer[MAXBYTE] = { 0 };
	int res = 0;
	string input;
	
	while (true)
	{
		cout << "输入connect连接服务器:";
		getline(cin, input);

		if (input == "connect")
		{
			connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
			cout << "服务器连接成功！" << endl;
			break;
		}
			
	}
	while (1)
	{
		res = recv(sock, szBuffer, MAXBYTE, NULL);

		//输出接收到的数据
		if (res > 0)
		{
			printf("来自服务器: %s\n", szBuffer);
			memset(szBuffer, 0, sizeof(szBuffer));
		}
	}

	//关闭套接字
	closesocket(sock);

	//终止使用 DLL
	WSACleanup();

	system("pause");
	return 0;
}