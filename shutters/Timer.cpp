#include "wincpp.hpp"
#include "Timer.hpp"
#include "nurserWindow.hpp"
#include "EventArgs.hpp"

namespace Shutters {

Timer::Timer()
:
	m_interval(0),
	m_enabled(false)
{
}

Timer::~Timer()
{
	stop();
}

bool
Timer::enabled()
{
	return m_enabled;
}

void
Timer::setEnabled(bool is)
{
	if (is == m_enabled)  return;
	m_enabled = is;
}

int
Timer::interval()
{
	return m_interval;
}

void
Timer::setInterval(int i)
{
	if (i == m_interval)  return;
	m_interval = i;
}

void
Timer::start()
{
	m_enabled = true;
	::SetTimer(
			ShuttersImpl::getNurserWindow(),
			reinterpret_cast<UINT_PTR>(this),
			m_interval,
			reinterpret_cast<TIMERPROC>(S_TimerProc)
		);
}

void
Timer::stop()
{
	::KillTimer(ShuttersImpl::getNurserWindow(), reinterpret_cast<UINT_PTR>(this));
}

void
Timer::S_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	Timer* timer = reinterpret_cast<Timer*>(idEvent);
	if (timer && timer->enabled()) {
		EventArgs e;
		timer->tick.fire(0 , e);
	}
}

}
