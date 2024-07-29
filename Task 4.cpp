#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#include <sstream>

#pragma comment(lib, "Ws2_32.lib")

const int PORT = 8080;

void handleClient(SOCKET clientSocket) {
    char buffer[30000] = { 0 };
    recv(clientSocket, buffer, 30000, 0);

    // Parse HTTP request (only GET method for simplicity)
    std::string request(buffer);
    std::istringstream requestStream(request);
    std::string method;
    std::string path;
    requestStream >> method >> path;

    if (method == "GET") {
        if (path == "/") {
            path = "/index.html";
        }
        std::string filePath = "www" + path;
        std::ifstream file(filePath);
        if (file) {
            std::stringstream fileContent;
            fileContent << file.rdbuf();
            std::string content = fileContent.str();

            std::ostringstream httpResponse;
            httpResponse << "HTTP/1.1 200 OK\n";
            httpResponse << "Content-Type: text/html\n";
            httpResponse << "Content-Length: " << content.size() << "\n";
            httpResponse << "\n";
            httpResponse << content;

            send(clientSocket, httpResponse.str().c_str(), httpResponse.str().size(), 0);
        }
        else {
            const char* notFoundResponse = "HTTP/1.1 404 Not Found\nContent-Length: 0\n\n";
            send(clientSocket, notFoundResponse, strlen(notFoundResponse), 0);
        }
    }

    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return -1;
    }

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket failed\n";
        WSACleanup();
        return -1;
    }

    // Bind socket to port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Server is listening on port " << PORT << "\n";

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed\n";
            closesocket(serverSocket);
            WSACleanup();
            return -1;
        }

        // Handle client connection in a new thread
        std::thread(handleClient, clientSocket).detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
