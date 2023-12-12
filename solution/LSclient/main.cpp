#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>

const int bufferSize = 1024;

class Client
{
private:
    int serverSocket;

public:
    Client(const std::string &serverIP, int serverPort)
    {
        // Создание сокета клиента
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1)
        {
            std::cerr << "Ошибка создания сокета" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Установка параметров сервера
        sockaddr_in serverAddr{};
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0)
        {
            std::cerr << "Некорректный адрес" << std::endl;
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        // Установка соединения с сервером
        std::cout << "Подключение к серверу " << serverIP << ":" << serverPort << std::endl;
        if (connect(serverSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
        {
            std::cerr << "Ошибка подключения к серверу" << std::endl;
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        std::cout << "Подключен к серверу " << serverIP << ":" << serverPort << std::endl;
    }

    // Запуск клиента
    void start()
    {
        char buffer[bufferSize];

        while (true)
        {

            std::cout << "> ";
            std::string command;
            std::getline(std::cin, command);

            if (command.empty())
            {
                std::cout << "Неверная команда. Введите команду." << std::endl;
                continue;
            }

            sendCommand(command);

            receiveResponse(buffer, sizeof(buffer));
            std::cout << buffer << std::endl;
        }
    }

    // Отправка команды на сервер
    void sendCommand(const std::string &command)
    {
        // Проверка успешной отправки команды
        if (send(serverSocket, command.c_str(), command.size(), 0) == -1)
        {
            std::cerr << "Ошибка отправки на сервер" << std::endl;
            close(serverSocket);
            exit(EXIT_FAILURE);
        }
    }

    // Получение ответа от сервера
    void receiveResponse(char *buffer, int bufferSize)
    {
        // Получение ответа от сервера
        ssize_t bytesRead = recv(serverSocket, buffer, bufferSize - 1, 0);
        if (bytesRead == -1)
        {
            std::cerr << "Ошибка получения ответа от сервера" << std::endl;
            close(serverSocket);
            exit(EXIT_FAILURE);
        }
        else if (bytesRead == 0)
        {
            // Обработка отключения сервера
            std::cerr << "Сервер отключен" << std::endl;
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';
    }

    ~Client()
    {
        close(serverSocket);
    }
};

int main(int argc, char *argv[])
{
    // Проверка аргументов командной строки
    if (argc != 3)
    {
        std::cerr << "Используется: " << argv[0] << " <serverPort> <serverAddress:proxyPort>" << std::endl;
        return 1;
    }

    const int serverPort = std::stoi(argv[1]);

    std::istringstream serverInfo(argv[2]);
    std::string serverAddress, serverPortStr;

    // Проверка успешного чтения адреса прокси и порта
    if (!std::getline(serverInfo, serverAddress, ':') || !std::getline(serverInfo, serverPortStr))
    {
        std::cerr << "Неверный адрес или порт" << std::endl;
        return 1;
    }

    const int proxyPort = std::stoi(serverPortStr);

    Client client(serverAddress, proxyPort);
    client.start();

    return 0;
}
