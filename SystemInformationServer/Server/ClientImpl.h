#pragma once

#include "Client.h"

#include <boost\asio.hpp>

using boost::asio::ip::tcp;

class ClientImpl :
	public Client
{
public:
	ClientImpl(tcp::socket sock);
	~ClientImpl();
};

