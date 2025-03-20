//#define WIN32_LEAN_AND_MEAN
//
//#include <iostream>
//#include <windows.h>
//#include <shellapi.h>
//#include <ws2tcpip.h>
//#include <TlHelp32.h>
//using namespace std;
//
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015"
//#define PAUSE 0
//
//bool IsServerRunning(const char* serverExe) {
//    HANDLE hProcessSnap;
//    PROCESSENTRY32 pe32;
//    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//    if (hProcessSnap == INVALID_HANDLE_VALUE) {
//        return false;
//    }
//
//    pe32.dwSize = sizeof(PROCESSENTRY32);
//    if (!Process32First(hProcessSnap, &pe32)) {
//        CloseHandle(hProcessSnap);
//        return false;
//    }
//
//    do {
//        if (wcscmp(pe32.szExeFile, L"Server.exe") == 0) {
//            CloseHandle(hProcessSnap);
//            return true;
//        }
//    } while (Process32Next(hProcessSnap, &pe32));
//
//    CloseHandle(hProcessSnap);
//    return false;
//}
//
//void StartServer(const char* serverExe) {
//    SHELLEXECUTEINFO sei;
//    ZeroMemory(&sei, sizeof(sei));
//    sei.cbSize = sizeof(sei);
//    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
//    sei.lpFile = L"D:\\папка иры\\Институт\\Клієнт серверне програмування\\Server\\x64\\Debug\\Server.exe";
//    sei.nShow = SW_SHOW;
//
//    if (!ShellExecuteEx(&sei)) {
//        cout << "Не вдалося запустити сервер!\n";
//    }
//}
//
//int main(int argc, char** argv) {
//    setlocale(0, "Ukrainian");
//    system("title CLIENT SIDE");
//
//    const char* serverExe = "server.exe"; 
//    if (!IsServerRunning(serverExe)) {
//        cout << "Сервер не запущено. Запускаємо сервер...\n";
//        StartServer(serverExe);
//        Sleep(1000); 
//    }
//
//    WSADATA wsaData;
//    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//    if (iResult != 0) {
//        return 11;
//    }
//
//    addrinfo hints;
//    ZeroMemory(&hints, sizeof(hints));
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//
//    const char* ip = "localhost";
//    addrinfo* result = NULL;
//    iResult = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);
//
//    if (iResult != 0) {
//        WSACleanup();
//        return 12;
//    }
//
//    SOCKET ConnectSocket = INVALID_SOCKET;
//
//    for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
//        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//
//        if (ConnectSocket == INVALID_SOCKET) {
//            WSACleanup();
//            return 13;
//        }
//
//        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//        if (iResult == SOCKET_ERROR) {
//            closesocket(ConnectSocket);
//            ConnectSocket = INVALID_SOCKET;
//            continue;
//        }
//        break;
//    }
//
//    freeaddrinfo(result);
//
//    if (ConnectSocket == INVALID_SOCKET) {
//        cout << "неможливо пiдключитися до сервера. перевiрте, чи запущено процес сервера!\n";
//        WSACleanup();
//        return 14;
//    }
//    else {
//        cout << "пiдключення до сервера пройшло успiшно!\n";
//    }
//
//    /*cout << "Доступні команди:\n";
//    cout << "1. \"як справи\" - сервер відповідає \"чудово\"\n";
//    cout << "2. \"goodbye\" - завершення роботи клієнта\n";*/
//
//    char message[DEFAULT_BUFLEN];
//    char answer[DEFAULT_BUFLEN];
//
//    /*while (true) {
//        cout << "Введіть повідомлення для сервера: ";
//        cin.getline(message, DEFAULT_BUFLEN);
//
//        iResult = send(ConnectSocket, message, (int)strlen(message), 0);
//        if (iResult == SOCKET_ERROR) {
//            cout << "Помилка відправки.\n";
//            break;
//        }
//
//        if (strcmp(message, "goodbye") == 0) {
//            cout << "Завершення роботи клієнта...\n";
//            break;
//        }
//
//        iResult = recv(ConnectSocket, answer, DEFAULT_BUFLEN, 0);
//        if (iResult > 0) {
//            answer[iResult] = '\0';
//            cout << "Відповідь сервера: " << answer << endl;
//        }
//        else {
//            cout << "Сервер закрив з'єднання.\n";
//            break;
//        }
//    }*/
//
//    while (true) {
//        cout << "Введіть ціле число (або 'exit' для завершення): ";
//        cin.getline(message, DEFAULT_BUFLEN);
//
//        if (strcmp(message, "exit") == 0) {
//            send(ConnectSocket, message, (int)strlen(message), 0);
//            break;
//        }
//
//        iResult = send(ConnectSocket, message, (int)strlen(message), 0);
//        if (iResult == SOCKET_ERROR) {
//            cout << "Помилка відправки.\n";
//            break;
//        }
//
//        iResult = recv(ConnectSocket, answer, DEFAULT_BUFLEN, 0);
//        if (iResult > 0) {
//            answer[iResult] = '\0';
//            cout << "Сервер повернув: " << answer << endl;
//        }
//        else {
//            cout << "Сервер закрив з'єднання.\n";
//            break;
//        }
//    }
//
//    closesocket(ConnectSocket);
//    WSACleanup();
//    return 0;
//}

