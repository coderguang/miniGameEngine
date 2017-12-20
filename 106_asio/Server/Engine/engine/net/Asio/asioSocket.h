#ifndef _ENGINE_ASIO_ASIO_SOCKET_H_
#define _ENGINE_ASIO_ASIO_SOCKET_H_

#include "boost/core/noncopyable.hpp"
#include "engine/def/boost_def.h"

namespace csg
{

	class CAsioServer:public virtual boost::noncopyable
	{
	public:
		CAsioServer(bool is_inner,int port);

		void startAccept();


	protected:


	private:
		bool _is_inner; //是否是内部端口
		int _listenPort;
		boost_acceptor_ptr _acceptor;
		boost_io_service_ptr _io_service;
	};
	


}
#endif