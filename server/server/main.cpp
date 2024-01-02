#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <string>
#include "Server.h"
#include "Server.h"

using namespace std;

const string IP = "127.0.0.1";
const char ip[] = "127.0.0.1";
const int port = 8080;

int main()
{
	m1_Server server(1);
	server.start();

	

	server.createClient();
	server.createClient();
	server.createClient();
	server.createClient();

	server.sentAllClients();
}

