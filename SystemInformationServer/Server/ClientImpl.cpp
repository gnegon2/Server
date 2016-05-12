#include "ClientImpl.h"

#include <boost\asio.hpp>

using boost::asio::ip::tcp;

ClientImpl::ClientImpl(tcp::socket sock) : Client(std::move(sock))
{
}


ClientImpl::~ClientImpl()
{
}
