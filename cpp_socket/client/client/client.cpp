#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll
using namespace std;

int main() {
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("114.242.62.15");
	sockAddr.sin_port = htons(61245);
	//connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//���շ��������ص�����
	char szBuffer[MAXBYTE] = { 0 };
	int res = 0;
	string input;
	
	while (true)
	{
		cout << "����connect���ӷ�����:";
		getline(cin, input);

		if (input == "connect")
		{
			connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
			cout << "���������ӳɹ���" << endl;
			break;
		}
			
	}
	while (1)
	{
		res = recv(sock, szBuffer, MAXBYTE, NULL);

		//������յ�������
		if (res > 0)
		{
			printf("���Է�����: %s\n", szBuffer);
			memset(szBuffer, 0, sizeof(szBuffer));
		}
	}

	//�ر��׽���
	closesocket(sock);

	//��ֹʹ�� DLL
	WSACleanup();

	system("pause");
	return 0;
}