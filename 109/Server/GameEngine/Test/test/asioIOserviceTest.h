
#pragma once

#include <vector>
#include <boost/asio.hpp>
#include <boost/thread/detail/singleton.hpp>

class TA {
public:
	~TA() {
		std::cout << "TA destroy" << std::endl;
	}
};

class TB {
public:
	~TB() {
		std::cout << "TB destroy" << std::endl;
	}
};

class TC {
public:
	~TC() {
		std::cout << "TC destroy" << std::endl;
	}
};

class TD {
public:
	~TD() {
		std::cout << "TD destroy" << std::endl;
	}
};

class ASIOA {
public:
	ASIOA() {
		std::cout << "ASIOA build" << std::endl;

		boost::shared_ptr<boost::asio::io_service> tmp_io(new boost::asio::io_service);
		m_io_service = tmp_io;
		boost::shared_ptr<boost::asio::io_service::work> tmp_work(new boost::asio::io_service::work(*m_io_service));
		m_work = tmp_work;
		boost::shared_ptr<boost::thread> tmp(new boost::thread(boost::bind(&boost::asio::io_service::run, &(*m_io_service))));
		m_thread =tmp;

// 		boost::shared_ptr<TC> tmp_tc(new TC);
// 		tc = tmp_tc;
// 		boost::shared_ptr<TD> tmp_td(new TD);
// 		td = tmp_td;
	}
	~ASIOA(){
		std::cout << "ASIOA destroy" << std::endl;
	}
	void stop() {
		m_io_service->stop();
		m_thread->join();
	};

private:
	boost::shared_ptr<boost::thread>	 m_thread;
	boost::shared_ptr<boost::asio::io_service::work> m_work;
	boost::shared_ptr<boost::asio::io_service> m_io_service;
// 	TA ta;
// 	TB tb;
// 	boost::shared_ptr<TC> tc;
// 	boost::shared_ptr<TD> td;
};

class ASIOB {
public:
	ASIOB() {
		boost::shared_ptr<boost::asio::io_service> tmp_io(new boost::asio::io_service);
		m_io_service = tmp_io;
		boost::shared_ptr<boost::asio::io_service::work> tmp_work(new boost::asio::io_service::work(*m_io_service));
		m_work = tmp_work;
		boost::shared_ptr<boost::thread> tmp(new boost::thread(boost::bind(&boost::asio::io_service::run, &(*m_io_service))));
		m_thread = tmp;

// 		boost::shared_ptr<TD> tmp_td(new TD);
// 		td = tmp_td;
// 		boost::shared_ptr<TC> tmp_tc(new TC);
// 		tc = tmp_tc;
	}
	~ASIOB() {
		std::cout << "ASIOB destroy" << std::endl;
	}
	void stop() {
		m_io_service->stop();
		m_thread->join();
	};

private:
	boost::shared_ptr<boost::thread>	 m_thread;
	boost::shared_ptr<boost::asio::io_service> m_io_service;
	boost::shared_ptr<boost::asio::io_service::work> m_work;
// 	TA ta;
// 	TB tb;
// 	boost::shared_ptr<TC> tc;
// 	boost::shared_ptr<TD> td;
};


void testA() {
	std::cout << "call A" << std::endl;
	ASIOA a;
	std::cin.get();
	a.stop();
	std::cout << "call A end" << std::endl;
}

void testB() {
	std::cout << "call B" << std::endl;
	ASIOB b;
	std::cin.get();
	b.stop();
	std::cout << "call B end" << std::endl;
}


int mainTestASIO() {
	
	char c= std::cin.get();
	if ('1' == c)
		testA();
	else if('2'==c)
		testB();
	cin.get();
	return 0;
}