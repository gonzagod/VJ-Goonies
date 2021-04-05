#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


#define SCREEN_WIDTH 672
#define SCREEN_HEIGHT 416

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
	int nextScreen();
	int prevScreen();
	int goToScreen(int level);
	int addPoints(int points);
	int modifyHP(int healthPoints);
	int modifyExp(int expPoints);
	bool addKey();
	bool removeKey();
	bool noHealth();
	bool keyStatus();
	void player_shoot(bool side);

	void play_goonies1(bool play);
	void play_sound1_3(bool play);
	void play_jump();
	void play_skull_die();
	void play_potion();

	int addGoonies();

	//Powerups
	void powerupHelmet();
	void powerupGrayRaincoat();
	void powerupHyperShoes();
	void powerupBlueSpellbook();
	void powerupYellowRaincoat();

	void restartGame();
	void gameOver();
	void gameWin();
	int howManyGoonies();

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

	void updateEnemyMap();

private:
	bool bPlay;                       // Continue to play game?
	int points;
	int higherPuntuation;
	Scene scene;
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time

};


#endif // _GAME_INCLUDE


