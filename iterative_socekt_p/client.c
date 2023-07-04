#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_BUF_LEN 1024

int main(int argc, char const* argv[])
{
    int retval, bytes_read, client_sockfd, my_port;
    struct sockaddr_in server_addr;
    char cli_buf[MAX_BUF_LEN]={0}, ser_buf[MAX_BUF_LEN]={0};

    if (!argv[1] || !argv[2] || !argv[3]) {
        printf("provide all 3 arguments: argv[1]<port>, argv[2]<ip 127.0.0.1>, argv3<msg to be send to server>\n");
        return 0;
    }
    my_port=atoi(argv[1]);
    memcpy(cli_buf, argv[3], strlen(argv[3]));

    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sockfd < 0) {
        perror("scoket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(my_port);
    server_addr.sin_addr.s_addr = inet_addr(argv[2]);

    retval = connect(client_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (retval < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    printf("sending msg to server.\n");
    send(client_sockfd, cli_buf, strlen(cli_buf), 0);

    bytes_read = read(client_sockfd, ser_buf, MAX_BUF_LEN);
    if (bytes_read > 0) {
        printf("msg received from server: [%s]\n", ser_buf);
    }

    close(client_sockfd);

    return 0;
}
