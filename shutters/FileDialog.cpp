#include "wincpp.hpp"
#include "FileDialog.hpp"
#include "Window.hpp"

using namespace Shutters;

FileDialog::FileDialog()
:
	m_fileName(),
	m_defaultExt(),
	m_filter(),
	m_initialDirectory(),
	m_filterIndex(1),
	m_addExtension(false)
{
}

const wstring&
FileDialog::getFileName()
{
	return m_fileName;
}

void
FileDialog::setFileName(const wstring& name)
{
	m_fileName = name;
}

const wstring&
FileDialog::getFilter()
{
	return m_filter;
}

void
FileDialog::setFilter(const wstring& filter)
{
	m_filter = filter;
}

const wstring&
FileDialog::getInitialDirectory()
{
	return m_initialDirectory;
}

void
FileDialog::setInitialDirectory(const wstring& dir)
{
	m_initialDirectory = dir;
}

int
FileDialog::getFilterIndex()
{
	return m_filterIndex;
}

void
FileDialog::setFilterIndex(int filterIndex)
{
	m_filterIndex = filterIndex;
}

const wstring&
FileDialog::getDefaultExt()
{
	return m_defaultExt;
}

void
FileDialog::setDefaultExt(const wstring& ext)
{
	m_defaultExt = ext;
}

bool
FileDialog::getAddExtension()
{
	return m_addExtension;
}

void
FileDialog::setAddExtension(bool add)
{
	m_addExtension = add;
}

bool
FileDialog::RunDialog(Window* owner)
{
	OPENFILENAME ofn;       // common dialog box structure
	wchar_t szFile[260];       // buffer for file name
	//HWND hwnd;              // owner window

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof ofn);
	ofn.lStructSize = sizeof ofn;
	//ofn.hwndOwner = hwnd;
	ofn.hwndOwner = owner->handle();
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	//ofn.lpstrFile[0] = '\0';
	wcscpy(ofn.lpstrFile, m_fileName.c_str());
	ofn.nMaxFile = sizeof szFile;
	//ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	wchar_t szFilter[500];
	wcscpy(szFilter, m_filter.c_str());
	wchar_t* p = szFilter;
	while (*p != L'\0') {
		if (*p == L'|')
			*p = L'\0';
		p++;
	}
	p++;
	*p = L'\0';
	ofn.lpstrFilter = szFilter;
	//ofn.nFilterIndex = 1;
	ofn.nFilterIndex = m_filterIndex;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = NULL;
	ofn.lpstrInitialDir = m_initialDirectory.c_str();
	if (m_addExtension)  ofn.lpstrDefExt = m_defaultExt.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
//	if (GetOpenFileName(&ofn) == TRUE) {
	if (getOpenSaveFileName(&ofn) == TRUE) {
		setFileName(ofn.lpstrFile);
		return true;
	}
	return false;
}
