#include <stdio.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
using namespace std;

int main() {
	//��ʼ�� DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("192.168.1.131");  //�����IP��ַ
	sockAddr.sin_port = htons(61245);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬
	listen(servSock, 20);

	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	cout << "�ȴ��ͻ�������..." << endl;
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	cout << "�ͻ��������ӣ�" << endl;
	//��ͻ��˷�������
	string input;
	const char *str;
	while (true)
	{
		cout << "������Ҫ���͵����ݣ�";
		getline(cin, input);
		str = input.c_str();
		if (input == "close")
			break;
		else
			send(clntSock, str, strlen(str) + sizeof(char), NULL);
	}

	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();

	return 0;
}