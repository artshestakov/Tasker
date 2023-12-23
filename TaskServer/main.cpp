#include "TRServer.h"
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_service ios;
        TRServer s(ios, 23071);
        ios.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
