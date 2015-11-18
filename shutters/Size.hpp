#pragma once

namespace Shutters {

class Size {
public:
	Size(int width = 0, int height = 0);
	int width;
	int height;
};

inline
Size::Size(int w, int h)
:
	width(w),
	height(h)
{
}

}
