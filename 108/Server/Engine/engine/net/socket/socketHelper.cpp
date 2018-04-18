#include "engine/net/socket/socketHelper.h"
#include "../session/sessionMgr.h"

void csg::CSocketHelper::startRead(CSessionPtr session)
{
	session->getSocket()->non_blocking(true);
	session->getSocket()->async_read_some(boost::asio::null_buffers(),
		boost::bind(&CSocketHelper::handleRead, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void csg::CSocketHelper::handleRead(CSessionPtr session, boost::system::error_code error, size_t bytes_transferred)
{
	if (error)
	{
		LogErr(__FUNCTION__<<",msg=" << error.message());
		disconnect(session, ESessionDisconnectReadErrorAsync);
		return;
	}
	//暂时先不考虑效率
	char tt[SERIALIZE_MAX_RESIZE];
	memset(&tt, '\0', SERIALIZE_MAX_RESIZE);
	boost::system::error_code read_err;
	int len = session->getSocket()->read_some(boost::asio::buffer(tt), read_err);
	if (read_err)
	{
		LogErr(__FUNCTION__<<" read error,msg=" << read_err.message());
		disconnect(session, ESessionDisconnectReadErrorSync);
		return;
	}
	else
	{
		if (-1 == session->handleRecvData(tt, len)) {
			LogDebug(__FUNCTION__ << ",read error len =" << len);
			disconnect(session, ESessionDisconnectOutOfRecvBuff);
			return;
		}
		LogDebug(__FUNCTION__<< ",read size=" << len);
	}
	startRead(session);
}

void csg::CSocketHelper::disconnect(CSessionPtr session, ESessionDisconnectReason reason)
{
	LogDebug(__FUNCTION__ << " ip:" << session->getAddress()<<",port:"<<session->getPort()<< ",reason:" << (int)reason);
	session->getSocket()->close();
	session->setStatus(ESessionStatusDisConnected);
	CSessionMgr::instance()->delSession(session);
}

