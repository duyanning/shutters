#pragma once

#include <shutters/button.hpp>
#include "DesignTimeControl.h"

using namespace Shutters;

class DTButton : public Button, public DesignTimeControl {
public:
	DTButton();
	DTButton* clone();
protected:
private:
};
