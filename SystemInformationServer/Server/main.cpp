#include <boost\asio.hpp>
#include <iostream>
#include <thread>
#include <string>
#include "main.h"
#include "Server.h"
#include "ServerImpl.h"

void testImplementation()
{
	mainServer = new ServerImpl(13);
	thread serverThread(&Server::startServer, mainServer);

	cout << "Type: quit\n"
			"to stop the server\n"
			"and quit the program\n";

	string userInput;
	while (true)
	{
		cin >> userInput;
		if (userInput.compare("quit") == 0)
		{
			mainServer->stopServer();
			break;
		}
	}
	serverThread.join();
	delete mainServer;
}

int main(int argc, char* argv[])
{
	testImplementation();

	system("pause");
	return 0;
}