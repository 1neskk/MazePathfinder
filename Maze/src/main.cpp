#include "stdafx.h"
#include "Application.h"

int main() {
	Application application;

	while (application.isRunning())
	{
		application.Update();

		application.Render();
	}
	return EXIT_SUCCESS;
}