#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  

void func(SOCKET sockfd);

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

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

        if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
            printf("Connection failed\n");
        } else {
            printf("Connected to server\n");
            func(sockfd);
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET sockfd) {
    int n;
    printf("\nEnter the number of Fibonacci terms: ");
    scanf("%d", &n);

    send(sockfd, (char*)&n, sizeof(n), 0);

    int fib[100];
    recv(sockfd, (char*)fib, n * sizeof(int), 0);

    printf("Fibonacci Sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");
}
