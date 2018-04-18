#ifndef _FRAMEWORK_TOOL_SIGNAL_TOOL_H_
#define _FRAMEWORK_TOOL_SIGNAL_TOOL_H_


namespace csg {

	void signalHandleExit(int signalNum);

	void signalHandleKill(int signalNum);



	void registSignalHandle();

}

#endif