#pragma once
#include "v_Client.h"
#include "v_Client.h"

#include <iostream>
#include <WinSock2.h>
#include <string>
#include <map>
using namespace std;

class m1_Server
{
public:
	const string IP = "127.0.0.1";
	const char ip[10] = "127.0.0.1";
	const int port = 8080;
	SOCKET wsocket;
	SOCKET new_wsocket;
	WSADATA wsaData;
	struct sockaddr_in server;
	int server_len;
	int buffer_size = 600000;

	map<string, bool> c_emails;
	map<string, v_Client> clients;

	v_Client activeClient;

	m1_Server(int n) {}
	~m1_Server() {
		closesocket(wsocket);
		WSACleanup();
	}

	virtual int start() {
		cout << "Start server initialization\n";

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

		return 0;
	}

	virtual void sentMessage(string response) {
		int bytes = 0;
		//while (true) {
			new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
			if (new_wsocket == INVALID_SOCKET) {
				cout << "Can not accept\n";
			}

			char buff[600000] = { 0 };
			bytes = recv(new_wsocket, buff, buffer_size, 0);
			if (bytes < 0) {
				cout << "Can not read client request\n";
			}

			string serverMessage = "HTTP/1.1 200 OK\nContent-type: TEXT/html\nContent-len: ";
			//string response = "<html><h1>Hello Word</h1></html>";
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
		//}
	}

	virtual bool createClient() {
		system("cls");
		cout << "Create new account\nEnter email: ";
		string email;
		cin >> email;

		if (c_emails[email] == true) {
			cout << "Account with this email exist\nWant to login? (y/n)\n";
			char a;
			cin >> a;
			if (a == 'y') this->loginIntoClient();
			cout << "Registration end\n";
			return false;
		}

		cout << "Enter password: ";
		string password;
		cin >> password;

		cout << "Enter username: ";
		string userName;
		cin >> userName;
		//v_Client client(email, password, userName);
		clients[email] = v_Client(email, password, userName);
		c_emails[email] = true;

		cout << "Account created succesfully!\n";
		return true;
	}

	virtual bool loginIntoClient() {
		system("cls");
		cout << "Login into account\n";
		cout << "Enter email: ";
		string email;
		cin >> email;
		if (c_emails[email] == false) {
			cout << "There is no accounts with such email\n";
			return false;
		}

		cout << "Enter password: ";
		string password;
		cin >> password;

		v_Client client = clients[email];
		if (password == client.getPassword())
		{
			cout << "Login succesfully\n";
			activeClient = client;
		}
		else {
			cout << "Invalid password\n"; 
			return false;
		}
		return true;
	}

	void sentAllClients() {
		string message = "<html>";
		
		for (auto client_ : clients) {
			v_Client client = client_.second;
			message += "<h1>" + client.getEmail() + " | " + client.getPassword() + " | " + client.getUserName() + " | " + to_string(client.getScore()) + " | " + "</h1>";
		}
		message += "</html>";

		this->sentMessage(message);
	}
};

