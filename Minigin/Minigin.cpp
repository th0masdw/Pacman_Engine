#include "MiniginPCH.h"
#include <vld.h>
#pragma comment(lib,"xinput.lib")
#include "MainGame.h"

int main(int argc, wchar_t* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	WinMain(GetModuleHandle(0), 0, 0, SW_SHOW);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);
	UNREFERENCED_PARAMETER(pCmdLine);

	MainGame* pGame = new MainGame();

	try {
		pGame->Initialize();
		pGame->Run();
	} catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;	
	}

	delete pGame;	
	return 0;
}