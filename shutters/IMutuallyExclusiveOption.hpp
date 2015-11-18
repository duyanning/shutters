#pragma once

#include "IStateOption.hpp"

namespace Shutters {

class IMutuallyExclusiveOption : public IStateOption {
public:
	IMutuallyExclusiveOption();
	void setGroupId(int groupId);
	int getGroupId();
private:
	int m_groupId;

};

}