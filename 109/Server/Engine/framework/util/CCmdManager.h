
#ifndef _FRAMEWORK_UTIL_CMD_MANAGER_H_
#define _FRAMEWORK_UTIL_CMD_MANAGER_H_

#include "../DesignPattern/Singleton.h"
#include "../json/value.h"
#include "../SmartPoint/refObject.h"
#include "../SmartPoint/smartPoint.h"

namespace csg
{

	typedef void (*dealFun)(Json::Value& js);

	class CCmdStruct :public virtual CRefObject
	{
	public:
		std::string cmd;
		std::string desc;
		dealFun func;
	};

	typedef CSmartPointShare<CCmdStruct> CCmdStructPtr;
	typedef std::map<std::string ,CCmdStructPtr> MapCmdStruct;

	class CCmdManager :public virtual Singleton<CCmdManager>
	{
	public:
		void registCmd(std::string cmdKey ,std::string Desc,dealFun func);

		bool dealCmd(std::string& cmdStr);

		void printCmd();

	protected:
		bool isCmdRegist(std::string& cmdKey);

	private:


		MapCmdStruct _map;
	};
}
#endif