#include "Component.hpp"
#include "Event.hpp"

namespace Shutters {

	class Timer : public Component {
	public:
		Timer();
		~Timer();

		bool enabled();
		void setEnabled(bool is);
		
		int interval();
		void setInterval(int i);

		void start();
		void stop();

		Event tick;
	protected:
	private:
		int m_interval;
		bool m_enabled;
		static void S_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	};

}
