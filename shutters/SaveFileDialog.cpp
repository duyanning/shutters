#include "wincpp.hpp"
#include "SaveFileDialog.hpp"

using namespace Shutters;

SaveFileDialog::SaveFileDialog()
{
}

BOOL
SaveFileDialog::getOpenSaveFileName(LPOPENFILENAME lpofn)
{
	return ::GetSaveFileName(lpofn);
}
