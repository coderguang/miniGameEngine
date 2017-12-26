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

	protected:
		void handleConnect(CSessionPtr session ,boost::system::error_code ex);

	private:
		std::string _ip;
		int _port;
		bool _isInner;
		CSessionPtr _session;
	};


}
#endif