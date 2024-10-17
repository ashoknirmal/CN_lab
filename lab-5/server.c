#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  

void func(SOCKET confd);

int main() {
    WSADATA wsaData;
    SOCKET sockfd, confd;
    struct sockaddr_in servaddr, cliaddr;
    int len;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
    } else {
        printf("Socket created\n");

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(43451);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
            printf("Bind failed\n");
        } else {
            printf("Bind successful\n");

            if (listen(sockfd, 5) == SOCKET_ERROR) {
                printf("Listen failed\n");
            } else {
                printf("Listening...\n");

                len = sizeof(cliaddr);
                confd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);

                if (confd == INVALID_SOCKET) {
                    printf("Accept failed\n");
                } else {
                    printf("Client connected\n");
                    func(confd);
                }
            }
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET confd) {
    int n;

    recv(confd, (char*)&n, sizeof(n), 0);

    int fib[100];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    send(confd, (char*)fib, n * sizeof(int), 0);

    closesocket(confd);
}
