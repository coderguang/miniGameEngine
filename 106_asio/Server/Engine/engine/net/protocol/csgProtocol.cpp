#include "engine/net/protocol/csgProtocol.h"

int csg::CCsgProtocol::handleRecvData(const void* inData ,const int len)
{
	_recvBuffer->append(inData ,len);
	return 0;
}

int csg::CCsgProtocol::handleSendData(const CSessionPtr& session ,const void* data ,const int len)
{
	_sendBuffer->append(data ,len);
	return 0;
}

