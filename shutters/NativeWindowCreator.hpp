#pragma once

namespace Shutters {

	class NativeWindowCreator {
	public:
		virtual HWND create() = 0;
	};

	NativeWindowCreator& getFrameWindowCreator();
	NativeWindowCreator& getChildWindowCreator();
	NativeWindowCreator& getNativeButtonCreator();
	NativeWindowCreator& getNativeTextBoxCreator();
	NativeWindowCreator& getNativeLabelCreator();
	NativeWindowCreator& getNativeListBoxCreator();
	NativeWindowCreator& getNativeComboBoxCreator();

}
