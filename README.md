# LanWorks

#### TCP/IP Sockets library by Icosagon


## Introduction

LanWorks is a TCP/IP Sockets library. It simplifies the process of creating sockets by
using different predefined functions. Developers can include this “LanWorks.h” library in
their projects and with one function they can set up a working sockets client or server.

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

## Functions

### void client_set_ip(char *_lanworks_ip)

```
Set the Server’s IP Address to which client will connect to.
```
### char client_get_ip()

```
Get the Server’s IP Address to which client will connect to.
```
### void lanworks_set_port(int _port)

```
Set the Socket’s port.
```
### int lanworks_get_port()

```
Get the Socket’s port.
```

### void socket_write(char _lan_buffer[max_char])

```
Write data to socket
```
### char *socket_read()

```
Read data from socket
```
### int client_init()

```
Initialize Client or create a socket client and connect to a server. Will return 1 if
successfully connected else it will return 0 and prints the error code.
```

### void client_loop(int sockfd)

```
Example function. This function executes a chat client loop.The program will
terminate if the use types exit and enter.
```

### void client_close()

```
Close the socket to which the client is connected to.
```
### int server_init()

```
Initialize Server or create a socket server and bind, listen, accept the client socket.
Will return 1 if successfully connected else it will return 0 and prints the error code.
```

### void server_loop(int sockfd)

```
Example function. This function executes a chat server loop. The program will
terminate if the use types exit and enter.
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

