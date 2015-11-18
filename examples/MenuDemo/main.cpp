#include <shutters/Shutters.hpp>

#include <shutters/MenuBar.hpp>
#include <shutters/SubMenu.hpp>
#include <shutters/CommandItem.hpp>
#include <shutters/CheckBoxMenuItem.hpp>
#include <shutters/RadioButtonMenuItem.hpp>
#include <shutters/MsgBox.hpp>
#include <shutters/FrameWindow.hpp>

#include <shutters/TextBox.hpp>
#include <shutters/Button.hpp>
#include <shutters/GdiplusManager.hpp>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

class MainWindow : public FrameWindow {

	MenuBar menuBar;
		SubMenu fileMenu;
			CommandItem openCmd;
			CommandItem closeCmd;
			SubMenu recentMenu;
				CommandItem hellocppCmd;
			CommandItem exitCmd;
		SubMenu editMenu;
			CommandItem copyCmd;
			CommandItem cutCmd;
			CommandItem pasteCmd;
		SubMenu viewMenu;
			CheckBoxMenuItem browerCmd;
			CheckBoxMenuItem outputCmd;
		SubMenu colorMenu;
			RadioButtonMenuItem redCmd;
			RadioButtonMenuItem greenCmd;
			RadioButtonMenuItem blueCmd;
			//--------------------------
			RadioButtonMenuItem darkCmd;
			RadioButtonMenuItem lightCmd;
		SubMenu helpMenu;
			CommandItem aboutCmd;

	Button m_button_ok;
public:

	void exitCmd_click(void*, EventArgs&)
	{
		close();
	}

	MainWindow()
	{
		m_button_ok.setText(L"OK");
		controls.add(m_button_ok);
		m_button_ok.setBounds(200, 10, 75, 20);

		//setMenu(menuBar);

		fileMenu.setText(L"File");
		menuBar.insert(fileMenu);
		openCmd.setText(L"Open");
		fileMenu.insert(openCmd);
		closeCmd.setText(L"Close");
		fileMenu.insert(closeCmd);

		recentMenu.setText(L"Recent");
		fileMenu.insert(recentMenu);
		hellocppCmd.setText(L"hello.cpp");
		recentMenu.insert(hellocppCmd);
		fileMenu.addSeparator();
		exitCmd.setText(L"Exit");
		exitCmd.click.addListener(this, &MainWindow::exitCmd_click);
		fileMenu.insert(exitCmd);

		editMenu.setText(L"Edit");
		menuBar.insert(editMenu);
		copyCmd.setText(L"Copy");
		editMenu.insert(copyCmd);
		cutCmd.setText(L"Cut");
		editMenu.insert(cutCmd);
		pasteCmd.setText(L"Paste");
		editMenu.insert(pasteCmd);

		viewMenu.setText(L"View");
		menuBar.insert(viewMenu);
		browerCmd.setText(L"Browser");
		viewMenu.insert(browerCmd);
		outputCmd.setText(L"Output");
		viewMenu.insert(outputCmd);

		colorMenu.setText(L"Color");
		menuBar.insert(colorMenu);
		redCmd.setText(L"Red");
		colorMenu.insert(redCmd);
		greenCmd.setText(L"Green");
		colorMenu.insert(greenCmd);
		blueCmd.setText(L"Blue");
		colorMenu.insert(blueCmd);
		colorMenu.addSeparator();
		darkCmd.setText(L"Dark");
		darkCmd.setGroupId(1);
		lightCmd.setText(L"Light");
		lightCmd.setGroupId(1);
		colorMenu.insert(darkCmd);
		colorMenu.insert(lightCmd);

		helpMenu.setText(L"Help");
		menuBar.insert(helpMenu);
		aboutCmd.setText(L"About");
		helpMenu.insert(aboutCmd);

		setMenu(menuBar);
	}
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GdiplusManager gdiplus;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MainWindow mainWindow;
	mainWindow.show();
	mainWindow.update();

	Shutters::SetStartupWindow(mainWindow);

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}
