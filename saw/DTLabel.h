#pragma once

#include <shutters/label.hpp>
#include "DesignTimeControl.h"

using namespace Shutters;

class DTLabel : public Label, public DesignTimeControl {
public:
	DTLabel();
	DTLabel* clone();
protected:
private:
};
