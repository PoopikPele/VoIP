#include "Header.h"

unsigned short int g_port;

void main()
{
	g_port = init();
	Sock Server(0);
	cout << Server.s_getaddrinfo () << endl;
	cout << Server.s_socket () << endl;
	cout << Server.s_bind () << endl;
	system("PAUSE");
}