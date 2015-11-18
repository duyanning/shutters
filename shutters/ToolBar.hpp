#include "WinControl.hpp"

namespace Shutters {

	class ToolBarButton : public Component {
	public:
		void setText(const wstring& t);
	protected:
	private:
		wstring m_text;
	};

	class ToolBar : public WinControl {
		typedef WinControl Base;
	public:
		ToolBar();
		~ToolBar();

		void add(const wstring& t);
		void add(ToolBarButton& btn);
	protected:
	private:
	};

}
