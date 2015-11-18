#pragma once

namespace Shutters {
	//using namespace std;


	class Icon {
	public:
		Icon(HICON handle);
		static Icon* fromHandle(HICON handle);
		HICON handle();
	private:
		HICON m_handle;
	};

}
