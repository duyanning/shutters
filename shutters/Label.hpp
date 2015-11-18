#pragma once

//#include "ChildWindow.hpp"
//#include "ButtonBase.hpp"
#include "WinControl.hpp"

class Gdiplus::Image;

namespace Shutters {
	using namespace std;

	class PaintEventArgs;

	class Label : public WinControl {
		typedef WinControl Base;
	public:
		Label(const wstring& text = L"");
		~Label();

		const Gdiplus::Image* image();
		void setImage(Gdiplus::Image* image);
	protected:
		void onPaint(PaintEventArgs& e);
	private:
		Gdiplus::Image* m_image;
	};

}
