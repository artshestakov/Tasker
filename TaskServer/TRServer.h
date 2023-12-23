#pragma once
//-----------------------------------------------------------------------------
#include "TRSession.h"
//-----------------------------------------------------------------------------
class TRServer
{
public:
    TRServer(boost::asio::io_service& ios, int port);
    ~TRServer();

    void handle_accept(std::shared_ptr<TRSession> s, const boost::system::error_code& e);

private:
    void start_async_accept(std::shared_ptr<TRSession> s);

private:
    boost::asio::io_service& m_IOS;
    boost::asio::ip::tcp::acceptor m_Acceptor;
};
//-----------------------------------------------------------------------------
