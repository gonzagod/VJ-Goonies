#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
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
	bool colision_with_enemies(bool attack_side, int& enemy, int attack_dist, bool& hit_side);

private:
	TileMap *map;
	Player *player;
	static const int num_skulls_Scene1 = 3;
	Skull* skullsScene1 = new Skull[num_skulls_Scene1];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int level = 1;
	string levelmap;
	int initSkullsPos[num_skulls_Scene1][2] = { {19,14}, {5,8}, {21,4} };
	int skullsPerScreen1[3] = { 1,2,0 };
	int firstSkulli;
};


#endif // _SCENE_INCLUDE

