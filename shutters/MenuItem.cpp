#include "wincpp.hpp"
#include "MenuItem.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

MenuItem::~MenuItem()
{
	disposeSelf();
}

const wstring&
MenuItem::text()
{
	return m_text;
}

void
MenuItem::dispose()
{
	disposeSelf();

	// Base::dispose();  // MenuItem has no Base
}

void
MenuItem::disposeSelf()
{
}
