#pragma once

#include <shutters/Shutters.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/TListBox.hpp>
#include <shutters/Button.hpp>
#include <shutters/Label.hpp>
#include <shutters/TextBox.hpp>
#include <shutters/MenuBar.hpp>
#include <shutters/SubMenu.hpp>
#include <shutters/CommandItem.hpp>
#include <vector>

#include "DesignTimeControl.h"
#include "DTButton.h"
#include "DTLabel.h"

using namespace Shutters;
using namespace std;

class DTForm;

class MainWindow : public FrameWindow {
public:
	MainWindow();
	~MainWindow();

private:
	MenuBar menuBar;
		SubMenu fileMenu;
			CommandItem newCmd;
			CommandItem openCmd;
			CommandItem saveCmd;
			CommandItem closeCmd;
			CommandItem exitCmd;
		SubMenu helpMenu;
			CommandItem aboutCmd;

	void buildMenu();
	void newCmd_click(void*, EventArgs&);
	void openCmd_click(void*, EventArgs&);
	void saveCmd_click(void*, EventArgs&);
	void closeCmd_click(void*, EventArgs&);
	void exitCmd_click(void*, EventArgs&);
	void aboutCmd_click(void*, EventArgs&);

	DTButton m_Button;
	DTLabel m_Label;

	Label m_lblToolbox;
	TListBox<DesignTimeControl*> m_lstClasses;

	Button m_btnAddToFrom;
	void m_btnAddToFrom_click(void*, EventArgs&);

	TextBox m_controlName;
	void m_controlName_textChanged(void*, EventArgs&);

	void MainWindow_closing(Window* sender, CancelEventArgs& e);

	DTForm* m_currentDTForm;
	vector<DTForm*> m_dtFroms;
};
