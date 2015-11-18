#pragma once

namespace Shutters {

class Window;

class ControlCollection {
public:
	ControlCollection(Window* owner);
	void add(Window* child);
	void add(Window& child);
	void remove(Window* child);
	void clear();
private:
	Window* m_owner;

	friend class Window;
	void setOwner(Window* owner);
};

}
