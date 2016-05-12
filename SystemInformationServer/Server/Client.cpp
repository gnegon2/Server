#include "Client.h"

Client::Client(tcp::socket sock) : sock(std::move(sock))
{
}

Client::~Client()
{
}
