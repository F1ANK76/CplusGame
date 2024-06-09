#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEG_NEW new
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "game.h"
#include "player.h"
#include "enemycopy.h"
#include "bullet.h"

// https://www.youtube.com/watch?v=sCCTwT8IJAE&list=PLMcUoebWMS1muMsyLM6K7uGBIjzDKKUF-&index=32 / 32번 영상 보는중

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // 동적할당 및 메모리 누수 확인

	Game game;

	{
		game.Initialize();
		game.RunLoop();
		game.Shutdown();
	}

	return 0;
}
