#ifndef _ENGINE_DEF_BOOST_DEF_
#define _ENGINE_DEF_BOOST_DEF_

#include "boost/asio.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>
//asio def

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> boost_socket_ptr;
typedef boost::shared_ptr<boost::thread> boost_thread_ptr;  //don't use boost/thread/detail/thread.hpp it make build error
typedef boost::shared_ptr<boost::asio::io_service> boost_io_service_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::acceptor> boost_acceptor_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> boost_work_ptr;



#endif