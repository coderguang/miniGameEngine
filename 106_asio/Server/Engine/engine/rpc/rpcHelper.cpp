#include "engine/rpc/rpcHelper.h"


using namespace csg;

void csg::CRpcHelper::prepareToCall(const CSessionPtr& session ,CAutoSerializeStream& __os ,SRMICall& call ,const CRMIProxyCallBackObjectPtr& backObject ,CRMIObjectBindPtr& objectBind)
{
	//д��type
	_csg_write(*__os ,ERMIMessageTypeCall);

	if ( backObject )
	{
		//�лص�����
		objectBind = CObjectPool<CRMIObjectBind>::instance()->newObject();
		objectBind->bindProxyCallBackObject(backObject);

		call.messageId = session->getCallBackId();

		session->addCallBackObject(call.messageId ,objectBind);

	}

	//д��call
	call._csg_write(*__os);

}

void csg::CRpcHelper::toCall(const CSessionPtr& session ,CAutoSerializeStream& __os ,CRMIObjectBindPtr& objectBind)
{
	__os->prepareToAppend();
	//����
	CAutoSerializeStream tmpOs(CSerializeStreamPool::instance()->newObject());
	tmpOs->writeSize(__os->getFlagDataSize());
	tmpOs->append(__os->getFlagData() ,__os->getFlagDataSize());
	tmpOs->append(__os->getData() ,__os->getDataSize());


	//��Э��ͷ
	SProtocolHead head;
	head.msgSize = tmpOs->getDataSize();
	CAutoSerializeStream addHeadOs(CSerializeStreamPool::instance()->newObject());
	addHeadOs->append(&head ,SIZE_OF_PROTOCOL_HEAD);
	addHeadOs->append(tmpOs->getData() ,tmpOs->getDataSize());

	//CSG_LOG_DEBUG("CRpcHelper::toCall,size=" << addHeadOs->getDataSize());

	//int sendSize=CSocketHelper::sendMsg(session->getSocketfd() ,addHeadOs->getData() ,addHeadOs->getDataSize());

	//CSG_LOG_DEBUG("CRpcHelper::toCall,sendSize=" <<sendSize);

}

void csg::CRpcHelper::prepareToReturn(const CSessionPtr& session ,CAutoSerializeStream& __os ,SRMIReturn& rmiReturn)
{

	//д��type
	_csg_write(*__os ,ERMIMessageTypeCallRet);
	//д��return info
	rmiReturn._csg_write(*__os);

	//CSG_LOG_DEBUG("CRpcHelper::prepareToReturn,size=" << __os->getDataSize());
}

void csg::CRpcHelper::toReturn(const CSessionPtr& session ,CAutoSerializeStream& __os)
{
	__os->prepareToAppend();

	//����
	CAutoSerializeStream tmpOs(CSerializeStreamPool::instance()->newObject());
	tmpOs->writeSize(__os->getFlagDataSize());
	tmpOs->append(__os->getFlagData() ,__os->getFlagDataSize());
	tmpOs->append(__os->getData() ,__os->getDataSize());

	//��Э��ͷ
	SProtocolHead head;
	head.msgSize = tmpOs->getDataSize();
	CAutoSerializeStream addHeadOs(CSerializeStreamPool::instance()->newObject());
	addHeadOs->append(&head ,SIZE_OF_PROTOCOL_HEAD);
	addHeadOs->append(tmpOs->getData() ,tmpOs->getDataSize());

	//CSG_LOG_DEBUG("CRpcHelper::toReturn,size=" << addHeadOs->getDataSize());

	//int sendSize=CSocketHelper::sendMsg(session->getSocketfd() ,addHeadOs->getData() ,addHeadOs->getDataSize());

	//CSG_LOG_DEBUG("CRpcHelper::toReturn,sendSize=" <<sendSize);
}