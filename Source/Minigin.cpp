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

	//HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(210);

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