#include "Header.h"

unsigned short int init ()
{
	unsigned short int port;
	if( !boost::filesystem::exists("conf.ini") )
		port = init_setup ();
	else
	{
		ptree pt;
		boost::property_tree::ini_parser::read_ini ("conf.ini", pt);
		port = pt.get<unsigned short int>("server_port");

	}
	return port;
}

unsigned short int init_setup ()
{
	unsigned short int port;
	short int type;
	char* pass;
	char temp_pass[32];
	cout << "Please enter the desired server port: ";
	cin >> port;
	while ( port < 1024 || port > 49152 )
	{
		cout << "Cannot run on port " << port << ".\nPlease enter the desired server port: ";
		cin >> port;
	}
	cout << "Please enter the desired server type:\n1 - Public\n2 - Password protected\n3 - Private" << endl;
	cin >> type;
	while ( type < 1 || type > 3 )
	{
		cout << "Invalid type.\nPlease enter the desired server type:\n1 - Public\n2 - Password protected\n3 - Private" << endl;
		cin >> type;
	}
	if ( type == 2 ) //If the type is set to password protected
	{
		cout << "Please enter the server's password (5 - 16 characters): ";
		cin >> temp_pass;
		while ( strlen( temp_pass ) < 5 || strlen ( temp_pass ) > 16 )
		{
			cout << "Invalid password\nPlease enter the server's password (5 - 16 characters): ";
			cin >> temp_pass;
		}
		pass = new char [strlen(temp_pass)];
		strcpy(pass, temp_pass);
	}
	else
	{
		pass = new char[1];
		*pass = 0;
	}
	init_file(port, type, pass);
	//delete[] pass;  //########   FIX   ############
	return port;
}

char* init_owner_pass_gen () //Generates a random password
{
	int i, temp;
	char* generated_pass = new char [33];
	srand(time(NULL));
	for(i = 0; i < 32; i++)
	{
		temp = rand() % 94 + 33;
		*(generated_pass + i) = temp;
	}
	*(generated_pass + i) = 0;
	return generated_pass;
}

void init_file (unsigned short int port, short int type, char* pass)
{
	ptree pt;
	pt.put("server_port", port);
	pt.put("server_type", type);
	pt.put("server_pass", pass);
	pt.put("server_owner_pass", init_owner_pass_gen() );
	write_ini("conf.ini", pt);
	cout << "Created config file 'conf.ini'." << endl;
}