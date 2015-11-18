#include "wincpp.hpp"
#include "ControlCollection.hpp"
#include "Window.hpp"

namespace Shutters {

ControlCollection::ControlCollection(Window* owner)
:
	m_owner(owner)
{
}

void
ControlCollection::add(Window* child)
{
	::SetParent(child->handle(), m_owner->handle());

	ControlEventArgs e;
	e.control = child;
	m_owner->onControlAdded(e);
}

void
ControlCollection::add(Window& child)
{
	add(&child);
}

void
ControlCollection::remove(Window*)
{
}

void
ControlCollection::clear()
{
}

void
ControlCollection::setOwner(Window* owner)
{
	m_owner = owner;
}

} // namespace Shutters