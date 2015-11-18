#pragma once

#include "CommandItem.hpp"
#include "IStateOption.hpp"

namespace Shutters {
	
	using namespace std;

	class CheckBoxMenuItem : public CommandItem , public IStateOption {
		typedef CommandItem Base;
	public:
		CheckBoxMenuItem(const wstring& text = wstring());
		~CheckBoxMenuItem();

		void setChecked(bool b);
		bool checked();
	protected:
		void handleClicked(void* sender, EventArgs& e);
	private:
	};

}
