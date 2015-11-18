#include "wincpp.hpp"
#include "OpenFileDialog.hpp"

using namespace Shutters;

OpenFileDialog::OpenFileDialog()
{
}

BOOL
OpenFileDialog::getOpenSaveFileName(LPOPENFILENAME lpofn)
{
	return ::GetOpenFileName(lpofn);
}
