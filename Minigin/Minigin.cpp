#include "MiniginPCH.h"
#include <vld.h>
#pragma comment(lib,"xinput.lib")
#include "MainGame.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	MainGame game{};
	game.Initialize();
	game.Run();

    return 0;
}