//#define WIN32_LEAN_AND_MEAN
//
//#include <iostream>
//#include <windows.h>
//#include <shellapi.h>
//#include <ws2tcpip.h>
//#include <TlHelp32.h>
//#include <thread>
//
//using namespace std;
//
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015"
//
//#define PAUSE 1
//
//SOCKET ConnectSocket = INVALID_SOCKET;
//
//bool IsServerRunning(const char* serverExe) {
//    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//    if (hProcessSnap == INVALID_HANDLE_VALUE) return false;
//
//    PROCESSENTRY32 pe32;
//    pe32.dwSize = sizeof(PROCESSENTRY32);
//    if (!Process32First(hProcessSnap, &pe32)) {
//        CloseHandle(hProcessSnap);
//        return false;
//    }
//
//    do {
//        if (wcscmp(pe32.szExeFile, L"Server.exe") == 0) {
//            CloseHandle(hProcessSnap);
//            return true;
//        }
//    } while (Process32Next(hProcessSnap, &pe32));
//
//    CloseHandle(hProcessSnap);
//    return false;
//}
//
//void StartServer(const char* serverExePath) {
//    SHELLEXECUTEINFO sei = {};
//    sei.cbSize = sizeof(sei);
//    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
//    sei.lpFile = (LPCWSTR)serverExePath;
//    sei.nShow = SW_SHOW;
//
//    if (!ShellExecuteEx(&sei)) {
//        cout << "Не вдалося запустити сервер!\n";
//    }
//}
//
//DWORD WINAPI Sender(void* param)
//{
//    while (true)
//    {
//        // відправити початковий буфер
//        char* message = new char[200];
//        cout << "Будь ласка, введіть повідомлення для сервера: ";
//        cin.getline(message, 199);
//
//        int iResult = send(ConnectSocket, message, (int)strlen(message), 0);
//        if (iResult == SOCKET_ERROR) {
//            cout << "помилка відправлення: " << WSAGetLastError() << "\n";
//            closesocket(ConnectSocket);
//            WSACleanup();
//            return 15;
//        }
//        else {
//            cout << "дані успішно надіслані на сервер: " << message << "\n";
//            // cout << "байтів з клієнта надіслано: " << iResult << "\n";
//            delete[] message;
//            Sleep(PAUSE);
//        }
//    }
//    return 0;
//}
//
//DWORD WINAPI Receiver(void* param)
//{
//	while (true)
//	{
//		// приймати дані, поки співрозмовник не закриє з'єднання
//		char answer[DEFAULT_BUFLEN];
//
//		int iResult = recv(ConnectSocket, answer, DEFAULT_BUFLEN, 0);
//		answer[iResult] = '\0';
//
//		if (iResult > 0) {
//			cout << "\nпроцес сервера надіслав повідомлення: " << answer << "\n";
//			// cout << "байтів отримано: " << iResult << "\n";
//		}
//		else if (iResult == 0)
//			cout << "з'єднання з сервером закрито.\n";
//		else
//			cout << "помилка прийому: " << WSAGetLastError() << "\n";
//	}
//	return 0;
//}
//
//int main()
//{
//	SetConsoleOutputCP(1251);
//	system("title CLIENT SIDE");
//
//	SetConsoleOutputCP(1251);
//	system("title CLIENT SIDE");
//
//	const char* serverExe = "Server.exe";
//	const wchar_t* serverExePath = L"D:\\папка иры\\Институт\\Клієнт серверне програмування\\Server\\x64\\Debug\\Server.exe";
//
//	if (!IsServerRunning(serverExe)) {
//		cout << "Сервер не запущено. Запускаємо сервер...\n";
//		StartServer((const char*)serverExePath);
//		Sleep(1500); // невелика пауза для запуску
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// ініціалізація Winsock
//	WSADATA wsaData;
//	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) {
//		cout << "не вдалося ініціалізувати Winsock: " << iResult << "\n";
//		return 11;
//	}
//	else {
//		// cout << "підключення Winsock.dll пройшло успішно!\n";
//		Sleep(PAUSE);
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	addrinfo hints;
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	// отримання адреси і порту сервера
//	const char* ip = "localhost"; // за замовчуванням, обидва додатки, і клієнт, і сервер, працюють на одній машині
//	// cout << "Будь ласка, введіть ім'я сервера: ";
//	// cin.getline(ip, 199);
//
//	// iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result); // розкоментувати, якщо потрібно отримати ім'я сервера з командного рядка
//	addrinfo* result = NULL;
//	iResult = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);
//
//	if (iResult != 0) {
//		cout << "getaddrinfo не вдалося: " << iResult << "\n";
//		WSACleanup();
//		return 12;
//	}
//	else {
//		// cout << "отримання адреси і порту клієнта пройшло успішно!\n";
//		Sleep(PAUSE);
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) { // серверів може бути кілька, тому не завадить цикл
//
//		// створення SOCKET для підключення до сервера
//		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//
//		if (ConnectSocket == INVALID_SOCKET) {
//			cout << "не вдалося створити socket: " << WSAGetLastError() << "\n";
//			WSACleanup();
//			return 13;
//		}
//
//		// підключення до сервера
//		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//		if (iResult == SOCKET_ERROR) {
//			closesocket(ConnectSocket);
//			ConnectSocket = INVALID_SOCKET;
//			continue;
//		}
//
//		// cout << "створення socket на клієнті пройшло успішно!\n";
//		Sleep(PAUSE);
//
//		break;
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	freeaddrinfo(result);
//
//	if (ConnectSocket == INVALID_SOCKET) {
//		cout << "неможливо підключитися до сервера!\n";
//		WSACleanup();
//		return 14;
//	}
//	else {
//		// cout << "підключення до сервера пройшло успішно!\n";
//		Sleep(PAUSE);
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	CreateThread(0, 0, Sender, 0, 0, 0);
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   // закрити з'єднання, оскільки більше даних не буде надіслано
//   // iResult = shutdown(ConnectSocket, SD_SEND);
//   // if (iResult == SOCKET_ERROR) {
//   //     cout << "не вдалося закрити з'єднання: " << WSAGetLastError() << "\n";
//   //     closesocket(ConnectSocket);
//   //     WSACleanup();
//   //     return 16;
//   // }
//   // else {
//   //     cout << "клієнт ініціює закриття з'єднання з сервером.\n";
//   // }
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	CreateThread(0, 0, Receiver, 0, 0, 0);
//
//	// очищення
//	//closesocket(ConnectSocket);
//	//WSACleanup();
//
//	//cout << "клієнт завершує свою роботу!\n";
//
//	//return 0;
//	Sleep(INFINITE);
//}


#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <ws2tcpip.h>
#include <TlHelp32.h>
#include <vector>
#include <string>

using namespace std;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "12345"

bool IsServerRunning(const wchar_t* serverExeName) {
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return false;
    }

    do {
        if (wcscmp(pe32.szExeFile, serverExeName) == 0) {
            CloseHandle(hProcessSnap);
            return true;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return false;
}

void StartServer(const wchar_t* serverPath) {
    SHELLEXECUTEINFO sei = {};
    sei.cbSize = sizeof(sei);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpFile = serverPath;
    sei.nShow = SW_SHOW;
    if (!ShellExecuteEx(&sei)) {
        cout << "Failed to start the server!\n";
    }
}

int main() {
    setlocale(0, "Ukrainian");
    system("title CLIENT SIDE");

    const wchar_t* serverExeName = L"Server.exe";
    const wchar_t* serverPath = L"D:\\папка иры\\Институт\\Клієнт серверне програмування\\Server\\x64\\Debug\\Server.exe";

    if (!IsServerRunning(serverExeName)) {
        cout << "Server is not running. Starting the server...\n";
        StartServer(serverPath);
        Sleep(1000);
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed.\n";
        return 1;
    }

    addrinfo hints = {}, * result = NULL;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result) != 0) {
        cout << "getaddrinfo failed.\n";
        WSACleanup();
        return 1;
    }

    SOCKET ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        cout << "Socket creation failed.\n";
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    if (connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        cout << "Could not connect to the server!\n";
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);
    cout << "Connection to the server was successful!\n";

    int choice;
    string login, password;

    while (true) {
        cout << "\n==== MENU ====\n";
        cout << "1. Login\n";
        cout << "2. Registration\n";
        cout << "3. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 3) {
            cout << "Exiting program.\n";
            break;
        }

        if (choice != 1 && choice != 2) {
            cout << "Wrong choice!\n";
            continue;
        }

        cout << "Enter login: ";
        getline(cin, login);
        cout << "Enter password: ";
        getline(cin, password);

        string message = (choice == 1 ? "LOGIN " : "REGISTER ") + login + " " + password;

        send(ConnectSocket, message.c_str(), message.length(), 0);

        char buffer[1024] = {};
        int bytesReceived = recv(ConnectSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            cout << "Server response: " << buffer << endl;
        }
        else {
            cout << "Error receiving response from server.\n";
        }
    }

    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}


