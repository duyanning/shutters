#ifndef SHUTTERS_FILEDIALOG_HPP
#define SHUTTERS_FILEDIALOG_HPP

#include "CommonDialog.hpp"

using namespace std;

namespace Shutters {

class FileDialog : public CommonDialog {
public:
	FileDialog();

	const wstring& getFileName();
	void setFileName(const wstring& name);

	const wstring& getDefaultExt();
	void setDefaultExt(const wstring& ext);

	const wstring& getFilter();
	void setFilter(const wstring& filter);

	const wstring& getInitialDirectory();
	void setInitialDirectory(const wstring& filter);

	int getFilterIndex();
	void setFilterIndex(int filterIndex);

	bool getAddExtension();
	void setAddExtension(bool add);
protected:
	bool RunDialog(Window* owner);
private:
	//BOOL (*m_pfGetFileName)(LPOPENFILENAME);
	virtual BOOL getOpenSaveFileName(LPOPENFILENAME lpofn) = 0;
	wstring m_fileName;
	wstring m_defaultExt;
	wstring m_filter;
	wstring m_initialDirectory;
	int m_filterIndex;
	bool m_addExtension;
};

}

#endif
