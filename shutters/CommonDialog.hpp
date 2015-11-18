#ifndef SHUTTERS_COMMONDIALOG_HPP
#define SHUTTERS_COMMONDIALOG_HPP

#include "DialogResult.hpp"

namespace Shutters {

class Window;

class CommonDialog {
public:
	DialogResult ShowDialog(Window* owner);
protected:
	virtual bool RunDialog(Window* owner) = 0;
};

}

#endif
