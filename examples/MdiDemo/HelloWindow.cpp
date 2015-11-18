#include "HelloWindow.h"
#include "MainWindow.h"

bool HelloWindow::menuBuilt;
MenuBar HelloWindow::helloMenuBar;
SubMenu HelloWindow::helloMenu;
CommandItem HelloWindow::duCmd;
CommandItem HelloWindow::yanCmd;
CommandItem HelloWindow::ningCmd;

void
HelloWindow::menu_click(void* sender, EventArgs& e)
{
	CommandItem* cmd = static_cast<CommandItem*>(sender);
	m_button.setText(cmd->text());
}

void
HelloWindow::onActivate(bool b)
{
	if (b) {
		getMdiFrame()->setMdiMenu(helloMenuBar, &helloMenu);
	}
	else {
		getMdiFrame()->setMdiMenu(MainWindow::mainMenuBar, 0);
	}
}

HelloWindow::HelloWindow(MdiFrameWindow* mdiFrame)
	: MdiChildWindow(mdiFrame)
{
	setText(L"Hello");
	m_button.setText(L"Hello");
	controls.add(m_button);
	m_button.setBounds(10, 10, 75, 20);
	buildMenu();
}

void
HelloWindow::buildMenu()
{
	if (!menuBuilt) {
		// 'Hello' menu
		helloMenu.setText(L"Hello");

		duCmd.setText(L"du");
		helloMenu.insert(duCmd);

		yanCmd.setText(L"yan");
		helloMenu.insert(yanCmd);

		ningCmd.setText(L"ning");
		helloMenu.insert(ningCmd);

		helloMenuBar.insert(MainWindow::fileMenu);
		helloMenuBar.insert(helloMenu);

		menuBuilt = true;
	}

	cnDu = duCmd.click.addListener(this, &HelloWindow::menu_click);
	cnYan = yanCmd.click.addListener(this, &HelloWindow::menu_click);
	cnNing = ningCmd.click.addListener(this, &HelloWindow::menu_click);
}
