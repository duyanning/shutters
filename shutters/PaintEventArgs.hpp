#ifndef SHUTTERS_PAINTEVENTARGS_HPP
#define SHUTTERS_PAINTEVENTARGS_HPP

#include "wincpp.hpp"

namespace Shutters {

	class PaintEventArgs {
	public:
		PaintEventArgs(HDC hdc)
		:
			graphics(hdc)
		{
		}
		//PaintEventArgs(const PaintEventArgs& a)
		//{
		//}
		Gdiplus::Graphics graphics;
	};

}

#endif