//#include <iostream>
//#include <winsock2.h>
//using namespace std;
//
//#pragma comment(lib,"ws2_32.lib") // подключение библиотеки winsock
//#pragma warning(disable:4996)
//
//#define SERVER "127.0.0.1" // ip-адрес сервера (локальный хост)
//#define BUFLEN 512 // максимальная длина ответа
//#define PORT 8888 // порт для приема данных
//
//class UDPClient {
//public:
//    UDPClient() {
//        // инициализация winsock
//        cout << "инициализация winsock...\n";
//        if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
//            cout << "ошибка инициализации. код ошибки: " << WSAGetLastError() << "\n";
//            exit(EXIT_FAILURE);
//        }
//        cout << "инициализация завершена.\n";
//
//        // создание сокета
//        if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
//            cout << "ошибка создания сокета. код ошибки: " << WSAGetLastError() << "\n";
//            exit(EXIT_FAILURE);
//        }
//
//        // настройка структуры адреса сервера
//        memset((char*)&server, 0, sizeof(server));
//        server.sin_family = AF_INET;
//        server.sin_port = htons(PORT);
//        server.sin_addr.S_un.S_addr = inet_addr(SERVER);
//    }
//
//    ~UDPClient() {
//        // закрытие сокета и очистка winsock
//        closesocket(client_socket);
//        WSACleanup();
//    }
//
//    void start() {
//        while (true) {
//            char message[BUFLEN];
//            cout << "введите сообщение: ";
//            cin.getline(message, BUFLEN);
//
//            // отправка сообщения серверу
//            if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
//                cout << "ошибка отправки. код ошибки: " << WSAGetLastError() << "\n";
//                exit(EXIT_FAILURE);
//            }
//            cout << "ожидайте ответ от сервера...\n";
//
//            // получение ответа от сервера
//            char answer[BUFLEN] = {};
//            int slen = sizeof(sockaddr_in);
//            int answer_length;
//
//            if ((answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
//                cout << "ошибка получения данных. код ошибки: " << WSAGetLastError() << "\n";
//                exit(EXIT_FAILURE);
//            }
//
//            cout << "ответ сервера: " << answer << "\n";
//        }
//    }
//
//private:
//    WSADATA ws; // данные winsock
//    SOCKET client_socket; // сокет клиента
//    sockaddr_in server; // адрес сервера
//};
//
//int main() {
//    system("title UDP CLIENT SIDE");
//    setlocale(0, "");
//
//    UDPClient udpClient;
//    udpClient.start();
//}

