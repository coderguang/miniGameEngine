#include "engine/net/protocol/csgProtocol.h"
#include "framework/util/endian.h"
#include "../../rpc/rmidef.h"
#include "../../mq/msgBlock.h"
#include "../../rpc/rmiObjectAdapter.h"

int csg::CCsgProtocol::handleRecvData(const void* inData, const int len)
{
	_recvBuffer->append(inData, len);
#ifdef _DEBUG
	std::string str(_recvBuffer->getData(), _recvBuffer->getDataSize());
	LogDebug("receive is " << str);
#endif

	return 0;
}

int csg::CCsgProtocol::handleSendData(const CSessionPtr session, const void* data, const int len)
{
	CAutoLock l(_writeLock);
	_sendBuffer->append(data, len);
	session->getSocket()->async_write_some(boost::asio::null_buffers(), boost::bind(&CCsgProtocol::handleWriteDataEx, this, session, boost::asio::placeholders::error));
	return 0;
}

int csg::CCsgProtocol::handleReadData(const CSessionPtr session)
{
	do
	{
		if (_receiveHead)
		{
			if (_recvBuffer->getDataSize() < _protocolHead.msgSize)
			{
				//data not enough for a packet
				return true;
			}
			else
			{
				//data enough for a packet
				if (!handlePacket(session, _recvBuffer->getData() + SIZE_OF_PROTOCOL_HEAD, _protocolHead.msgSize))
				{
					LogInfo("CProtocol::handlePacket error");
					return false;
				}
				_recvBuffer->popData(_protocolHead.msgSize + SIZE_OF_PROTOCOL_HEAD);
				_receiveHead = false;
			}
		}
		else
		{
			if (_recvBuffer->getDataSize() >= SIZE_OF_PROTOCOL_HEAD)
			{
				memcpy(&_protocolHead, _recvBuffer->getData(), SIZE_OF_PROTOCOL_HEAD);
				_protocolHead.msgSize = endian(_protocolHead.msgSize);
				_receiveHead = true;
			}
			else
			{
				return true;
			}
		}
	} while (true);

	return false;

	return 0;
}

int csg::CCsgProtocol::handleWriteData(const CSessionPtr session)
{

	return 0;
}

int csg::CCsgProtocol::handlePacket(const CSessionPtr session, const void *packageData, const int len)
{
	CAutoSerializeStream is(CSerializeStreamPool::instance()->newObject());
	is->append(packageData, len);

	is->setUseBitMark(false);

	is->prepareToRead();

	ERMIMessageType mqType;
	_csg_read(*is, mqType);

	switch (mqType)
	{
	case csg::ERMIMessageTypeMQ:
	{
		CMsgBlockPtr msg = new CMsgBlock();
		msg->_csg_read(*is);

		if (!msg)
		{
			assert(false);
			return false;
		}
		msg->_msgBase->print();
	}
	break;
	case csg::ERMIMessageTypeCall:
	{
		SRMICall rmiCall;
		rmiCall._csg_read(*is);

		MapRMIObject mapObject;
		if (!CRMIObjectAdapter::instance()->findRmiObject("Test", mapObject))
		{
			return false;
		}
		MapRMIObject::iterator it = mapObject.find(rmiCall.rpcId);
		if (it == mapObject.end())
		{
			return false;
		}
		is->setUseBitMark(true);
		it->second->__onCall(session, rmiCall, *is);
	}
	break;
	case csg::ERMIMessageTypeCallRet:
	{
		SRMIReturn rmiReturn;
		rmiReturn._csg_read(*is);

		is->setUseBitMark(true);

		LogInfo("CProtocol::handlePacket" << ",messageId=" << rmiReturn.messageId);

		if (rmiReturn.messageId <= 0)
			return true;

		CRMIObjectBindPtr backObject;
		if (!session->getCallBackObject(rmiReturn.messageId, backObject))
		{
			return false;
		}
		if (backObject->_callBack)
		{
			backObject->_callBack->__response(*is);
		}
	}
	break;
	default:
	{
		LogErr("unkonw type=" << mqType);
		assert(false);
		return false;
	}
	}

	return true;
}

int csg::CCsgProtocol::handleWriteDataEx(const CSessionPtr session, boost::system::error_code err)
{
	if (err)
	{
		LogErr("CCsgProtocol::handleWriteDataEx handleWritet,ex=" << err.message());
		return -1;
	}
	else
	{
		LogDebug("CCsgProtocol::handleWriteDataEx handleWritet.....");
		boost::system::error_code write_err;
		int wlen = session->getSocket()->write_some(boost::asio::buffer(_sendBuffer->getData(),0), write_err);
		if (write_err)
		{
			LogErr("CCsgProtocol::handleWriteDataEx write some2,ex=" << write_err.message());
			return -1;
		}
		else
		{
			LogDebug("CCsgProtocol::handleWriteDataEx handleWritet complete,size=" << wlen);
		}
		_sendBuffer->popData(wlen);
	}
	return 0;
}

