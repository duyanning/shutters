#include <shutters/MsgBox.hpp>
#include <shutters/OpenFileDialog.hpp>
#include "MainWindow.h"
#include "DTButton.h"
#include "DTForm.h"
#include "AboutDialog.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

MainWindow::MainWindow()
:
	m_currentDTForm(0)
{
	setText(L"Saw");

	buildMenu();

	m_lblToolbox.setText(L"Toolbox:");
	controls.add(m_lblToolbox);
	m_lblToolbox.setBounds(20, 20, 150, 25);

	controls.add(m_lstClasses);
	m_lstClasses.setBounds(20, 50, 150, 200);

	m_Button.hide();
	m_Button.setBounds(10, 10, 75, 20);
	m_lstClasses.add(L"Button", &m_Button);
	m_Label.hide();
	m_Label.setBounds(10, 10, 75, 20);
	m_lstClasses.add(L"Label", &m_Label);

	m_btnAddToFrom.setText(L"Add To Form");
	controls.add(m_btnAddToFrom);
	m_btnAddToFrom.setBounds(20, 250, 150, 20);
	m_btnAddToFrom.click.addListener(this, &MainWindow::m_btnAddToFrom_click);

	controls.add(m_controlName);
	m_controlName.setBounds(200, 20, 150, 20);
	m_controlName.textChanged.addListener(this, &MainWindow::m_controlName_textChanged);

	closing.addListener(this, &MainWindow::MainWindow_closing);
}

void
MainWindow::buildMenu()
{
	fileMenu.setText(L"&File");
	menuBar.insert(fileMenu);

		newCmd.setText(L"&New");
		newCmd.click.addListener(this, &MainWindow::newCmd_click);
		fileMenu.insert(newCmd);

		openCmd.setText(L"&Open");
		openCmd.click.addListener(this, &MainWindow::openCmd_click);
		fileMenu.insert(openCmd);

		saveCmd.setText(L"&Save");
		saveCmd.click.addListener(this, &MainWindow::saveCmd_click);
		fileMenu.insert(saveCmd);

		closeCmd.setText(L"&Close");
		closeCmd.click.addListener(this, &MainWindow::closeCmd_click);
		fileMenu.insert(closeCmd);

		fileMenu.addSeparator();

		exitCmd.setText(L"E&xit");
		exitCmd.click.addListener(this, &MainWindow::exitCmd_click);
		fileMenu.insert(exitCmd);

	helpMenu.setText(L"&Help");
	menuBar.insert(helpMenu);

		aboutCmd.setText(L"&About Saw");
		aboutCmd.click.addListener(this, &MainWindow::aboutCmd_click);
		helpMenu.insert(aboutCmd);


	setMenu(menuBar);

}

MainWindow::~MainWindow()
{
	for (vector<DTForm*>::iterator i = m_dtFroms.begin(); i != m_dtFroms.end(); ++i)
		delete *i;
}

void
MainWindow::MainWindow_closing(Window* sender, CancelEventArgs& e)
{
	if (MsgBox(this, L"Are you sure?", L"WARNING", MB_YESNO) ==  IDNO)
		e.cancel = true;
}

void
MainWindow::m_btnAddToFrom_click(void*, EventArgs&)
{
	DesignTimeControl* control = m_lstClasses.selectedValue();

	if (control)
		m_currentDTForm->addControl(dynamic_cast<Window*>(control->clone()));
}

void
MainWindow::m_controlName_textChanged(void*, EventArgs&)
{
	m_currentDTForm->setControlName(m_controlName.text());
}

void
MainWindow::newCmd_click(void*, EventArgs&)
{
	m_currentDTForm = new DTForm;
	m_currentDTForm->show();
	m_currentDTForm->update();

	m_dtFroms.push_back(m_currentDTForm);
}

void
MainWindow::openCmd_click(void*, EventArgs&)
{
	OpenFileDialog dlg;
    dlg.setInitialDirectory(L"c:\\");
    dlg.setFilter(L"cpp files (*.cpp)|*.cpp|h files (*.h)|*.h|All files (*.*)|*.*");
    dlg.setFilterIndex(2);

    if(dlg.ShowDialog(this) == OK) {
    }
}

void
MainWindow::saveCmd_click(void*, EventArgs&)
{
	m_currentDTForm->save();
}

void
MainWindow::closeCmd_click(void*, EventArgs&)
{
}

void
MainWindow::exitCmd_click(void*, EventArgs&)
{
	close();
}

void
MainWindow::aboutCmd_click(void*, EventArgs&)
{
	AboutDialog dlg;
	if (dlg.showDialog(this) == OK) {
	}
}
