# ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
# endif
// Library Includes
# include <iostream>
// Winsock Includes
# include <windows.h>
# include <winsock2.h>
# include <ws2tcpip.h>
# include <iphlpapi.h>
# include <stdio.h>

int main(int argc, char* argv[]) {
	// STEPS 1 - 3 Are same for client
	SOCKET clientSocket;
	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;
	int port = 59802;
	int wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr == 0) {
		std::cout << "The client Winsock DLL is found!" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}
	else {
		std::cout << "The Winsock DLL is not found!" << std::endl;
		return 0;
	}

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Error at socket():" << WSAGetLastError() << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Socket() is OK!" << std::endl;
	}
	/* STEP 3: CONNECT
	 * In this step the client differs from the server. Step 3 connects to the server
	 * using the connect function.
	 *
	 * Arguments:
	 * 		s: Descriptor identitifying an unbound socket. (Client socket)
	 * 		addr: Structure containing server IP address and port.
	 * 		addrlen: Size in bytes of addr structure
	 *
	 * 	Connect will wait 75 seconds for server to respond
	 * 	Returns 0 if successful or Socket_error if not
	 */
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		std::cout << "Client: connect() - Failed to connect." << std::endl;
		WSACleanup();

		return 0;
	}
	else {
		std::cout << "Client: connect() OK." << std::endl;
		std::cout << "Cliend: can start sending and receiving data..." << std::endl;
	}

	return 0;
}
