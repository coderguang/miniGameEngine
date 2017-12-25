#ifndef _ENGINE_DEF_BOOST_DEF_
#define _ENGINE_DEF_BOOST_DEF_

#include "boost/asio.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>
//asio def

typedef boost::asio::ip::tcp::socket boost_socket;
typedef boost::shared_ptr<boost_socket> boost_socket_ptr;
typedef boost::thread boost_thread;
typedef boost::shared_ptr<boost_thread> boost_thread_ptr;  //don't use boost/thread/detail/thread.hpp it make build error
typedef boost::asio::io_service boost_io_service;
typedef boost::shared_ptr<boost_io_service> boost_io_service_ptr;
typedef boost::asio::ip::tcp::acceptor boost_acceptor;
typedef boost::shared_ptr<boost_acceptor> boost_acceptor_ptr;
typedef boost::asio::io_service::work boost_work;
typedef boost::shared_ptr<boost_work> boost_work_ptr;



#endif