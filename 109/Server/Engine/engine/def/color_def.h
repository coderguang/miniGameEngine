#ifndef _ENGINE_DEF_COLOR_DEF_H_
#define _ENGINE_DEF_COLOR_DEF_H_

#include "engine/def/environment_def.h"

namespace csg {

	enum ECsgColor {
#ifdef CSG_WIN
		Color_White = 7,
		Color_Green = 10,
		Color_Red = 12,
		Color_Pink = 13,
		Color_Yellow = 14,
#else
		Color_Red = 31,
		Color_Green = 32,
		Color_Yellow = 33,
		Color_Pink = 35,
		Color_White = 37

#endif


	};

	class CColorHelper{
	public:
		static void setColor(int color)
		{
#ifdef CSG_WIN
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole ,color);
#else
			printf("\033[%d;40;1m" ,color);
#endif
		}
	};

}
#endif