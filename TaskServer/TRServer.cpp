#include "TRServer.h"
#include "TRUtils.h"
//-----------------------------------------------------------------------------
TRServer::TRServer(boost::asio::io_service& ios, int port)
    : m_IOS(ios), m_Acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    start_async_accept(std::make_shared<TRSession>(m_IOS));
}
//-----------------------------------------------------------------------------
TRServer::~TRServer()
{

}
//-----------------------------------------------------------------------------
void TRServer::handle_accept(std::shared_ptr<TRSession> s, const boost::system::error_code& e)
{
    if (e)
    {
        std::cout << "Can't accept connect from client: " + e.message() << std::endl;
        s.reset();
        return;
    }

    std::cout << "Accepted connection from " << TRUtils::get_socket_address(s) << std::endl;

    s->start_async_read();
    s = std::make_shared<TRSession>(m_IOS);
    start_async_accept(s);
}
//-----------------------------------------------------------------------------
void TRServer::start_async_accept(std::shared_ptr<TRSession> s)
{
    m_Acceptor.async_accept(s->get_socket(),
        boost::bind(&TRServer::handle_accept, this, s,
            boost::asio::placeholders::error));
}
//-----------------------------------------------------------------------------
