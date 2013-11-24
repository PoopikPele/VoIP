#include "Header.h"
#include <Windows.h>
#include <WS2tcpip.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define WIN32_LEAN_AND_MEAN

Sock::Sock (bool t_type)
{
	ListenSocket = INVALID_SOCKET;
	ClientSocket = INVALID_SOCKET;
	type = t_type;
	result = NULL;
	recvbuflen = DEFAULT_BUFLEN;
	iResult = WSAStartup (MAKEWORD (2, 2), &wsaData);
	if (iResult != 0)
	{
		cout << "WSAStuartup faile with error " << iResult << endl;
	}
	else
	{
		ZeroMemory (&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		if (!type)
		{
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
		}
		else
		{
			hints.ai_socktype = SOCK_DGRAM;
			hints.ai_protocol = IPPROTO_UDP;
		}
		hints.ai_flags = AI_PASSIVE;
	}
}

bool Sock::s_getaddrinfo()
{
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		cout << "gainfo failed with error " << iResult << endl;
		WSACleanup();
		return false;
	}
	return true;
}

bool Sock::s_socket()
{
	ListenSocket = socket (result -> ai_family, result -> ai_socktype, result -> ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "Socket failed with error " << WSAGetLastError();
		freeaddrinfo (result);
		WSACleanup();
		return false;
	}
	return true;
}

bool Sock::s_bind() //FIX
{
	bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	return true;
}

bool Sock::s_listen()
{
	freeaddrinfo(result);
	iResult = listen (ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Listen failed with error " << WSAGetLastError() << endl;
		closesocket (ListenSocket);
		WSACleanup();
		return false;
	}
	return true;
}

bool Sock::s_accept()
{
	ClientSocket = accept (ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "Accept failed with error " << WSAGetLastError () << endl;
		WSACleanup();
		return false;
	}
	closesocket (ListenSocket);
	return true;
}

bool Sock::s_recv()
{
	do
	{
		iResult = recv (ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			cout << "Recieved " << iResult << " bytes." << endl;
			cout << recvbuf << endl << endl;
			iSendResult = send (ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR)
			{
				cout << "Send failed with error " << WSAGetLastError () << endl;
				closesocket (ClientSocket);
				WSACleanup();
				return false;
			}
			cout << "Send " << iSendResult << " bytes." << endl;
		}
		else if (!iResult)
		{
			cout << "Closing connection." << endl;
			return true;
		}
		else
		{
			cout << "Recv failed with error " << WSAGetLastError () << endl;
			closesocket (ClientSocket);
			WSACleanup();
			return false;
		}
	}
	while (iResult > 0);
}