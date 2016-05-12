#pragma once

#include <boost\asio.hpp>

using boost::asio::ip::tcp;

class Client
{
public:
	tcp::socket sock;
	Client(tcp::socket sock);
	virtual ~Client();
};

