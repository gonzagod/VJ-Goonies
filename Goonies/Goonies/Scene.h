#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "pjLoadingScreen.h"
#include "Skull.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void updateScene();
	int nextScreen();
	int prevScreen();

private:
	void initShaders();

private:
	TileMap *map;
	pjLoadingScreen *goon;
	pjLoadingScreen *goonie1;
	pjLoadingScreen *goonie2;
	pjLoadingScreen *goonie3;
	pjLoadingScreen *goonie4;
	pjLoadingScreen *goonie5;
	pjLoadingScreen *goonie6;
	pjLoadingScreen* goonie = new pjLoadingScreen[6];
	pjLoadingScreen *evil;
	pjLoadingScreen *konami;
	pjLoadingScreen *msx; 
	pjLoadingScreen *msx2;
	pjLoadingScreen *lletres;
	pjLoadingScreen *playStart;
	Player *player;
	Skull *skull1;
	ShaderProgram texProgram;
	float currentTime;
	int estat;
	glm::mat4 projection;
	int level;
	string levelmap;

};


#endif // _SCENE_INCLUDE

