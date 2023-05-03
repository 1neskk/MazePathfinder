#include "stdafx.h"
#include "Application.h"

#ifdef DIST
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application application;
	while (application.isRunning())
	{
		application.Update();
		application.Render();
	}
	return EXIT_SUCCESS;
}

#else
int main() {
	Application application;

	while (application.isRunning())
	{
		application.Update();

		application.Render();
	}
	return EXIT_SUCCESS;
}
#endif
