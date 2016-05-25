// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost\asio.hpp>

using boost::asio::ip::tcp;

using namespace std;

const int maxLength = 1024;

void printInfo()
{
	cout << "System Information Client v1.0" << endl;
	cout << "Authors:" << endl;
	cout << "Mateusz Grzegorzek" << endl;
	cout << "Bartosz Maludzinski\n" << endl;

	cout << "Type an IP address and port of the server you want "
			"to connect: \n";
}

int main()
{
	printInfo();

	string ipAddress;
	cout << "IP address: ";
	cin >> ipAddress;
	unsigned port;
	cout << "Port: ";
	cin >> port;

	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);

		tcp::socket s(io_service);
		tcp::resolver::query query(tcp::v4(), ipAddress, to_string(port));
		tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::connect(s, iterator);

		cout << "\nSuccesfully connected to the server!\n";
		cout << "Start to getting data...\n\n";

		while (true)
		{
			char reply[maxLength];
			size_t reply_length = s.read_some(boost::asio::buffer(reply));
			std::cout.write(reply, reply_length);
		}
	}
	catch (boost::system::system_error &e)
	{
		cerr << endl << __FILE__ << "::" << __LINE__ << "::" << e.what() << endl;
	}
	
	system("pause");
    return 0;
}

