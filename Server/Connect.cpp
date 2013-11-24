#include "Header.h"

bool connect ()
{
	short int type = connect_type_check ();
	char pass[32];
	if (type == 2)
	{
		cout << "Please enter the server's password: ";
		cin >> pass;
		if ( !connect_password_check (pass) )
			return 1;
		else
			return 0;
	}
	else if (type == 3)
		return 0;
	else
		return 1;
}

short int connect_type_check ()
{
	ptree pt;
	boost::property_tree::ini_parser::read_ini ("conf.ini", pt);
	return pt.get<short int>("server_type");
}

bool connect_password_check (char* pass)
{
	ptree pt;
	string server_pass;
	boost::property_tree::ini_parser::read_ini ("conf.ini", pt);
	server_pass.append(pt.get<string>("server_pass"));
	if ( !server_pass.compare(pass) )
		return 1;
	else
		return 0;
}