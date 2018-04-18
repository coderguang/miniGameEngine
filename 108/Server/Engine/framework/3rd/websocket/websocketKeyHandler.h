#ifndef _FRAMEWORK_3RD_WEBSOCKET_WEBSOCKET_HELPER_H_
#define _FRAMEWORK_3RD_WEBSOCKET_WEBSOCKET_HELPER_H_

#include "engine/serialize/bytesbuffer.h"
#include <map>
#include "../../SmartPoint/smartPoint.h"
#include "../../SmartPoint/refObject.h"

namespace csg {

	class CWebSocketKeyHandler :public CRefObject{
	public:
		CWebSocketKeyHandler(const CBytesBuffer& data);

		bool getClientReqKey(const CBytesBuffer& data);

		int fetchHttpInfo();

		int fetchHttpInfo(const CBytesBuffer& data);

		std::string getRespondStr();

		void printMsg();
	private:
		CBytesBuffer _head_buffer;
	public:
		std::map<std::string, std::string> _head_key_map;
	};

	typedef CSmartPointShare<CWebSocketKeyHandler> CWebSocketKeyHandlerPtr;

}
#endif