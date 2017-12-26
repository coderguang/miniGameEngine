#ifndef _ENGINE_BASE_SERVER_SOCKET_SERVER_H_
#define _ENGINE_BASE_SERVER_SOCKET_SERVER_H_

#include "framework/SmartPoint/refObject.h"
#include "../def/boost_def.h"
#include "../net/session/session.h"

namespace csg
{
	class CSocketServer:public virtual CRefObject
	{
	public:
		void init(int port ,bool isInner ,int sessionType);

		int getPort()const;

		bool isInner()const;

		void startListen();
	
	protected:
		void startAccept();

		void handleAccept(CSessionPtr session ,const boost::system::error_code& err);

		void startRead(CSessionPtr& session);

		void handleRead(CSessionPtr& session ,boost::system::error_code error ,size_t bytes_transferred);

		void disconnect(CSessionPtr& session);

	private:
		int _port;
		bool _isInner;
		int _sessionType;
		boost_acceptor_ptr acceptor;
	};

}
#endif