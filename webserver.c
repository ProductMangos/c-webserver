#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    // create socket
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("webserver (socket)");
        return 1;
    }

    printf("socket created successfully\n");

    // bind struct
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = PF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

// bind socket to address
    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("webserver (bind)");
        return 1;
    }

    printf("socket successfully bound to address\n");


    if (listen(sockfd, 128) != 0) {
        perror("webserver (listen)");
        return 1;    
    }
    printf("server listening for connections on address\n");

// accept connections from clients
// infinite loop
// accept connections
// close connection when accepted
    for (;;) {
        int client_socket = accept(sockfd, (struct sockaddr *)&host_addr, (socklen_t *)&host_addrlen);
        if (client_socket < 0) {
            perror("webserver (accept)");
            continue;
        }
        printf("client accepted\n");
        close(client_socket);
    }
    return 0;
}