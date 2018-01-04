#ifndef _ENGINE_NET_SESSION_SESSION_H_
#define _ENGINE_NET_SESSION_SESSION_H_

#include "framework/SmartPoint/refObject.h"
#include "../../def/boost_def.h"
#include "framework/SmartPoint/smartPoint.h"
#include "../protocol/protocol.h"
#include "../../mq/msgBlock.h"

namespace csg
{
	enum ESessionType
	{
		ESessionTypeClient=1,
		ESessionTypeInner=2,
	};

	enum ESessionStatus
	{
		ESessionStatusWaitConnecting=1, //�ȴ�����
		ESessionStatusConnected=2, //������
		ESessionStatusDisConnected=3, //�ѶϿ�
	};

	class IProtocol;
	typedef CSmartPointShare<IProtocol> IProtocolPtr;

	class CRMIObjectBind;
	typedef CSmartPointShare<CRMIObjectBind> CRMIObjectBindPtr;

	typedef std::map<int ,CRMIObjectBindPtr> MapRMIObjectBind;

	class CRMIObject;
	typedef CSmartPointShare<CRMIObject> CRMIObjectPtr;;
	typedef std::map<int ,CRMIObjectPtr> MapRMIObject;
	typedef std::map<std::string ,MapRMIObject> MapEndPointRMIObject; //������Щ���ӿ���ʹ����Щ�ӿ�

	class CSession;
	typedef CSmartPointShare<CSession> CSessionPtr;

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

	public:
		void setProtocol(IProtocolPtr protocol);

		int handleRecvData(const void* inData ,const int len);

		int handleSendData(const CSessionPtr session ,const void* data ,const int len);

		int handlePacketRecvData();

	public:
		//rpc
		int getCallBackId();

		void addCallBackObject(int callBackId ,CRMIObjectBindPtr& object);

		bool getCallBackObject(int callBackId ,CRMIObjectBindPtr& backObject);

	public:
		//msg
		int pushMessage(const CMsgBlockPtr& mb);

	private:
		boost_socket_ptr _socket;
		int _sessionType;
		int _callBackId;
		bool _isInner;
		int _status;
		int _socketId;
	private:
		IProtocolPtr _protocol;
		CLock _readLock;
		CLock _writeLock;

	private:
		MapRMIObject _rmiObjectMap; //��session ���Ե��õ�Զ�̽ӿ�
		MapRMIObjectBind _callBackMap;
	};

}
#endif