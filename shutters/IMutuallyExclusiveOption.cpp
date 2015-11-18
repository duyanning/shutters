#include "wincpp.hpp"
#include "IMutuallyExclusiveOption.hpp"

using namespace Shutters;

IMutuallyExclusiveOption::IMutuallyExclusiveOption()
:
m_groupId(0)
{
}

void
IMutuallyExclusiveOption::setGroupId(int groupId)
{
	m_groupId = groupId;
}

int
IMutuallyExclusiveOption::getGroupId()
{
	return m_groupId;
}
