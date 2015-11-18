#include "AboutDialog.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

AboutDialog::AboutDialog()
{
	setBounds(30, 30, 300, 100);
	btnOk.setText(L"Ok");
	controls.add(btnOk);
	btnOk.setBounds(200, 10, 75, 20);
	btnOk.click.addListener(this, &AboutDialog::btnOk_click);
}

void
AboutDialog::btnOk_click(void*, EventArgs&)
{
	dialogResult = OK;
}
