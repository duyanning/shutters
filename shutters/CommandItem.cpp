#include "wincpp.hpp"
#include "CommandItem.hpp"
#include "Menu.hpp"


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

//map<UINT, CommandItem*> CommandItem::id_to_pointer_map;

map<UINT, CommandItem*>&
G_Id_To_Pointer_Map()
{
	static map<UINT, CommandItem*> id_to_pointer_map;
	return id_to_pointer_map;
}

CommandItem::CommandItem(const wstring& text)
:
	MenuItem(text),
	m_id(0)
{
	m_id = genId();
	addToMap(m_id);
}

CommandItem::~CommandItem()
{
	disposeSelf();
}

UINT
CommandItem::getId()
{
	return m_id;
}

UINT CommandItem::m_newId = 5;

UINT
CommandItem::genId()
{
	return m_newId++;
}

CommandItem*
CommandItem::S_IdToPointer(UINT id)
{
	map<UINT, CommandItem*>::iterator pos = G_Id_To_Pointer_Map().find(id);
	if (pos != G_Id_To_Pointer_Map().end())
		return pos->second;
	return 0;
}

void
CommandItem::addToMap(UINT id)
{
	G_Id_To_Pointer_Map()[id] = this;
}

void
CommandItem::removeFromMap()
{
	G_Id_To_Pointer_Map().erase(getId());
}

void
CommandItem::disposeSelf()
{
	destroyId();
}

void
CommandItem::dispose()
{
	disposeSelf();
}

void
CommandItem::destroyId()
{
	if (m_id) {
		removeFromMap();
		m_id = 0;
	}
}

void
CommandItem::setText(const wstring& text)
{
	m_text = text;
	if (m_parentMenu) {
		::ModifyMenu(m_parentMenu->handle(), m_id, MF_STRING | MF_BYCOMMAND, m_id, m_text.c_str());
	}
}