//#define WIN32_LEAN_AND_MEAN
//
//#include <ws2tcpip.h>
//#include <windows.h>
//#include <iostream>
//#include <string>
//using namespace std;
//
//#pragma comment (lib, "Ws2_32.lib")
//
//#define DEFAULT_BUFLEN 4096
//
//#define SERVER_IP "127.0.0.1"
//#define DEFAULT_PORT "8888"
//
//SOCKET client_socket;
//
//DWORD WINAPI Sender(void* param)
//{
//    // під час запуску клієнта можна запросити його нік, колір повідомлень тощо
//    // string nick;
//    // cin >> nick;
//
//    while (true) {
//        // cout << "Please insert your query for server: ";
//        char query[DEFAULT_BUFLEN];
//        cin.getline(query, DEFAULT_BUFLEN);
//        send(client_socket, query, strlen(query), 0);
//
//        // альтернативний варіант введення даних стрiнгом
//        // string query;
//        // getline(cin, query);
//        // send(client_socket, query.c_str(), query.size(), 0);
//    }
//}
//
//DWORD WINAPI Receiver(void* param)
//{
//    while (true) {
//        char response[DEFAULT_BUFLEN];
//        int result = recv(client_socket, response, DEFAULT_BUFLEN, 0);
//        response[result] = '\0';
//
//        // cout << "...\nYou have new response from server: " << response << "\n";
//        cout << response << "\n";
//        // cout << "Please insert your query for server: ";
//    }
//}
//
//BOOL ExitHandler(DWORD whatHappening)
//{
//    switch (whatHappening)
//    {
//    case CTRL_C_EVENT: // closing console by ctrl + c
//    case CTRL_BREAK_EVENT: // ctrl + break
//    case CTRL_CLOSE_EVENT: // closing the console window by X button
//    case CTRL_LOGOFF_EVENT: // user logs off
//    case CTRL_SHUTDOWN_EVENT: // system is shutting down
//        cout << "Shutting down...\n";
//        Sleep(1000);
//        send(client_socket, "off", 3, 0);
//        return(TRUE);
//        break;
//    default:
//        return FALSE;
//    }
//}
//
//int main()
//{
//    // обробник закриття вікна консолі
//    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ExitHandler, true);
//
//    system("title Client");
//
//    // initialize Winsock
//    WSADATA wsaData;
//    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//    if (iResult != 0) {
//        printf("WSAStartup failed with error: %d\n", iResult);
//        return 1;
//    }
//
//    addrinfo hints = {};
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//
//    // resolve the server address and port
//    addrinfo* result = nullptr;
//    iResult = getaddrinfo(SERVER_IP, DEFAULT_PORT, &hints, &result);
//    if (iResult != 0) {
//        printf("getaddrinfo failed with error: %d\n", iResult);
//        WSACleanup();
//        return 2;
//    }
//
//    addrinfo* ptr = nullptr;
//    // attempt to connect to an address until one succeeds
//    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
//        // create a client-side socket for connecting to server
//        client_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//
//        if (client_socket == INVALID_SOCKET) {
//            printf("socket failed with error: %ld\n", WSAGetLastError());
//            WSACleanup();
//            return 3;
//        }
//
//        // connect to server
//        iResult = connect(client_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
//        if (iResult == SOCKET_ERROR) {
//            closesocket(client_socket);
//            client_socket = INVALID_SOCKET;
//            continue;
//        }
//        break;
//    }
//
//    freeaddrinfo(result);
//
//    if (client_socket == INVALID_SOCKET) {
//        printf("Unable to connect to server!\n");
//        WSACleanup();
//        return 5;
//    }
//
//    string nickname;
//    cout << "Enter your nickname: ";
//    getline(cin, nickname);
//
//    // одразу надіслати нікнейм на сервер
//    send(client_socket, nickname.c_str(), nickname.size(), 0);
//
//    CreateThread(0, 0, Sender, 0, 0, 0);
//    CreateThread(0, 0, Receiver, 0, 0, 0);
//
//    Sleep(INFINITE);
//}