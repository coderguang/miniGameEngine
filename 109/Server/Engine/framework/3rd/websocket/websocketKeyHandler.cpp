#include "websocketKeyHandler.h"
#include <string>
#include "framework/log/Log.h"
#include "sha1.h"
#include "base64.h"

#ifdef CSG_LINUX
	#include <arpa/inet.h>
#endif

static const std::string WEB_SOCKET_MAGIC_KEY = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

csg::CWebSocketKeyHandler::CWebSocketKeyHandler(const CBytesBuffer& data)
{
	_head_buffer.clear();
	_head_buffer.append(data.getData(), data.getDataSize());
}

bool csg::CWebSocketKeyHandler::getClientReqKey(const CBytesBuffer& data)
{
	return true;
}

int csg::CWebSocketKeyHandler::fetchHttpInfo(const CBytesBuffer& data)
{
	std::istringstream http_info(data.getData());
	std::string request;
	std::getline(http_info, request);
	if (request[request.size() - 1] == '\r')
		request.erase(request.end() - 1);
	else
		return -1;

	std::string header;
	std::string::size_type end;

	while (std::getline(http_info, header) && header != "\r") {
		if (header[header.size() - 1] != '\r')
			continue;
		else
			header.erase(header.end() - 1);
		end = header.find(":", 0);
		if (end != std::string::npos) {
			std::string key = header.substr(0, end);
			std::string value = header.substr(end + 2);
			_head_key_map[key] = value;
		}
	}
	return 0;
}

std::string csg::CWebSocketKeyHandler::getRespondStr()
{
	std::string server_key = _head_key_map["Sec-WebSocket-Key"];

	LogInfo("client key:" << server_key);

	server_key += WEB_SOCKET_MAGIC_KEY;

	SHA1 sha;
	unsigned int message_digest[5];
	sha.Reset();
	sha << server_key.c_str();

	sha.Result(message_digest);
	for (int i = 0; i < 5; i++) {
		message_digest[i] = htonl(message_digest[i]);
	}
	server_key = base64_encode(reinterpret_cast<const unsigned char*>(message_digest), 20);
	server_key += "\r\n";
	 
	std::string request_str="";
	request_str+="HTTP/1.1 101 Switching Protocols\r\n";
	request_str += "Connection: upgrade\r\n";
	request_str += "Sec-WebSocket-Accept: ";
	request_str += server_key.c_str();
	request_str += "Upgrade: websocket\r\n\r\n";

	LogInfo("response server_key:" <<server_key);
	return request_str;
}

int csg::CWebSocketKeyHandler::fetchHttpInfo()
{
	return fetchHttpInfo(_head_buffer);
}

void csg::CWebSocketKeyHandler::printMsg()
{
	LogDebug("print http_info ==========================");
	for (std::map<std::string, std::string>::iterator it = _head_key_map.begin(); it != _head_key_map.end(); ++it) {
		LogDebug("key:" << it->first << "  -----  value:" << it->second);
	}
	LogDebug("print http_info end ==========================");
}
