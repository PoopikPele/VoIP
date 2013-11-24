#include "Header.h"

bool owner_login (char* owner_pass)
{
	string pass;
	ptree pt;
	boost::property_tree::ini_parser::read_ini("conf.ini", pt);
	pass = pt.get<string>("server_owner_pass");
	if (!pass.compare (owner_pass) )
		return true;
	else
		return false;
}