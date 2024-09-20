# LanWorks

#### TCP/IP Sockets wrapper library created by IcosagonZ (which is me)

## Introduction
LanWorks is a TCP/IP Sockets wrapper library. It simplifies the process of creating sockets by
using different predefined functions. Developers can include this “LanWorks.h” library in
their projects and with one function they can set up a working sockets client or server.

Please report any bugs or issues and feel free to ask any doubts.

## Usage
To use this library add it to path of your source code (or in a folder /lib) then include it using #include "LanWorks.h", no need for any additional setup or setting up library in gcc as all the library functions is contained in one single header file.
<br><br>
Examples are included in `examples/` folder. 

## Dependencies
```c
// Standard Libraries
#include <stdio.h> // Standard IO
#include <stdlib.h> // Standard Library
#include <string.h> // String Library
#include <unistd.h>

// Connectivity Libraries
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
```
## Client functions
### void client_set_ip(char *_lanworks_ip)
```
Set the Server’s IP Address to which client will connect to.
```
### char *client_get_ip()
```
Get the Server’s IP Address to which client will connect to.
```
### void client_set_port(int _port)
```
Set client's port number.
```
### int client_get_port()
```
Get the client’s port number.
```
### void client_write(char _lan_buffer[max_char])
```
Write data to client.
```
### char *client_read()
```
Read data from client.
```
### int client_init()
```
Initialize Client or create a socket client and connect to a server. Will return 0 if
successfully connected else it will return 1 and prints the error code if enabled.
```
### void client_close()
```
Close the socket to which the client is connected to.
```

## Server functions
### void server_set_port(int _port)
```
Set server's port number.
```
### int server_get_port()
```
Get the server’s port number.
```
### void server_write(char _lan_buffer[max_char])
```
Write data to server.
```
### char *server_read()
```
Read data from server.
```
### int server_init()
```
Initialize Server or create a socket server and bind, listen, accept the client socket.
Will return 1 if successfully connected else it will return 0 and prints the error code.
```
### void server_close()
```
Close the socket to which the client is connected to.
```

## Error Codes

### Server

Error code |  Description | Function
---------- | ------------ | -----------
LS001 | Socket creation failed  | socket()
LS002 | Socket bind failed | bind()
LS003 | Socket listen failed | listen()
LS004 | Socket accept failed | accept()
LS005 | Socket close failed | close()

### Client

Error code |  Description | Function
---------- | ------------ | -----------
LC001 | Socket creation failed | socket()
LC002 | Socket connect failed | connect()
LC003 | Socket close failed | close()

