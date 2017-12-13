#ifndef _ENGINE_DEF_BOOST_DEF_
#define _ENGINE_DEF_BOOST_DEF_

#include "boost/asio.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio/io_service.hpp>
//asio def

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> boost_socket_ptr;
//typedef boost::shared_ptr<boost::thread> boost_thread_ptr;
typedef boost::shared_ptr<boost::asio::io_service> boost_io_service_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::acceptor> boost_acceptor_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> boost_work_ptr;



#endif