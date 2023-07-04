#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define MAX_BUF_LEN 1024

int main(int argc, char const* argv[])
{
    int socket_desc, conn_fd;
    struct sockaddr_in server_addr, client_addr;

    char cli_buf[MAX_BUF_LEN]={0};
    char ser_buf[MAX_BUF_LEN]={0};

    int addrlen = sizeof(client_addr);
    int bytes_read=0;
    
    if (!argv[1] || !argv[2]) {
        printf("provide all 2 arguments: argv[1]<port> and argv[2]<msg to be sent to client>\n");
        return 0;
    }
    memcpy(ser_buf, argv[2], strlen(argv[2]));
    //printf("argv[1]=[%d], argv[2]=[%s]\n", atoi(argv[1]), argv[2]);

    /* 
     * creating a socket of below category: 
     * @family = AF_INET
     * @type = SOCK_STREAM
     * @protocol = 0; 0 means system's default protocol for the
     *      given family and type is chosen here.
     * */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    //printf("creted socket_desc=[%d]\n", socket_desc);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*
     * The “bind()” system call is used to assign a local protocol 
     * address(combination of IPv4/IPv6 address & port no) to an existing socket .
     * */
    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    /*
     * The “listen()” function is called by a TCP server and it converts an
     * unconnected socket into a passive socket , indicating that the kernel
     * should accept incoming connection requests directed to this socket.
     *
     * @backlog = 5, specifies that 5 connection requests can be queued by the
     * system while it waits for the server to execute the accept system call
     * */
    if (listen(socket_desc, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for client to accept\n");
        /*
         * The “accept()” is called by a TCP server to return the next completed
         * connection from the front of the completed connection queue. If the completed 
         * connection queue is empty the process is put to sleep.
         * If “accept()” is successful, it’s return value is a brand new descriptor,
         * automatically created by the kernel.
         * */
        conn_fd = accept(socket_desc, (struct sockaddr*)&client_addr, (socklen_t *)&addrlen);
        if (conn_fd < 0) {
            perror("accept failed");
            //exit(EXIT_FAILURE);
            break;
        }

        bytes_read = read(conn_fd, cli_buf, MAX_BUF_LEN);
        printf("bytes_read=[%d], msg received from client=[%s]\n", bytes_read, cli_buf);

        send(conn_fd, ser_buf, strlen(ser_buf), 0);
        printf("ack sent to client\n");

        /*close the connection socket*/
        close(conn_fd);
    }

    /*close the listening socket*/
    shutdown(socket_desc, SHUT_RDWR);

    return 0;
}
