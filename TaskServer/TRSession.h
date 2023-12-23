#pragma once
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
class TRSession : public std::enable_shared_from_this<TRSession>
{
public:
    TRSession(boost::asio::io_service& ios);
    virtual ~TRSession();

    boost::asio::ip::tcp::socket& get_socket();
    void start_async_read();
    void handle_read(std::shared_ptr<TRSession>& s, const boost::system::error_code& e, size_t bytes);

private:
    boost::asio::ip::tcp::socket m_Socket;
    std::vector<char> m_Data;
};
//-----------------------------------------------------------------------------
