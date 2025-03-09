#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <ws2tcpip.h>
#include <TlHelp32.h>
using namespace std;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define PAUSE 0

bool IsServerRunning(const char* serverExe) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return false;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return false;
    }

    do {
        if (wcscmp(pe32.szExeFile, L"Server.exe") == 0) {
            CloseHandle(hProcessSnap);
            return true;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return false;
}

void StartServer(const char* serverExe) {
    SHELLEXECUTEINFO sei;
    ZeroMemory(&sei, sizeof(sei));
    sei.cbSize = sizeof(sei);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpFile = L"D:\\папка иры\\Институт\\Клієнт серверне програмування\\Server\\x64\\Debug\\Server.exe";
    sei.nShow = SW_SHOW;

    if (!ShellExecuteEx(&sei)) {
        cout << "Не вдалося запустити сервер!\n";
    }
}

int main(int argc, char** argv) {
    setlocale(0, "Ukrainian");
    system("title CLIENT SIDE");

    const char* serverExe = "server.exe"; 
    if (!IsServerRunning(serverExe)) {
        cout << "Сервер не запущено. Запускаємо сервер...\n";
        StartServer(serverExe);
        Sleep(1000); 
    }

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

    /*cout << "Доступні команди:\n";
    cout << "1. \"як справи\" - сервер відповідає \"чудово\"\n";
    cout << "2. \"goodbye\" - завершення роботи клієнта\n";

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
    }*/

    char message[DEFAULT_BUFLEN];
    char answer[DEFAULT_BUFLEN];

    while (true) {
        cout << "Введіть ціле число (або 'exit' для завершення): ";
        cin.getline(message, DEFAULT_BUFLEN);

        if (strcmp(message, "exit") == 0) {
            send(ConnectSocket, message, (int)strlen(message), 0);
            break;
        }

        iResult = send(ConnectSocket, message, (int)strlen(message), 0);
        if (iResult == SOCKET_ERROR) {
            cout << "Помилка відправки.\n";
            break;
        }

        iResult = recv(ConnectSocket, answer, DEFAULT_BUFLEN, 0);
        if (iResult > 0) {
            answer[iResult] = '\0';
            cout << "Сервер повернув: " << answer << endl;
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
