#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define PAUSE 0

int main(int argc, char** argv) {
    setlocale(0, "Ukrainian");
    system("title CLIENT SIDE");


    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        return 11;
    }

    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    const char* ip = "localhost";
    addrinfo* result = NULL;
    iResult = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);

    if (iResult != 0) {
        WSACleanup();
        return 12;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (ConnectSocket == INVALID_SOCKET) {
            WSACleanup();
            return 13;
        }

        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        cout << "неможливо пiдключитися до сервера. перевiрте, чи запущено процес сервера!\n";
        WSACleanup();
        return 14;
    }
    else {
        cout << "пiдключення до сервера пройшло успiшно!\n";
    }

    cout << "Доступні команди:\n";
    cout << "1. \"your name\"\n";
    cout << "2. \"how are you doing\"\n";
    cout << "3. \"goodbye\"\n";
    cout << endl;

    char message[DEFAULT_BUFLEN];
    char answer[DEFAULT_BUFLEN];

    while (true) {
        cout << "Введіть повідомлення для сервера: ";
        cin.getline(message, DEFAULT_BUFLEN);

        iResult = send(ConnectSocket, message, (int)strlen(message), 0);
        if (iResult == SOCKET_ERROR) {
            cout << "Помилка відправки.\n";
            break;
        }

        if (strcmp(message, "goodbye") == 0) {
            cout << "Завершення роботи клієнта...\n";
            break;
        }

        iResult = recv(ConnectSocket, answer, DEFAULT_BUFLEN, 0);
        if (iResult > 0) {
            answer[iResult] = '\0';
            cout << "Відповідь сервера: " << answer << endl;
        }
        else {
            cout << "Сервер закрив з'єднання.\n";
            break;
        }
    }

    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
