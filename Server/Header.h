#include <iostream>
#include <new>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <WinSock2.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

using boost::property_tree::ptree;
using namespace std;

//####    General    ####
bool general_ip_trim (char* ip);

//####    Initialize    ####
unsigned short int init ();
unsigned short int init_setup ();
char* init_owner_pass_gen ();
void init_file (unsigned short int port, short int type, char* pass);

//####    Owner    ####
bool owner_login (char* pass);

//####    Admin    ####
short int admin_change_pass (char* pass, bool force);
bool admin_change_type (short int type, char* pass);
short int admin_ban_ip (char* ip);

//####    Connect    ####
bool connect ();
short int connect_type_check ();
bool connect_password_check (char* pass);

//####    Socket Class    ####
class Sock
{
public:
	Sock (bool t_type); //0 - TCP, 1 - UDP
	bool s_getaddrinfo (); //getaddrinfo
	bool s_socket ();
	bool s_bind ();
	bool s_listen ();
	bool s_accept ();
	bool s_recv ();
private:
	SOCKET ListenSocket;
	SOCKET ClientSocket;
	struct addrinfo *result;
	struct addrinfo hints;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen;
	bool type; //0 - TCP, 1 - UDP
	int iResult, iSendResult;
	WSADATA wsaData;
};