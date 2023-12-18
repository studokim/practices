#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <regex>
#include <poll.h>

const int TimeoutMilliSeconds = 5000;

class Client
{
private:
    int clientSocket;
    static const int BufferSize = 1024;

    // Отправка команды на сервер
    void SendCommand(const std::string &command)
    {
        // Проверка успешной отправки команды
        ssize_t sentBytes = send(clientSocket, command.c_str(), command.size(), 0);
        if (sentBytes == -1)
        {
            std::cerr << "Ошибка отправки на сервер" << std::endl;
            close(clientSocket);
            exit(EXIT_FAILURE);
        }
        else if (sentBytes != static_cast<ssize_t>(command.size()))
        {
            std::cerr << "Не все данные были отправлены" << std::endl;
            close(clientSocket);
            exit(EXIT_FAILURE);
        }
    }

    // Проверка валидности команды
    bool IsValidCommand(const std::string &command)
    {
        std::regex lsCommandPattern("^ls(\\s*-?[ahl]+\\s*)*(\\s+/[a-zA-Z0-9_/]+)?$");
        return std::regex_match(command, lsCommandPattern);
    }

    // Проверка задержки сервера
    void WaitForResponse()
    {
        struct pollfd fd;
        fd.fd = clientSocket;
        fd.events = POLLIN | POLLHUP | POLLERR;

        int result = poll(&fd, 1, TimeoutMilliSeconds);

        if (result == -1)
        {
            std::cerr << "Ошибка при проверке задержки сервера: " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
        else if (result == 0)
        {
            std::cerr << "Задержка со стороны сервера. Пожалуйста, подождите." << std::endl;
        }
    }

    // Получение ответа от сервера
    void ReceiveResponse(char *buffer, int bufferSize)
    {
        ssize_t bytesRead = recv(clientSocket, buffer, bufferSize - 1, 0);
        if (bytesRead == -1)
        {
            std::cerr << "Ошибка получения ответа от сервера" << std::endl;
            close(clientSocket);
            exit(EXIT_FAILURE);
        }
        else if (bytesRead == 0)
        {
            // Обработка отключения сервера
            std::cerr << "Сервер отключен" << std::endl;
            std::cout << "Нажмите Enter для завершения программы." << std::endl;
            std::cin.get();
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';
    }

public:
    Client(int clientPort, const std::string &serverIP, int serverPort)
    {
        // Создание сокета клиента
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1)
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
            close(clientSocket);
            exit(EXIT_FAILURE);
        }

        // Установка параметров клиента
        sockaddr_in clientAddr{};
        memset(&clientAddr, 0, sizeof(clientAddr));
        clientAddr.sin_family = AF_INET;
        clientAddr.sin_port = htons(clientPort);
        clientAddr.sin_addr.s_addr = INADDR_ANY;

        // Привязка сокета к порту клиента
        if (bind(clientSocket, reinterpret_cast<sockaddr *>(&clientAddr), sizeof(clientAddr)) == -1)
        {
            std::cerr << "Ошибка привязки сокета к порту" << std::endl;
            close(clientSocket);
            exit(EXIT_FAILURE);
        }

        // Подключение к серверу
        std::cout << "Подключение к серверу " << serverIP << ":" << serverPort << " с портом клиента " << clientPort << std::endl;
        if (connect(clientSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
        {
            std::cerr << "Ошибка подключения к серверу" << std::endl;
            close(clientSocket);
            exit(EXIT_FAILURE);
        }

        std::cout << "Подключен к серверу " << serverIP << ":" << serverPort << " с портом клиента " << clientPort << std::endl;
    }

    // Запуск клиента
    void Start()
    {
        char buffer[BufferSize];

        while (true)
        {
            std::cout << "> ";
            std::string command;
            std::getline(std::cin, command);

            // Проверка пустой команды или неверной команды
            if (command.empty() || !IsValidCommand(command))
            {
                std::cout << "Неверная команда. Введите корректную команду." << std::endl;
                continue;
            }

            SendCommand(command);

            // Проверка задержки сервера
            WaitForResponse();

            // Получение и вывод ответа от сервера
            ReceiveResponse(buffer, sizeof(buffer));
            std::cout << buffer << std::endl;
        }
    }

    // Деструктор класса Client
    ~Client()
    {
        shutdown(clientSocket, SHUT_RDWR);
        close(clientSocket);
    }
};

int main(int argc, char *argv[])
{
    // Проверка количества аргументов командной строки
    if (argc != 3)
    {
        std::cerr << "Используется: " << argv[0] << " <clientPort> <serverAddress:serverPort>" << std::endl;
        return 1;
    }

    const int clientPort = std::stoi(argv[1]);

    std::istringstream serverInfo(argv[2]);
    std::string serverAddress, serverPortStr;

    // Проверка успешного извлечения адреса и порта сервера
    if (!std::getline(serverInfo, serverAddress, ':') || !std::getline(serverInfo, serverPortStr))
    {
        std::cerr << "Неверный адрес или порт" << std::endl;
        return 1;
    }

    const int serverPort = std::stoi(serverPortStr);

    Client client(clientPort, serverAddress, serverPort);
    client.Start();

    return 0;
}
