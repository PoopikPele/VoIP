#include "Header.h"

bool general_ip_trim (char* ip)
{
	bool flag = true;
	char temp[] = "\0\0\0";
	short int temp_num, restart = 0; 
	for (short int i = 0; i < strlen(ip) + 1 && flag; i++)
	{
		if ( *(ip + i) != '.' && *(ip + i) != 0)
			temp[i - restart] = ip[i];
		else if ( *(ip + i) == '.' || *(ip + i) == 0)
		{
			restart = i + 1;
			temp_num = atoi(temp);
			if (temp_num > 255)
				flag = false;
			else
				for (int j = 0; j < 3; j++)
					temp[j] = 0;
		}
	}
	if (!flag)
		return false;
	else
		return true;
}