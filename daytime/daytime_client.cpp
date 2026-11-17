#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <host_ip>" << std::endl;
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address" << std::endl;
        close(sockfd);
        return 1;
    }

    const char* msg = " ";
    if (sendto(sockfd, msg, strlen(msg), 0,
               (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Send failed" << std::endl;
        close(sockfd);
        return 1;
    }

    char buffer[1024];
    socklen_t len = sizeof(server_addr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr*)&server_addr, &len);
    if (n < 0) {
        std::cerr << "Receive failed" << std::endl;
    } else {
        buffer[n] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
    }

    close(sockfd);
    return 0;
}
