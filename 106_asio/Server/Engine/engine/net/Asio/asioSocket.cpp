#include "engine/net/Asio/asioSocket.h"
#include "engine/core/csgServer.h"

using namespace csg;

csg::CAsioServer::CAsioServer(bool is_inner,int port):_listenPort(port),_is_inner(is_inner)
{
	//_io_service = CCsgServiceMgr::instance()->get_io_service();
	//_acceptor = boost_acceptor_ptr(new boost::asio::ip::tcp::acceptor(*_io_service ,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4() ,_listenPort)));
}

void csg::CAsioServer::startAccept()
{

}
