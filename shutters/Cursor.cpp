#include "wincpp.hpp"
#include "Cursor.hpp"

using namespace Shutters;

Cursor::Cursor(HCURSOR handle)
	:
m_handle(handle)
{
}

void
Cursor::setCurrent(Cursor* cursor)
{
	::SetCursor(cursor->handle());
}

HCURSOR
Cursor::handle()
{
	return m_handle;
}