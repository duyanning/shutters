#include "HelloWindow.h"
#include "WorldWindow.h"
#include "MainWindow.h"

bool MainWindow::menuBuilt;
MenuBar MainWindow::mainMenuBar;
SubMenu MainWindow::fileMenu;
CommandItem MainWindow::newHelloCmd;
CommandItem MainWindow::newWorldCmd;
CommandItem MainWindow::closeCurrentCmd;

MainWindow::MainWindow()
{
	setText(L"MDI Demo");
	buildMenu();
	setMdiMenu(mainMenuBar, 0);
}

void
MainWindow::buildMenu()
{
	if (!menuBuilt) {
		// 'File' menu
		fileMenu.setText(L"File");

		newHelloCmd.setText(L"New Hello");
		fileMenu.insert(newHelloCmd);

		newWorldCmd.setText(L"New World");
		fileMenu.insert(newWorldCmd);

		closeCurrentCmd.setText(L"Close Current");
		fileMenu.insert(closeCurrentCmd);

		// menu bar (3)
		mainMenuBar.insert(fileMenu);

		menuBuilt = true;
	}
	newHelloCmd.click.addListener(this, &MainWindow::newHelloCmd_click);
	newWorldCmd.click.addListener(this, &MainWindow::newWorldCmd_click);
	closeCurrentCmd.click.addListener(this, &MainWindow::closeCurrentCmd_click);
}

void
MainWindow::newHelloCmd_click(void*, EventArgs&)
{
	newChild<HelloWindow>();
}

void
MainWindow::newWorldCmd_click(void*, EventArgs&)
{
	newChild<WorldWindow>();
}

void
MainWindow::closeCurrentCmd_click(void*, EventArgs&)
{
	MdiChildWindow* activeChild = getActiveChild();
	if (activeChild)
		deleteChild(activeChild);
}
