#ifndef _ENGINE_BASE_SERVER_SOCKET_SERVER_H_
#define _ENGINE_BASE_SERVER_SOCKET_SERVER_H_

#include "framework/SmartPoint/refObject.h"
#include "../def/boost_def.h"
#include "../net/session/session.h"
#include "boost/smart_ptr/enable_shared_from_this.hpp"

namespace csg
{
	class CSocketServer:public virtual boost::enable_shared_from_this<CSocketServer>
	{
	public:
		void init(int port ,bool isInner ,int sessionType);

		int getPort()const;

		bool isInner()const;

		int startListen();
	
		void stop();

	protected:
		void startAccept();

		void handleAccept(CSessionPtr session ,const boost::system::error_code& err);

	private:
		unsigned short _port;
		bool _isInner;
		int _sessionType;
		boost_acceptor_ptr acceptor;
	};


	typedef boost::shared_ptr<CSocketServer> boost_CSocketServer_ptr;

}
#endif