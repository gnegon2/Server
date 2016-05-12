#pragma once

#include <string>
#include "Client.h"

using namespace std;

class Server
{
public: 
	virtual void startServer() = 0;
	virtual void addNewClient(Client *client) = 0;
	virtual void removeClient(Client *client) = 0;
	virtual void sendMeasurementsToClients() = 0;
	virtual void stopServer() = 0;
	virtual ~Server();
};

