// DemoObjectCulling.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DemoObjectCulling.h"
#include "DemoObjectCullingApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DemoObjectCullingApp App;
	App.Initialize();
	App.Run();
	App.Uninitialize();
    return 0;
}
