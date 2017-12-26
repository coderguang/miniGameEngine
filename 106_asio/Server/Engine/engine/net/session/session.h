#ifndef _ENGINE_NET_SESSION_SESSION_H_
#define _ENGINE_NET_SESSION_SESSION_H_

#include "framework/SmartPoint/refObject.h"
#include "../../def/boost_def.h"
#include "framework/SmartPoint/smartPoint.h"

namespace csg
{
	enum ESessionType
	{
		ESessionTypeClient=1,
		ESessionTypeInner=2,
	};

	enum ESessionStatus
	{
		ESessionStatusWaitConnecting=1, //等待连接
		ESessionStatusConnected=2, //已连接
		ESessionStatusDisConnected=3, //已断开
	};

	class CSession:public virtual CRefObject
	{
	public:
		CSession();

		virtual ~CSession();

		void setInner(bool isInner);

		bool isInner()const;

		void setSocket(boost_socket_ptr& socket);

		boost_socket_ptr& getSocket();

		void setType(int type);

		int getType()const;

		void setStatus(int status);

		int getStatus();

		void setSocketId(int id);

		int getSocketId()const;

	private:
		boost_socket_ptr _socket;
		int _sessionType;
		int _callBackId;
		bool _isInner;
		bool _status;
		int _socketId;
	};

	typedef CSmartPointShare<CSession> CSessionPtr;

}
#endif