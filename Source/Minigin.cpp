#include "MiniginPCH.h"
//#include <vld.h>
#include <ctime>
#pragma comment(lib,"xinput.lib")
#include "Game/MainGame.h"

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

	srand(static_cast<unsigned>(time(0)));

	MainGame* pGame = new MainGame();

	try {
		pGame->Initialize();
		pGame->Run();
	} catch (std::exception& ex) {
		Debug::LogError(ex.what());
	}

	delete pGame;	
	return 0;
}