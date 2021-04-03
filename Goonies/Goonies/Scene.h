#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "pjLoadingScreen.h"
#include "Puntuacio.h"
#include "Bars.h"
#include "Skull.h"
#include "Enemy.h"


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
	void updateScene(bool portal);
	void restartGame();
	int nextScreen();
	int prevScreen();
	int goToScreen(int x);
	int addPoints(int points);
	int modifyHP(int healthPoints);
	int modifyExp(int expPoints);

	bool noHealth();
	glm::ivec2 getPlayerPosition();



private:
	void initShaders();
	bool colision_with_enemies(bool attack_side, int& enemy, int attack_dist, bool& hit_side);
	void setEnemyMap(int enemy_level);

private:
	TileMap *map, *map_enemy;
	pjLoadingScreen *goon;
	pjLoadingScreen* goonie = new pjLoadingScreen[6];
	pjLoadingScreen *evil;
	pjLoadingScreen *konami;
	pjLoadingScreen *msx;
	pjLoadingScreen *msx2;
	pjLoadingScreen *lletres;
	pjLoadingScreen *playStart;
	Bars* healthBar;
	Bars* expBar;
	Bullet *bullet;
	Puntuacio* puntuation = new Puntuacio[14];
	Player *player;
	Enemy *enemy;
	ShaderProgram texProgram, texProgram2;
	float currentTime;
	int estat;
	glm::mat4 projection;
	int level;
	int punts;
	int maxPunts;
	int health;
	int exp;
	string levelmap;
	int firstSkullLevel, maxSkullLevel;
};


#endif // _SCENE_INCLUDE

