#include "wincpp.hpp"
#include "Label.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"
#include "PaintEventArgs.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

Label::Label(const wstring& text)
:
	m_image(0)
{
	using namespace ShuttersImpl;

	HWND handle = ::CreateWindowEx(
			0,
			L"static",
			text.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT | SS_NOTIFY,
			0,
			0,
			0,
			0,
			getNurserWindow(),
			NULL,
			0,
			NULL
		);
	setOldWndProc(replaceWndProc(handle, S_WndProc));
	setHandle(handle);
	addToMap(handle);
}

Label::~Label()
{
}

const Gdiplus::Image*
Label::image()
{
	return 0;
}

void
Label::setImage(Gdiplus::Image* image)
{
//	ShuttersImpl::modifyStyle(handle(), 0, SS_);
	if (m_image == image)  return;

	m_image = image;
	invalidate();
}

void
Label::onPaint(PaintEventArgs& e)
{
	Base::onPaint(e);
	if (m_image) {
		e.graphics.DrawImage(m_image, 0, 0);
	}
}
