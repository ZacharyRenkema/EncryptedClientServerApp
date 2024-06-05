#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// Library Includes
# include <iostream>
// Winsock Includes
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

# pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[]) {
	SOCKET serverSocket, acceptSocket;
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2,2);
	int wsaerr = WSAStartup(wVersionRequested, &wsaData);
	int port = 59802;

	if (wsaerr != 0) {
		std::cout << "The Winsock dll is not found!" << std::endl;
	}
	else {
		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}


	return 0;
}
