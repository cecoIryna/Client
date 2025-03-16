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

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <ws2tcpip.h>
#include <TlHelp32.h>
#include <thread>

using namespace std;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#define PAUSE 1

SOCKET ConnectSocket = INVALID_SOCKET;

bool IsServerRunning(const char* serverExe) {
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe32;
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

void StartServer(const char* serverExePath) {
    SHELLEXECUTEINFO sei = {};
    sei.cbSize = sizeof(sei);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpFile = (LPCWSTR)serverExePath;
    sei.nShow = SW_SHOW;

    if (!ShellExecuteEx(&sei)) {
        cout << "Не вдалося запустити сервер!\n";
    }
}

DWORD WINAPI Sender(void* param)
{
    while (true)
    {
        // відправити початковий буфер
        char* message = new char[200];
        cout << "Будь ласка, введіть повідомлення для сервера: ";
        cin.getline(message, 199);

        int iResult = send(ConnectSocket, message, (int)strlen(message), 0);
        if (iResult == SOCKET_ERROR) {
            cout << "помилка відправлення: " << WSAGetLastError() << "\n";
            closesocket(ConnectSocket);
            WSACleanup();
            return 15;
        }
        else {
            cout << "дані успішно надіслані на сервер: " << message << "\n";
            // cout << "байтів з клієнта надіслано: " << iResult << "\n";
            delete[] message;
            Sleep(PAUSE);
        }
    }
    return 0;
}

DWORD WINAPI Receiver(void* param)
{
	while (true)
	{
		// приймати дані, поки співрозмовник не закриє з'єднання
		char answer[DEFAULT_BUFLEN];

		int iResult = recv(ConnectSocket, answer, DEFAULT_BUFLEN, 0);
		answer[iResult] = '\0';

		if (iResult > 0) {
			cout << "\nпроцес сервера надіслав повідомлення: " << answer << "\n";
			// cout << "байтів отримано: " << iResult << "\n";
		}
		else if (iResult == 0)
			cout << "з'єднання з сервером закрито.\n";
		else
			cout << "помилка прийому: " << WSAGetLastError() << "\n";
	}
	return 0;
}

int main()
{
	SetConsoleOutputCP(1251);
	system("title CLIENT SIDE");

	SetConsoleOutputCP(1251);
	system("title CLIENT SIDE");

	const char* serverExe = "Server.exe";
	const wchar_t* serverExePath = L"D:\\папка иры\\Институт\\Клієнт серверне програмування\\Server\\x64\\Debug\\Server.exe";

	if (!IsServerRunning(serverExe)) {
		cout << "Сервер не запущено. Запускаємо сервер...\n";
		StartServer((const char*)serverExePath);
		Sleep(1500); // невелика пауза для запуску
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ініціалізація Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "не вдалося ініціалізувати Winsock: " << iResult << "\n";
		return 11;
	}
	else {
		// cout << "підключення Winsock.dll пройшло успішно!\n";
		Sleep(PAUSE);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// отримання адреси і порту сервера
	const char* ip = "localhost"; // за замовчуванням, обидва додатки, і клієнт, і сервер, працюють на одній машині
	// cout << "Будь ласка, введіть ім'я сервера: ";
	// cin.getline(ip, 199);

	// iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result); // розкоментувати, якщо потрібно отримати ім'я сервера з командного рядка
	addrinfo* result = NULL;
	iResult = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);

	if (iResult != 0) {
		cout << "getaddrinfo не вдалося: " << iResult << "\n";
		WSACleanup();
		return 12;
	}
	else {
		// cout << "отримання адреси і порту клієнта пройшло успішно!\n";
		Sleep(PAUSE);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) { // серверів може бути кілька, тому не завадить цикл

		// створення SOCKET для підключення до сервера
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			cout << "не вдалося створити socket: " << WSAGetLastError() << "\n";
			WSACleanup();
			return 13;
		}

		// підключення до сервера
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}

		// cout << "створення socket на клієнті пройшло успішно!\n";
		Sleep(PAUSE);

		break;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		cout << "неможливо підключитися до сервера!\n";
		WSACleanup();
		return 14;
	}
	else {
		// cout << "підключення до сервера пройшло успішно!\n";
		Sleep(PAUSE);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	CreateThread(0, 0, Sender, 0, 0, 0);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

   // закрити з'єднання, оскільки більше даних не буде надіслано
   // iResult = shutdown(ConnectSocket, SD_SEND);
   // if (iResult == SOCKET_ERROR) {
   //     cout << "не вдалося закрити з'єднання: " << WSAGetLastError() << "\n";
   //     closesocket(ConnectSocket);
   //     WSACleanup();
   //     return 16;
   // }
   // else {
   //     cout << "клієнт ініціює закриття з'єднання з сервером.\n";
   // }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	CreateThread(0, 0, Receiver, 0, 0, 0);

	// очищення
	//closesocket(ConnectSocket);
	//WSACleanup();

	//cout << "клієнт завершує свою роботу!\n";

	//return 0;
	Sleep(INFINITE);
}
