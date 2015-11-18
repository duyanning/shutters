#pragma once

#include "Component.hpp"

namespace Shutters {

	using namespace std;

	class MenuItem;
	class CommandItem;
	class SubMenu;

	class Menu : public Component {
		typedef set<MenuItem*> Items;
	public:
		typedef Items::iterator iterator;
		iterator begin()
		{
			return m_items.begin();
		}

		iterator end()
		{
			return m_items.end();
		}
		void insert(SubMenu* subMenu);
		void insert(SubMenu& subMenu);
		void insert(CommandItem* cmd);
		void insert(CommandItem& cmd);
		Menu();
		virtual ~Menu();
		HMENU handle()
		{
			return m_hMenu;
		}
		virtual void dispose();
	protected:
		HMENU m_hMenu;
	private:
		Items m_items;
		void disposeSelf();		// non-virtual
		void destroyHandle();
		//static UINT genId();
		//static UINT m_newId;
	};

};