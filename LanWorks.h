// LanWorks - Simple TCP/IP Wrapper
// Version 1.0
// By Icosagon

// Standard Libraries
#include <stdio.h>  // Standard IO
#include <stdlib.h> // Standard Library
#include <string.h> // String Library
#include <unistd.h>

// Connectivity Libraries
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define max_char 80					// Max characters number
#define SA struct sockaddr

char *server_ip = "127.0.0.1";		// Server IP for Client
int server_port = 8005;				// Sockets Server port number
int client_port = 8005;				// Sockets Client port number
int sockfd, connfd, client_connfd;
int can_print = 1;

char lan_buffer[max_char];			// Sockets Read/Write buffer
char client_buffer[max_char];		// Sockets Read/Write buffer

// Print command
void print(char *_print_text)
{
    if(can_print==1)
    {
        printf("%s", _print_text);
    }
}
// CLIENT FUNCTIONS
// Set IP Address
void client_set_ip(char *_lanworks_ip)
{
    server_ip = _lanworks_ip;
}

// Get IP Address
char *client_get_ip()
{
    return server_ip;
}

// Set client port number
void client_set_port(int _port)
{
    client_port = _port;
}

// Get client port number
int client_get_port()
{
    return client_port;
}

// Write data to socket
void client_write(char _lan_buffer[max_char])
{
    bzero(client_buffer, sizeof(client_buffer));
    strcpy(client_buffer, _lan_buffer);
    write(client_connfd, client_buffer, sizeof(client_buffer));
}
// Read data from socket
char *client_read()
{
    bzero(client_buffer, sizeof(client_buffer));
    read(client_connfd, client_buffer,  sizeof(client_buffer));
    return client_buffer;
}

// Initialize Client
int client_init()
{
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        print("LC001\n");
        return 1;
    }
    else
    {
        // Socket created
        bzero(&servaddr, sizeof(servaddr));

        // Assign Family, IP and server_port
        servaddr.sin_family = AF_INET;
        //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Local server
        servaddr.sin_addr.s_addr = inet_addr(server_ip);
        servaddr.sin_port = htons(client_port);

        if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!=0)
        {
            print("LC002\n");
            return 1;
        }
        else
        {
            // Connection successful
            client_connfd = sockfd;
            return 0;
        }
    }
}

void client_close()
{
    close(client_connfd);
}

// SERVER FUNCTIONS
// Set server_port number
void server_set_port(int _port)
{
    server_port = _port;
}

// Get server port number
int server_get_port()
{
    return server_port;
}

// Initialize server
int server_init()
{
    socklen_t len;
    struct sockaddr_in servaddr, cli;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        print("LS001\n");
        return 1;
    }
    else
    {
        // Socket created
        bzero(&servaddr, sizeof(servaddr));

        // Assign Family, IP and server_port
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(server_port);

        // Bind socket
        if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr)))!=0)
        {
            print("LS002\n");
            return 1;
        }
        else
        {
            // Socket binded

            if((listen(sockfd, 5))!=0)
            {
                print("LS003\n");
                return 1;
            }
            else
            {
                // Socket listening
                len = sizeof(cli);

                // Accept connection
                connfd = accept(sockfd, (SA*)&cli, &len);
                if(connfd<0)
                {
                    print("LS004\n");
                    return 1;
                }
                else
                {
                    // Socket client accepted
                    return 0;
                }
            }
        }
    }
}

// Write data to socket
void server_write(char _lan_buffer[max_char])
{
    bzero(lan_buffer, sizeof(lan_buffer));
    strcpy(lan_buffer, _lan_buffer);
    write(connfd, lan_buffer, sizeof(lan_buffer));
}
// Read data from socket
char *server_read()
{
    bzero(lan_buffer, sizeof(lan_buffer));
    read(connfd, lan_buffer,  sizeof(lan_buffer));
    return lan_buffer;
}

void server_close()
{
    close(sockfd);
}
