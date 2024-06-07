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

# pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[]) {
	/* STEP 1:
	 * The first step required is to initialize the DLL. Dll (Dynamic Link Library) is
	 * a dynamic library that contains code and data to be used by more than one program
	 * at a time.
	 *
	 * In this step, we need to initialize it with the need to create sockets that will
	 * be used to communicate between the client and server. Additionally, the DLL ensures
	 * that the network-related code is loaded and linked at runtime rather than at compile
	 * time.
	 */
	SOCKET serverSocket, acceptSocket;
	WSADATA wsaData;
	// Formats word into proper format to pass into WSAStartup()
	WORD wVersionRequested = MAKEWORD(2,2); // Version of Winsock
	int wsaerr = WSAStartup(wVersionRequested, &wsaData);
	int port = 59802;
	// Check if DLL is found (WSAStartup returns 0 if passes)
	if (wsaerr == 0) {
		std::cout << "The Winsock dll is found!" << std::endl;
		// Prints WSA status to terminal
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}
	else {
		std::cout << "The Winsock dll is not found!" << std::endl;
	}
	/* STEP 2:
	 * In step 2 we refer to the protocol that will be used. Either UDP or TCP. In this
	 * example TCP (Transmission Control Protocol) will be used. We must create the socket
	 * using the socket function that is bound to a specific transport service provider
	 *
	 * Arguments:
	 * 		af - The address family specification (AF_INET for UDP or TCP)
	 * 		type - The type specification (TCP or UDP)
	 * 		protocol - Protocol specification to be used (IPPROTO_TCP) for TCP
	 */
	SOCKET serverSocket = INVALID_SOCKET;
	// AF_INET for UDP or TCP
	// SOCK_STREAM for TCP
	// IPPROTO_TCP for TCP
	serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (serverSocket==INVALID_SOCKET) {
		std::cout << "Error at socket():" << WSAGetLastError() << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Socket() is OK!" << std::endl;
	}


	return 0;
}
