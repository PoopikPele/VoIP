#include "Header.h"

short int admin_change_pass (char* pass, bool force)
{
	ptree pt;
	short int type;
	boost::property_tree::ini_parser::read_ini ("conf.ini", pt);
	type = pt.get<short int>("server_type");
	if (type == 2 || force)
	{
		if ( strlen(pass) > 16 || strlen(pass) < 5 )
			return 2;
		else
		{
			pt.put("server_pass", pass);
			write_ini("conf.ini", pt);
			return 0;
		}
	}
	else
		return 1;
}

bool admin_change_type (short int type, char* pass)
{
	if (type == 2 && !admin_change_pass (pass, 1) )
	{
		ptree pt;
		boost::property_tree::ini_parser::read_ini("conf.ini", pt);
		pt.put("server_type", type);
		write_ini("conf.ini", pt);
		return true;
	}
	else if (type == 2)
		return false;
	else
	{
		ptree pt;
		boost::property_tree::ini_parser::read_ini("conf.ini", pt);
		pt.put("server_type", type);
		pt.put("server_pass", "\0");
		write_ini("conf.ini", pt);
		return true;
	}
}

short int admin_ban_ip (char* ip)
{
	ofstream out;
	out.open("banned_ip.csv", ios::app);
	out << ip << ",";
	return 0;
}