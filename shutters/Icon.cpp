#include "wincpp.hpp"
#include "Icon.hpp"

using namespace Shutters;

Icon::Icon(HICON handle)
	:
m_handle(handle)
{
}


Icon*
Icon::fromHandle(HICON handle)
{
	return new Icon(handle);
}

HICON
Icon::handle()
{
	return m_handle;
}