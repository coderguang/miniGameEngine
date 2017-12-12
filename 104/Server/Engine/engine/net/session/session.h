#ifndef _ENGINE_NET_SESSION_SESSION_H_
#define _ENGINE_NET_SESSION_SESSION_H_

#include "framework/SmartPoint/refObject.h"
#include "framework/SmartPoint/smartPoint.h"
#include "../protocol/protocol.h"
#include "../../mq/msgBlock.h"
#include "../../rpc/rmiObjectAdapter.h"
#include "../../rpc/rmiObject.h"

namespace csg
{
	class CProtocol;
	typedef CSmartPointShare<CProtocol> CProtocolPtr;

	class CRMIObjectBind;
	typedef CSmartPointShare<CRMIObjectBind> CRMIObjectBindPtr;

	typedef std::map<int ,CRMIObjectBindPtr> MapRMIObjectBind;

	class CRMIObject;
	typedef CSmartPointShare<CRMIObject> CRMIObjectPtr;;
	typedef std::map<int ,CRMIObjectPtr> MapRMIObject;
	typedef std::map<std::string ,MapRMIObject> MapEndPointRMIObject; //������Щ���ӿ���ʹ����Щ�ӿ�

	class CSession :public virtual CRefObject
	{
	public:
		CSession(int socketfd ,std::string& addr ,int port,bool isInner);

		void setSocketfd(int fd);

		int getSocketfd()const;

		void print(std::string info);

		virtual ~CSession();

		void setProtocol(CProtocolPtr& protocol);

		bool onRecvData(const void* buf ,int len);

		bool addRMIObject(const MapRMIObject& objects);

		int getCallBackId();

		void addCallBackObject(int callBackId ,CRMIObjectBindPtr& object);

		bool getCallBackObject(int callBackId ,CRMIObjectBindPtr& backObject);

	public:
		void handlePacket();

		bool pushMessage(const CMsgBlockPtr& mb);

	private:
		CLock& getNetRecvIoLock();

		CLock& getNetSendIoLock();

		void setGetMsgFlag(bool b);

		bool isGetMsg();

	private:
		int _socketfd;
		std::string _remoteAddr;
		int _remotePort;
		bool _isClient;
		CProtocolPtr _protocol;
		CLock _netRecvIoLock;
		CLock _netSendIoLock;
		bool _isGetMsg; //����Ƿ���յ��µ���

		MapRMIObject _rmiObjectMap;  //��session ���Ե��õ�Զ�̽ӿ�

		MapRMIObjectBind _callBackMap;

		int _callBackId;  //�ص�id

	};
	typedef CSmartPointShare<CSession> CSessionPtr;
}
#endif