#ifndef SHUTTERS_SAVEFILEDIALOG_HPP
#define SHUTTERS_SAVEFILEDIALOG_HPP

#include "FileDialog.hpp"

namespace Shutters {

class SaveFileDialog : public FileDialog {
public:
	SaveFileDialog();
	BOOL getOpenSaveFileName(LPOPENFILENAME lpofn);
protected:
	//bool RunDialog(Window* owner);

};

}

#endif
