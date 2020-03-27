// LanWorks Client Example
// Version 1.0
// By Icosagon

// Libraries
#include <stdio.h>		// Standard IO Library
#include "LanWorks.h"	// LanWorks Library

int client_error; // Server init success value

int main()
{
	client_set_ip("127.0.0.1");
	client_set_port(8000);

	client_error = client_init();
	if(client_error==0) // If success
	{
		client_write("Hello world\n");
		client_close();
		printf("Done!\n");
	}
	else // Error occured
	{
		printf("Error!\n");
	}
	return client_error;
}
