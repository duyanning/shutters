#include "DTForm.h"
#include "DesignTimeControl.h"
#include <crtdbg.h>
#include <shutters/SaveFileDialog.hpp>
#include <shutters/tostring.hpp>
#include <shutters/Rectangle.hpp>
#include <fstream>
#include <sstream>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

DTForm::DTForm()
:
	m_currentControl(0),
	name(L"Form1")
{
}

DTForm::~DTForm()
{
	for (vector<Window*>::iterator i = m_controls.begin(); i != m_controls.end(); ++i)
		delete *i;
}

void
DTForm::addControl(Window* control)
{
	controls.add(control);
	m_controls.push_back(control);
	
	control->mouseDown.addListener(this, &DTForm::someControl_mouseDown);
	control->mouseUp.addListener(this, &DTForm::someControl_mouseUp);
	control->mouseMove.addListener(this, &DTForm::someControl_mouseMove);
}

void drawRect(HDC hdc, const Shutters::Rectangle& rect)
{
	Gdiplus::Rect outline;
	outline.X = rect.x();
	outline.Y = rect.y();
	outline.Width = rect.width();
	outline.Height = rect.height();

	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
	graphics.DrawRectangle(&pen, outline);
}

void drawOutline(HDC hdc, Window* control)
{
	Shutters::Rectangle bounds = control->bounds();

	Shutters::Rectangle rect;
	rect.setX(bounds.x() - 3);
	rect.setY(bounds.y() - 3);
	rect.setWidth(bounds.width() + 6);
	rect.setHeight(bounds.height() + 6);

	drawRect(hdc, rect);
}

void
DTForm::someControl_mouseDown(Window* sender, MouseEventArgs& e)
{
	DesignTimeControl* control = dynamic_cast<DesignTimeControl*>(sender);
	control->m_previousPos = Point(e.X, e.Y);
	control->m_mouseDown = true;
	sender->setCapture(true);

	if (m_currentControl != sender) {
		Window* oldCurrent = m_currentControl;
		m_currentControl = sender;

		HDC hdc = ::GetDC(handle());
		drawOutline(hdc, m_currentControl);
		::ReleaseDC(handle(), hdc);

	}
}

void
DTForm::someControl_mouseUp(Window* sender, MouseEventArgs& e)
{
	DesignTimeControl* control = dynamic_cast<DesignTimeControl*>(sender);
	control->m_mouseDown = false;
	sender->setCapture(false);

	HDC hdc = ::GetDC(handle());
	drawOutline(hdc, sender);
	::ReleaseDC(handle(), hdc);
}

void
DTForm::someControl_mouseMove(Window* sender, MouseEventArgs& e)
{
	Point currentPos = Point(e.X, e.Y);
	DesignTimeControl* control = dynamic_cast<DesignTimeControl*>(sender);
	if (control->m_mouseDown) {
		int deltaX = currentPos.x - control->m_previousPos.x;
		int deltaY = currentPos.y - control->m_previousPos.y;

		Point oldLoc = sender->location();
		Point newLoc(oldLoc.x + deltaX, oldLoc.y + deltaY);
		sender->setLocation(newLoc);

		this->invalidate();
		this->update();

	}
}

void
DTForm::save()
{
	SaveFileDialog dlg;
    dlg.setInitialDirectory(L"c:\\");
	dlg.setFileName(name);
//    dlg.setFilter(L"h Saw files (*.h.saw)|*.h.saw|cpp Saw files (*.cpp.saw)|*.saw.h|All files (*.*)|*.*");
    dlg.setFilter(L"All files (*.*)|*.*");
    dlg.setFilterIndex(1);

    if(dlg.ShowDialog(this) == OK) {
		string baseSawFileName = tostring(dlg.getFileName());
		createSawFiles(baseSawFileName);
    }
}

void
DTForm::createSawFiles(string baseSawFileName)
{
	string hSawFileName = baseSawFileName + ".h.saw";
	string cppSawFileName = baseSawFileName + ".cpp.saw";

	locale::global(locale(""));	// HACK, for vc8 bug, bug?
	ofstream hSawOfs(hSawFileName.c_str());
	ofstream cppSawOfs(cppSawFileName.c_str());
	locale::global(locale::classic());	// HACK

	hSawOfs << "// This file is created by Saw.\n";
	cppSawOfs << "// This file is created by Saw.\n";

	cppSawOfs << "void\n";
	cppSawOfs << "Form1::InitializeComponent()\n";
	cppSawOfs << "{\n";

	for (vector<Window*>::iterator i = m_controls.begin(); i != m_controls.end(); ++i) {
		DesignTimeControl* control = dynamic_cast<DesignTimeControl*>(*i);

		string typeStr = tostring(control->type);
		string nameStr = tostring(control->name);
		Point loc = (*i)->location();
		Size sz = (*i)->size();
		string textStr = '\"' + tostring((*i)->text()) + '\"';

		ostringstream oss;
		oss << '('
			<< loc.x << ", " << loc.y
			<< ')';
		string locStr = oss.str();

		oss.str("");
		oss << '('
			<< sz.width << ", " << sz.height
			<< ')';
		string szStr = oss.str();

		hSawOfs << typeStr << ' ' << nameStr << ";\n";

		cppSawOfs << '\t' << nameStr
			<< ".setText("
			<< textStr << ");"
			<< '\n';

		cppSawOfs << '\t' << nameStr
			<< ".setLocation"
			<< locStr << ';'
			<< '\n';

		cppSawOfs << '\t' << nameStr
			<< ".setSize"
			<< szStr << ';'
			<< '\n';

		cppSawOfs << '\t' << "this->controls.add("
			<< nameStr
			<< ");"
			<< '\n';

		cppSawOfs << '\n';
	}

	cppSawOfs << "}\n";

	hSawOfs << "void InitializeComponent();\n";

}

void
DTForm::this_mouseDown(Window* sender, MouseEventArgs& e)
{
	if (m_currentControl) {
		invalidate();
		update();
		m_currentControl = 0;
	}
}

void
DTForm::setControlName(const wstring& name)
{
	if (m_currentControl) {
		DesignTimeControl* control = dynamic_cast<DesignTimeControl*>(m_currentControl);
		control->name = name;
	}
	else {
		this->name = name;
	}
}
