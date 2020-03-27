// LanWorks Server Example
// Version 1.0
// By Icosagon

// Libraries
#include <stdio.h>		// Standard IO Library
#include "LanWorks.h"	// LanWorks Library

int server_error; // Server init success value

int main()
{
	server_set_port(8000);
	server_error = server_init();

	if(server_error==0) // If success
	{
		server_write("Hello world\n");
		server_close();
		printf("Done!\n");
	}
	else // Error occured
	{
		printf("Error!\n");
	}
	return server_error;
}
