#include <cstring>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#define PORT 8080
 
void execute_command(const std::string& command) {
    if (command == "open google") {
        // system("start https://google.com"); // Windows
        system("xdg-open https://google.com"); // Linux
    }
    // Add more commands here
}

int main() {
    #ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    #endif

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    std::cout << "Server listening on port " << PORT << std::endl;
    
    while(true) {
        // Accept connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[1024] = {0};
        recv(new_socket, buffer, 1024, 0);
        
        // Parse HTTP request (simple example)
        std::string request(buffer);
        size_t body_pos = request.find("\r\n\r\n");
        if (body_pos != std::string::npos) {
            std::string body = request.substr(body_pos + 4);
            execute_command(body);
        }
        
        // Send HTTP response
        const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 17\r\n\r\nCommand executed";
        send(new_socket, response, strlen(response), 0);
        #ifdef _WIN32
        closesocket(new_socket);
        #else
        close(new_socket);
        #endif
    }
    
    #ifdef _WIN32
    WSACleanup();
    #endif
    return 0;
}