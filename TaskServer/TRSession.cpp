#include "TRSession.h"
#include "TRUtils.h"
//-----------------------------------------------------------------------------
TRSession::TRSession(boost::asio::io_service& ios)
    : m_Socket(ios)
{
    m_Data.resize(TCP_BUFFER_SIZE);
}
//-----------------------------------------------------------------------------
TRSession::~TRSession()
{

}
//-----------------------------------------------------------------------------
boost::asio::ip::tcp::socket& TRSession::get_socket()
{
    return m_Socket;
}
//-----------------------------------------------------------------------------
void TRSession::start_async_read()
{
    m_Socket.async_read_some(
        boost::asio::buffer(m_Data, TCP_BUFFER_SIZE),
        boost::bind(&TRSession::handle_read, this, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}
//-----------------------------------------------------------------------------
void TRSession::handle_read(std::shared_ptr<TRSession>& s, const boost::system::error_code& e, size_t bytes)
{
    std::string client_address = TRUtils::get_socket_address(s);

    if (e)
    {
        //Определим, а вдруг клиент отключился
        if (e == boost::asio::error::connection_reset ||
            e == boost::asio::error::eof)
        {
            std::cout << "Disconnected " << client_address << std::endl;
        }
        else //А вот тут уже ошибка
        {
            std::cout << "Can't read data from client " << client_address << ": " << e.message() << std::endl;
        }
        return;
    }

    std::fill(m_Data.begin(), m_Data.end(), '\0');
    start_async_read();
}
//-----------------------------------------------------------------------------
