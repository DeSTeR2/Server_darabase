#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <string>
#include "Server.h"

using namespace std;

const string IP = "127.0.0.1";
const char ip[] = "127.0.0.1";
const int port = 8080;

int main()
{
	m1_Server server(1);
	server.start();

	string messages[3] = {
		"<html>Hello Word 1</html>",
		"<html>Hello Word 2</html>",
		"<html>Hello Word 3</html>"
	};

	int counter = 0;

	while (true) {
		counter %= 3;
		server.sentMessage(messages[counter]);
		counter++;
	}
}

