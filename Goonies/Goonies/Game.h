#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "InitialScreen.h"


#define SCREEN_WIDTH 576
#define SCREEN_HEIGHT 352

#define STATE_INTRO		0
#define STATE_MENU		1
#define STATE_RUN		2
#define STATE_GAME_OVER 3


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}


	static Game &instance()
	{
		static Game G;

		return G;
	}

	void init();
	bool update(int deltaTime);
	void render();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	bool bPlay;                       // Continue to play game?
	Scene scene;
	//InitialScreen scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time

};


#endif // _GAME_INCLUDE


