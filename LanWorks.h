// LanWorks - Icosagon

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

#define max_char 80 // Max characters number
#define SA struct sockaddr

char *lanworks_ip = "127.0.0.1";    // Server IP for Client
int port = 8081 ;                   // Sockets Port number
int sockfd, connfd;
int can_print = 1;

char lan_buffer[max_char]; // Sockets Read/Write buffer

// Print command
void print(char *_print_text)
{
    if(can_print==1)
    {
        printf("%s", _print_text);
    }
}

// Set IP Address
void client_set_ip(char *_lanworks_ip)
{
    lanworks_ip = _lanworks_ip;
}

// Get IP Address
char *client_get_ip()
{
    return lanworks_ip;
}

// Set port number
void lanworks_set_port(int _port)
{
    port = _port;
}

// Get port number
int lanworks_get_port()
{
    return port;
}

// Write data to socket
void socket_write(char _lan_buffer[max_char])
{
    bzero(lan_buffer, sizeof(lan_buffer));
    strcpy(lan_buffer, _lan_buffer);
    write(connfd, lan_buffer, sizeof(lan_buffer));
}

char *socket_read()
{
    bzero(lan_buffer, sizeof(lan_buffer));
    read(connfd, lan_buffer,  sizeof(lan_buffer));
    return lan_buffer;
}

// Client Loop
void client_loop(int sockfd)
{
    int n;

    for(;;)
    {
        bzero(lan_buffer, sizeof(lan_buffer));
        printf("Client: ");
        n = 0;
        while((lan_buffer[n++]=getchar())!='\n'); // Get message from terminal

        write(sockfd, lan_buffer, sizeof(lan_buffer));
        bzero(lan_buffer, sizeof(lan_buffer));

        read(sockfd, lan_buffer,  sizeof(lan_buffer)); // Read message
        printf("Server: %s", lan_buffer);

        if((strncmp(lan_buffer, "exit", 4))==0)
        {
            print("Client Exit\n");
            break;
        }
    }
}

// Initialize Client
int client_init()
{
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        print("LC001\n");
        return 0;
    }
    else
    {
        // Socket created
        bzero(&servaddr, sizeof(servaddr));

        // Assign Family, IP and Port
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(port);

        if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!=0)
        {
            print("LC002\n");
            return 0;
        }
        else
        {
            // Connection successful
            // client_loop(sockfd);
            connfd = sockfd;
            return 1;
        }
    }
}

void client_close()
{
    close(sockfd);
}

// Server Loop
void server_loop(int sockfd)
{
    int n;
    for(;;)
    {
        bzero(lan_buffer, max_char);
        read(sockfd, lan_buffer,  sizeof(lan_buffer)); // Read message
        printf("Client: %sServer: ", lan_buffer);
        printf("Client: %sServer: ", socket_read());
        bzero(lan_buffer, max_char);
        n = 0;
        while((lan_buffer[n++]=getchar())!='\n'); // Get message from terminal
        write(sockfd, lan_buffer, sizeof(lan_buffer));

        if(strncmp("exit", lan_buffer, 4)==0)
        {
            print("Server Exit\n");
            break;
        }
    }
}

// Initialize server
int server_init()
{
    int len;
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

        // Assign Family, IP and Port
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(port);

        // Bind socket
        if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr)))!=0)
        {
            print("LS002\n");
            return 0;
        }
        else
        {
            // Socket binded

            if((listen(sockfd, 5))!=0)
            {
                print("LS003\n");
                return 0;
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
                    return 0;
                }
                else
                {
                    // Socket client accepted
                    // server_loop(connfd);
                    return 1;
                }
            }
        }
    }
}

void server_close()
{
    close(sockfd);
}
