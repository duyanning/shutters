#include "wincpp.hpp"
#include "GdiplusManager.hpp"

using namespace Shutters;

GdiplusManager::GdiplusManager()
{
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStarupInput, 0);
}

GdiplusManager::~GdiplusManager()
{
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

//GdiplusManager g_gdiplus_manager;
//volatile GdiplusManager g_gdiplus_manager;  // volatile cannot ensure g_gdiplus_manager to be linked from library while no reference form application!
#pragma comment(lib, "GDIplus.lib")
