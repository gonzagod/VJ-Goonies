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
	int goToScreen(int x);
	int addPoints(int points);

private:
	void initShaders();
	bool colision_with_enemies(bool attack_side, int& enemy, int attack_dist, bool& hit_side);

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
	static const int num_skulls_Scene1 = 3;
	Skull* skullsScene1 = new Skull[num_skulls_Scene1];
	ShaderProgram texProgram;
	float currentTime;
	int estat;
	glm::mat4 projection;
	int level;
	int punts;
	string levelmap;
	int initSkullsPos[num_skulls_Scene1][2] = { { 19,14 },{ 5,8 },{ 21,4 } };
	int skullsPerScreen[6] = { 0,0,0,1,2,0 };
	int firstSkullLevel, maxSkullLevel;
};


#endif // _SCENE_INCLUDE

