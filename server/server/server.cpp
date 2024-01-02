#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <string>

using namespace std;

const string IP = "127.0.0.1";
const char ip[] = "127.0.0.1";
const int port = 8080;

int main()
{
	cout << "Start server initialization\n";

	SOCKET wsocket;
	SOCKET new_wsocket;
	WSADATA wsaData;
	struct sockaddr_in server;
	int server_len;
	int buffer_size = 30720;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "Can not WSAStartup\n";
		return -1;
	}

	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET) {
		cout << "Can not create socket\n";
		return -2;
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(port);
	server_len = sizeof(server);

	if (bind(wsocket, (SOCKADDR*)&server, server_len) != 0) {
		cout << "Can not bind socket\n";
		return -3;
	}

	if (listen(wsocket, 20) != 0) {
		cout << "Can not start listening\n";
		return -4;
	}

	cout << "Server started. Server adress: " + IP + ":" + to_string(port) + "\n";

	int bytes = 0;
	while (true) {
		new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
		if (new_wsocket == INVALID_SOCKET) {
			cout << "Can not accept\n";
		}

		char buff[30720] = { 0 };
		bytes = recv(new_wsocket, buff, buffer_size,0);
		if (bytes < 0) {
			cout << "Can not read client request\n";
		}

		string serverMessage = "HTTP/1.1 200 OK\nContent-type: TEXT/html\nContent-len: ";
		string response = "<html><h1>Hello Word</h1></html>";
		serverMessage += to_string(response.size()) + "\n\n" + response;
		
		int bytesSent = 0;
		int totalBytes = 0;
		while (totalBytes < serverMessage.size()) {
			bytesSent = send(new_wsocket, serverMessage.c_str(), serverMessage.size(), 0);
			if (bytesSent < 0) {
				cout << "Can not send response\n";
			}

			totalBytes += bytesSent;
		}

		cout << "Sent responce to client\n";
		closesocket(new_wsocket);
	}

	closesocket(wsocket);
	WSACleanup();
}

