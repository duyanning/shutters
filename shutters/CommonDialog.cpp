#include "wincpp.hpp"
#include "CommonDialog.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

DialogResult
CommonDialog::ShowDialog(Window* owner)
{
	if (RunDialog(owner))
		return OK;
	return Cancel;
}
