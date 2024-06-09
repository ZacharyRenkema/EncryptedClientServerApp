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
// # include "stdafx.h"

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
	serverSocket = INVALID_SOCKET; // Do not redeclare
	// AF_INET for UDP or TCP
	// SOCK_STREAM for TCP
	// IPPROTO_TCP for TCP
	serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Error at socket():" << WSAGetLastError() << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Socket() is OK!" << std::endl;
	}
	// When creating a socket remember to close the socket with "int closesocket(Socket s);"
	/* STEP 3:
	 * In step 3, after creating our socket we must bind the ip address and the port to the socket.
	 * Refer to diagram in notes for visual description...
	 *
	 * Arguments:
	 * 		s: Descriptor identitifying an unbound socket.
	 * 		name: Address to assign to the socket from the sockaddr stucture
	 * 		socklen: Length in bytes of the address structure.
	 *
	 * If no error occurs, bind() return 0. Otherwise, it returns SOCKET_ERROR
	 */
	sockaddr_in service;
	service.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &service.sin_addr.s_addr);
	service.sin_port = htons(port);

	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
	    std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
	    closesocket(serverSocket);
	    WSACleanup();

	    return 1; // Exit if binding fails
	}
	else {
	    std::cout << "bind() is OK!" << std::endl;
	}
	/* STEP 4:
	 * Step 4 is the listenting stage. In this step we must place the server socket in a state where it listens
	 * for incoming connections.
	 *
	 * Arguments:
	 * 		s: Descriptor identifyinf a bound, unconnected socket.
	 * 		backlog: The maximum number of connections allowed (also OS dependant).
	 *
	 * If no errors occur, return 0. Otherwise, it returns SOCKET_ERROR
	 */
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "Listen(): Error listening on socket" << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "Listening is sucessful" << std::endl;
	}
	/* STEP 4:
	 * Accept. In this step we must call the accept function which listens for a connection from another client. With
	 * this function it returns another function. Referring back to the visualization, this function actually makes a duplicate
	 * of the existing socket passed into it.
	 *
	 * Arguments:
	 * 		s: Descriptor that identifies a socket that has been placed in the listening state.
	 * 		addr: Optional struicture containing the client address information
	 * 		addrlen: Optional size of the address structure (if included)
	 *
	 * 	If no errors occur, the function returns a duplicate socket.
	 */
	SOCKET acceptSocket;
	acceptSocket = accept(serverSocket, NULL, NULL);

	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
		// Cleanup to conserve resources
		WSACleanup();
		return -1;
	}


	return 0;
}
