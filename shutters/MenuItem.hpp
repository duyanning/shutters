#pragma once

#include "Component.hpp"

namespace Shutters {

	using namespace std;

	class Menu;

	class MenuItem : public Component {
		friend Menu;
	public:
		MenuItem(const wstring& text)
		:
			m_text(text),
			m_parentMenu(0)
		{
		}

		virtual ~MenuItem() = 0;
		const wstring& text();
		virtual void dispose();
		virtual void setText(const wstring& text) = 0;;
		wstring m_text;
	protected:
		Menu* m_parentMenu;
	private:
		void disposeSelf();
	};
};