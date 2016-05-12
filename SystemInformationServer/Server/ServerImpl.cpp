#include <vector>
#include <string>
#include <boost\asio.hpp>
#include "ServerImpl.h"
#include "CpuInfo.h"
#include "MemoryInfo.h"

#include <iostream>

ServerImpl::ServerImpl(unsigned short port) : port(port)
{
	addMeasurements();
	measurements = getMeasurements();
}

void ServerImpl::startServer()
{
	isRunning = true;
	senderThread = new thread(&Server::sendMeasurementsToClients, this);
	io_service = new boost::asio::io_service;
	tcp::acceptor a(*io_service, tcp::endpoint(tcp::v4(), port));
	while(true)
	{
		std::this_thread::sleep_for(1s);
		unique_lock<std::mutex> isRunningLock(isRunningMutex);
		if (isRunning)
		{
			isRunningLock.unlock();
			tcp::socket sock(*io_service);
			try 
			{
				a.accept(sock);
			}
			catch (boost::system::system_error &e)
			{
				break;
			}
			Client *client = new Client(std::move(sock));
			this->addNewClient(client);
		}
		else
		{
			break;
		}
	}
}

void ServerImpl::addMeasurements()
{
	CpuInfo *cpuInfo = new CpuInfo;
	MemoryInfo *memoryInfo = new MemoryInfo;

	info.push_back(cpuInfo);
	info.push_back(memoryInfo);
}

void ServerImpl::addNewClient(Client *client)
{
	unique_lock<std::mutex> clientsLock(clientsMutex);
	clients.push_back(client);
}

void ServerImpl::removeClient(Client *client)
{
	for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it) == client)
		{
			clients.erase(it);
			break;
		}
	}
}

vector<string> ServerImpl::getMeasurements()
{
	vector<string> newMeasurements;
	for (Info *i : info)
	{
		newMeasurements.push_back(i->getInfo());
	}
	return newMeasurements;
}

bool ServerImpl::checkMeasurements(vector<string> newMeasurements)
{
	bool measurementsHasChanged = false;
	unsigned measNumber = 0;
	for (string &meas : newMeasurements)
	{
		if (meas.compare(measurements.at(measNumber)) != 0 )
		{
			measurementsHasChanged = true;
			break;
		}
		measNumber++;
	}
	return measurementsHasChanged;
}

void ServerImpl::sendMeasurementsToClients()
{
	while (true)
	{
		std::this_thread::sleep_for(1s);
		unique_lock<std::mutex> isRunningLock(isRunningMutex);
		if (isRunning)
		{
			isRunningLock.unlock();
			unique_lock<std::mutex> clientsLock(clientsMutex);
			if (clients.size() > 0)
			{
				vector<string> newMeasurements = getMeasurements();
				if (checkMeasurements(newMeasurements))
				{
					measurements = newMeasurements;
					string newLine = "\r\n";
					vector<Client*> disconnectedClients;
					for (Client *c : clients)
					{
						try
						{
							for (string &s : measurements)
							{
								boost::asio::write(c->sock, boost::asio::buffer(s));
								boost::asio::write(c->sock, boost::asio::buffer(newLine));
							}
							boost::asio::write(c->sock, boost::asio::buffer(newLine));
						}
						catch (boost::system::system_error &e)
						{
							disconnectedClients.push_back(c);
							cout << __FILE__ << "::" << __LINE__ << "::" << e.what() << endl;
						}
					}
					if (disconnectedClients.size() > 0)
					{
						for (Client *c : disconnectedClients)
						{
							removeClient(c);
						}
					}
				}
			}
		}
		else
		{
			break;
		}
	}
}

void ServerImpl::stopServer()
{
	delete io_service;
	unique_lock<std::mutex> isRunningLock(isRunningMutex);
	isRunning = false;
}

ServerImpl::~ServerImpl()
{
	for (Client *c : clients)
	{
		c->sock.close();
	}
	for (Info *i : info)
	{
		delete i;
	}
	senderThread->join();
	delete senderThread;
}
