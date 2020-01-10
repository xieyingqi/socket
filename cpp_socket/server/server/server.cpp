#include <stdio.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
using namespace std;

int main() {
	//初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("192.168.1.131");  //具体的IP地址
	sockAddr.sin_port = htons(61245);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//进入监听状态
	listen(servSock, 20);

	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	cout << "等待客户端连接..." << endl;
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	cout << "客户端已连接！" << endl;
	//向客户端发送数据
	string input;
	const char *str;
	while (true)
	{
		cout << "请输入要发送的内容：";
		getline(cin, input);
		str = input.c_str();
		if (input == "close")
			break;
		else
			send(clntSock, str, strlen(str) + sizeof(char), NULL);
	}

	//关闭套接字
	closesocket(clntSock);
	closesocket(servSock);

	//终止 DLL 的使用
	WSACleanup();

	return 0;
}