#pragma once

namespace Shutters {
	//using namespace std;


	class Cursor {
	public:
		Cursor(HCURSOR handle);
		HCURSOR handle();
		static void setCurrent(Cursor* cursor);
	private:
		HCURSOR m_handle;
	};

}
