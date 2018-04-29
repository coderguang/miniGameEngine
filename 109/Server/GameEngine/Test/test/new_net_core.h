#pragma once
#include <boost/thread/detail/singleton.hpp>
#include <vector>

#define net_new_core_csg boost::detail::thread::singleton<new_net_core>::instance()
#define IO_SERVICE_NUM 1

namespace fytx {
	typedef boost::shared_ptr<boost::asio::io_service>			io_service_ptr;
	typedef boost::shared_ptr<boost::asio::io_service::work>	work_ptr;
	typedef boost::shared_ptr<boost::thread>					thread_ptr;
}

using namespace fytx;

class new_net_core
{

public:
	new_net_core() {
		std::cout << "new_net_core build" << std::endl;
	};
	~new_net_core() {
		std::cout << "new_net_core destroy" << std::endl;
	};

	void init() {
		for (int i = 0; i < IO_SERVICE_NUM; ++i)
		{
			io_service_ptr servicePtr(new boost::asio::io_service);
			work_ptr work(new boost::asio::io_service::work(*servicePtr));
			test_ServiceVec.push_back(servicePtr);
			test_WorkVec.push_back(work);
		};
		std::cout << __FUNCTION__ << std::endl;
	}

	void run() {
		for (std::size_t i = 0; i < test_ServiceVec.size(); ++i)
		{
			boost::shared_ptr<boost::thread> threadPtr(new boost::thread(
				boost::bind(&boost::asio::io_service::run, test_ServiceVec[i])));
			m_ThreadVec.push_back(threadPtr);
		}
		std::cout << __FUNCTION__ << std::endl;
	};

	void stop() {
		for (std::size_t i = 0; i < test_ServiceVec.size(); ++i)
			test_ServiceVec[i]->stop();
		for (std::size_t i = 0; i < m_ThreadVec.size(); ++i)
			m_ThreadVec[i]->join();
		std::cout << __FUNCTION__ << std::endl;
	};

private:
	std::vector<thread_ptr>			m_ThreadVec;
	std::vector<work_ptr>			test_WorkVec;
	std::vector<io_service_ptr>		test_ServiceVec;
};


