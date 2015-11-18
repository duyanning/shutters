#pragma once

#include <string>
#include <shutters/Point.hpp>

class DesignTimeControl {
public:
	DesignTimeControl();
	Shutters::Point m_previousPos;
	bool m_mouseDown;
	std::wstring type;
	std::wstring name;
	virtual DesignTimeControl* clone() = 0;
};
