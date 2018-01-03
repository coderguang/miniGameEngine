#ifndef _ENGINE_BASE_SERVER_CLIENT_H_
#define _ENGINE_BASE_SERVER_CLIENT_H_

#include "framework/SmartPoint/refObject.h"
#include "../net/session/session.h"

namespace csg
{
	class CSocketClient :public virtual CRefObject
	{
	public:
		CSocketClient();

		void init(std::string ip ,int port,bool isInner);

		void startConnect();

		void testWrite()
		{
			boost::system::error_code ex;
			handleWrite(_session ,ex);
		};

	protected:
		void handleConnect(CSessionPtr session ,boost::system::error_code ex);

		void handleWrite(CSessionPtr session ,boost::system::error_code ex);

		void disconnect(CSessionPtr session);

		void startRead(CSessionPtr session);

		void handleRead(CSessionPtr session ,boost::system::error_code error ,size_t bytes_transferred);

	private:
		std::string _ip;
		int _port;
		bool _isInner;
		CSessionPtr _session;
	};


}
#endif