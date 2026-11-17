#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <host_ip>" << std::endl;
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address" << std::endl;
        close(sockfd);
        return 1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Connected to Echo Server. Enter text (type 'exit' to quit):" << std::endl;

    std::string input;
    char buffer[1024] = {0};

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        send(sockfd, input.c_str(), input.length(), 0);

        memset(buffer, 0, sizeof(buffer));
        int valread = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (valread > 0) {
            std::cout << "Echo: " << buffer << std::endl;
        } else if (valread == 0) {
            std::cout << "Server closed connection." << std::endl;
            break;
        }
    }

    close(sockfd);
    return 0;
}
