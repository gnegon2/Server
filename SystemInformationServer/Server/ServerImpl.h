#pragma once

#include <mutex>
#include <vector>
#include "Server.h"
#include "Client.h"
#include "Info.h"
#include "CpuInfo.h"

class ServerImpl :
	public Server
{
	thread *senderThread;
	boost::asio::io_service *io_service;
	unsigned short port;

	bool isRunning;
	vector<string> measurements;
	vector<Info*> info;
	vector<Client*> clients;

	mutex isRunningMutex;
	mutex clientsMutex;

	void addMeasurements();
	vector<string> getMeasurements();
	bool checkMeasurements(vector<string> newMeasurements);

public:
	ServerImpl(unsigned short port);
	void startServer();
	void addNewClient(Client * client);
	void removeClient(Client * client);
	void sendMeasurementsToClients();
	void stopServer();
	~ServerImpl();
};

