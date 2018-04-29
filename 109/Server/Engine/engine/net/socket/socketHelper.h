#ifndef _ENGINE_NET_SOCKET_SOCKET_HELPER_H_
#define _ENGINE_NET_SOCKET_SOCKET_HELPER_H_

#include "engine/net/session/session.h"
#include "boost/system/error_code.hpp"

namespace csg {
	class CSocketHelper {
	public:
		static void startRead(CSessionPtr session);

		static void handleRead(CSessionPtr session, boost::system::error_code error, size_t bytes_transferred);

		static void disconnect(CSessionPtr session, ESessionDisconnectReason reason);
	};

}
#endif