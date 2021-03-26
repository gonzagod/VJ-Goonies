#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "pjLoadingScreen.h"
#include "Puntuacio.h"
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
	int addPoints(int points);

private:
	void initShaders();

private:
	TileMap *map;
	pjLoadingScreen *goon;
	pjLoadingScreen* goonie = new pjLoadingScreen[6];
	pjLoadingScreen *evil;
	pjLoadingScreen *konami;
	pjLoadingScreen *msx; 
	pjLoadingScreen *msx2;
	pjLoadingScreen *lletres;
	pjLoadingScreen *playStart;
	Puntuacio* puntuation = new Puntuacio[14];
	Player *player;
	Skull *skull1;
	ShaderProgram texProgram;
	float currentTime;
	int estat;
	glm::mat4 projection;
	int level;
	int punts;
	string levelmap;

};


#endif // _SCENE_INCLUDE

