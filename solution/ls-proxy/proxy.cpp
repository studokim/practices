#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class Proxy
{
private:
    int proxySocket;
    int clientSocket;
    int serverSocket;

public:
    Proxy(const char *proxyIP, int proxyPort, const char *serverIP, int serverPort)
    {
        // Создание сокета прокси
        proxySocket = socket(AF_INET, SOCK_STREAM, 0);

        if (proxySocket == -1)
        {
            std::cerr << "Error creating proxy socket" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Установка параметров прокси
        struct sockaddr_in proxyAddr;
        memset(&proxyAddr, 0, sizeof(proxyAddr));
        proxyAddr.sin_family = AF_INET;
        proxyAddr.sin_port = htons(proxyPort);

        if (inet_pton(AF_INET, proxyIP, &proxyAddr.sin_addr) <= 0)
        {
            std::cerr << "Invalid proxy address" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Установка соединения с сервером
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (serverSocket == -1)
        {
            std::cerr << "Error creating server socket" << std::endl;
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);

        if (inet_pton(AF_INET, serverIP, &serverAddr.sin_addr) <= 0)
        {
            std::cerr << "Invalid server address" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        bool wantReconnect = true;
        const int maxConnectionAttempts = 3;
        int connectionAttempts = 0;

        while (wantReconnect && connect(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
        {
            if (++connectionAttempts >= maxConnectionAttempts)
            {
                std::cerr << "Exceeded maximum connection attempts. Exiting." << std::endl;
                exit(EXIT_FAILURE);
            }

            std::cerr << "Error connecting to server. Enter 'y' or 'Y' to repeat: ";
            char choice;
            std::cin >> choice;

            if (choice != 'y' && choice != 'Y')
            {
                wantReconnect = false;
                std::cerr << "Exiting." << std::endl;
                exit(EXIT_FAILURE);
            }

            std::cerr << "Retrying..." << std::endl;

            sleep(1);
        }

        if (bind(proxySocket, (struct sockaddr *)&proxyAddr, sizeof(proxyAddr)) == -1)
        {
            std::cerr << "Error binding proxy socket" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (listen(proxySocket, 1) == -1)
        {
            std::cerr << "Error listening on proxy socket" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Connected to server at " << serverIP << ":" << serverPort << std::endl;
        std::cout << "Listening at " << proxyIP << ":" << proxyPort << std::endl;
    }

    void start()
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        while (true)
        {
            // Ожидание подключения от клиента
            clientSocket = accept(proxySocket, (struct sockaddr *)&clientAddr, &clientAddrLen);

            if (clientSocket == -1)
            {
                std::cerr << "Error accepting client connection" << std::endl;
                continue;
            }

            std::cout << "Got connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

            char buffer[1024];

            while (true)
            {
                // Перенаправление команд от клиента на сервер
                ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

                if (bytesRead <= 0)
                {
                    std::cout << "Client disconnected" << std::endl;
                    close(clientSocket);
                    break; 
                }

                buffer[bytesRead] = '\0';
                send(serverSocket, buffer, bytesRead, 0);

                // Перенаправление ответов сервера на клиента
                ssize_t serverBytesRead = recv(serverSocket, buffer, sizeof(buffer) - 1, 0);

                if (serverBytesRead <= 0)
                {
                    std::cerr << "Error receiving response from server" << std::endl;
                    break;
                }

                buffer[serverBytesRead] = '\0';
                send(clientSocket, buffer, serverBytesRead, 0);
            }
        }
    }

    ~Proxy()
    {
        close(proxySocket);
        close(clientSocket);
        close(serverSocket);
    }
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <proxyIP:proxyPort> <serverIP:serverPort>" << std::endl;
        return 1;
    }

    const char *proxyIP = strtok(argv[1], ":");
    const char *proxyPortStr = strtok(nullptr, ":");
    const char *serverIP = strtok(argv[2], ":");
    const char *serverPortStr = strtok(nullptr, ":");

    // Проверка корректности аргументов командной строки
    if (proxyIP == nullptr || proxyPortStr == nullptr || serverIP == nullptr || serverPortStr == nullptr)
    {
        std::cerr << "Invalid command line arguments" << std::endl;
        return 1;
    }

    const int proxyPort = std::stoi(proxyPortStr);
    const int serverPort = std::stoi(serverPortStr);

    Proxy proxy(proxyIP, proxyPort, serverIP, serverPort);
    proxy.start();

    return 0;
}
