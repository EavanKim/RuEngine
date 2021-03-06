#include "CTCPConnect.h"

using namespace RuEngine;

#if _WIN64 || _WIN32
CTCPConnect::CTCPConnect()
{

}

CTCPConnect::CTCPConnect(const char* _sz_port, const char* _sz_addr)
{
	Initialize(_sz_port, _sz_addr);
}

CTCPConnect::~CTCPConnect()
{
	Close();
	Release();
}

void CTCPConnect::Initialize()
{
	WSAStartup(MAKEWORD(2, 2), &mtag_data);

	mtag_socket = {};
	mtag_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	mtag_addr = {};
	mtag_addr.sin_family = AF_INET;
	mtag_addr.sin_port = htons(atoi(msz_port));
	mtag_addr.sin_addr.s_addr = inet_addr(msz_ip);
}

void CTCPConnect::Initialize(const char* _sz_port, const char* _sz_addr)
{
	int addrlen = (int)strnlen(_sz_addr, 255);
	msz_ip = new char[addrlen];
	memcpy(msz_ip, _sz_addr, addrlen);

	int portlen = (int)strnlen(_sz_port, 255);
	msz_port = new char[portlen];
	memcpy(msz_port, _sz_port, portlen);
}

int CTCPConnect::Connect()
{
	int result = 0;
	try
	{
		result = connect(mtag_socket, (SOCKADDR*)&mtag_addr, sizeof(mtag_addr));

		if (result < 0)
			throw result;
	}
	catch (int e)
	{

	}

	return result;
}

void CTCPConnect::Send(void* _packet)
{
	int result = 
		send(
			mtag_socket
			, (char*)_packet
			, (int)strnlen_s((char*)_packet, 255)
			, 0);
}

void CTCPConnect::Close()
{
	closesocket(mtag_socket);
	WSACleanup();
}

void CTCPConnect::Release()
{
	if (nullptr != msz_ip)
	{
		delete msz_ip;
	}

	if (nullptr != msz_port)
	{
		delete msz_port;
	}
}

#else
CTCPConnect::CTCPConnect()
{

}

CTCPConnect::CTCPConnect(const char* _sz_port, const char* _sz_addr)
{
	Initialize(_sz_port, _sz_addr);
}

CTCPConnect::~CTCPConnect()
{
	Close();
	Release();
}

void CTCPConnect::Initialize()
{
	Initialize(msz_port, msz_ip);
}

void CTCPConnect::Initialize(const char* _sz_port, const char* _sz_addr)
{
	int addrlen = strnlen(_sz_addr, 255);
	msz_ip = new char[addrlen];
	memccpy(msz_ip, _sz_addr, addrlen, 255);

	int portlen = strnlen(_sz_port, 255);
	msz_port = new char[portlen];
	memccpy(msz_port, _sz_port, portlen, 255);

	int strlen = sizeof(mtag_servaddr);
	int buf, cNum;//cNum ���� ��ȣ

	if ((mi_socketfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket fail");
	}
	else
	{
		memset(&mtag_servaddr, 0, strlen);
		mtag_servaddr.sin_family = AF_INET;
		//inet_pton(AF_INET, _sz_addr, &mtag_servaddr.sin_addr);
		mtag_servaddr.sin_addr.s_addr = inet_addr(_sz_addr);
		mtag_servaddr.sin_port = htons(atoi(_sz_port));
	}
}

int CTCPConnect::Connect()
{
	int result = 0;

	int strlen = sizeof(mtag_servaddr);

	cout << "try connect to server : ";
	cout << msz_ip << ":" << msz_port << endl;

	result = connect(mi_socketfd, (struct sockaddr *)&mtag_servaddr, strlen);

	if (result < 0)
	{
		cout << "connect error" << endl;
	}

	return result;
}

void CTCPConnect::Send(void* _packet)
{
	ssize_t result = write(mi_socketfd, _packet, 4);

	cout << "SendData -> result : " << result << endl;

	if (result < 0)
	{

	}
}

void CTCPConnect::Close()
{
	int result = close(mi_socketfd);

	if (result < 0)
	{

	}
}

void CTCPConnect::Release()
{
	if (nullptr != msz_ip)
	{
		delete msz_ip;
	}

	if (nullptr != msz_port)
	{
		delete msz_port;
	}
}
#endif

