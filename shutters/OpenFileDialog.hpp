#ifndef SHUTTERS_OPENFILEDIALOG_HPP
#define SHUTTERS_OPENFILEDIALOG_HPP

#include "FileDialog.hpp"

namespace Shutters {

class OpenFileDialog : public FileDialog {
public:
	OpenFileDialog();
	BOOL getOpenSaveFileName(LPOPENFILENAME lpofn);
protected:
	//bool RunDialog(Window* owner);

};

}

#endif
