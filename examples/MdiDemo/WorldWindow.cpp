#include "WorldWindow.h"
#include "MainWindow.h"

bool WorldWindow::menuBuilt;
MenuBar WorldWindow::worldMenuBar;
SubMenu WorldWindow::worldMenu;
CommandItem WorldWindow::chinaCmd;
CommandItem WorldWindow::usaCmd;

void
WorldWindow::menu_click(void* sender, EventArgs& e)
{
	CommandItem* cmd = static_cast<CommandItem*>(sender);
	m_button.setText(cmd->text());
}

void
WorldWindow::onActivate(bool b)
{
	if (b) {
		getMdiFrame()->setMdiMenu(worldMenuBar, &worldMenu);
	}
	else {
		getMdiFrame()->setMdiMenu(MainWindow::mainMenuBar, 0);
	}
}

WorldWindow::WorldWindow(MdiFrameWindow* mdiFrame)
	: MdiChildWindow(mdiFrame)
{
	setText(L"World");
	m_button.setText(L"World");
	controls.add(m_button);
	m_button.setBounds(10, 10, 75, 20);
	buildMenu();
}

void
WorldWindow::buildMenu()
{
	if (!menuBuilt) {

		// 'World' menu
		worldMenu.setText(L"World");

		chinaCmd.setText(L"china");
		worldMenu.insert(chinaCmd);

		usaCmd.setText(L"usa");
		worldMenu.insert(usaCmd);

		worldMenuBar.insert(MainWindow::fileMenu);
		worldMenuBar.insert(worldMenu);

		menuBuilt = true;
	}
	cnChina = chinaCmd.click.addListener(this, &WorldWindow::menu_click);
	cnUsa = usaCmd.click.addListener(this, &WorldWindow::menu_click);
}
