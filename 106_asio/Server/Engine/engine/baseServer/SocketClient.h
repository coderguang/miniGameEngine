#ifndef _ENGINE_BASE_SERVER_CLIENT_H_
#define _ENGINE_BASE_SERVER_CLIENT_H_

#include "framework/SmartPoint/refObject.h"
#include "../net/session/session.h"
#include "boost/smart_ptr/enable_shared_from_this.hpp"
#include "../mq/msgBlock.h"

namespace csg
{
	class CSocketClient :public virtual boost::enable_shared_from_this<CSocketClient>
	{
	public:
		CSocketClient();

		void init(std::string ip ,int port,bool isInner);

		void startConnect();

		void pushMessage(const CMsgBlockPtr& mb);

		CSessionPtr getSession();

	protected:
		void handleConnect(CSessionPtr session ,boost::system::error_code ex);

		void disconnect(CSessionPtr session);

		void startRead(CSessionPtr session);

		void handleRead(CSessionPtr session ,boost::system::error_code error ,size_t bytes_transferred);

	private:
		std::string _ip;
		int _port;
		bool _isInner;
		CSessionPtr _session;
	};

	typedef boost::shared_ptr<CSocketClient> boost_CSocketClient_ptr;

}
#endif