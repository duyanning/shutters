#pragma once

#include "CommandItem.hpp"
#include "IMutuallyExclusiveOption.hpp"

namespace Shutters {
	
	using namespace std;

	class RadioButtonMenuItem : public CommandItem , public IMutuallyExclusiveOption {
		typedef CommandItem Base;
	public:
		RadioButtonMenuItem(const wstring& text = wstring());
		~RadioButtonMenuItem();

		void setChecked(bool b);
		bool checked();
	protected:
		void handleClicked(void* sender, EventArgs& e);
	private:
	};

}
