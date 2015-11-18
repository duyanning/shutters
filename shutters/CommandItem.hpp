#pragma once

#include "MenuItem.hpp"
#include "Event.hpp"
#include "SafeMap.hpp"

namespace Shutters {

	using namespace std;

	class CommandItem : public MenuItem {
	public:
		//EVENT_TYPE(EventClicked, (CommandItem* cmd), (cmd));
		//EventClicked click;
		Event click;
		CommandItem(const wstring& text = wstring());
		~CommandItem();
		virtual void dispose();
		UINT getId();
		static CommandItem* S_IdToPointer(UINT);
		void setText(const wstring& text);
	protected:
		static UINT genId();
		static UINT m_newId;
	private:
		UINT m_id;
		//static map<UINT, CommandItem*> id_to_pointer_map;
		void addToMap(UINT id);
		void removeFromMap();
		void disposeSelf();	// non-virtual
		void destroyId();
	};

//	extern SafeMap<UINT, CommandItem*> cmdItemId_to_this_map;

};