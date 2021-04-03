#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "pjLoadingScreen.h"
#include "Puntuacio.h"
#include "Bars.h"
#include "Key.h"
#include "Padlock.h"
#include "Door.h"
#include "Goonie.h"
#include "GooniePoints.h"
#include "PowerUps.h"
#include "ViewPowerUp.h"
#include "WaterDrop.h"
#include "Steam.h"
#include "Stalactites.h"
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
	void restartGame();
	int nextScreen();
	int prevScreen();
	int goToScreen(int x);
	int addPoints(int points);
	int modifyHP(int healthPoints);
	int modifyExp(int expPoints);
	int addGoonies();

	bool noHealth();
	bool addKey();
	bool removeKey();
	bool keyStatus();
	bool portalStatus();

	void powerupHelmet();
	void powerupGrayRaincoat();
	void powerupHyperShoes();
	void powerupBlueSpellbook();
	void powerupYellowRaincoat();

	void godMode();

private:
	void initShaders();
	bool colision_with_enemies(bool attack_side, int& enemy, int attack_dist, bool& hit_side);
	bool collision_with_keys();
	bool collision_with_padlocks();
	bool collision_with_objects_door();
	bool collision_with_powerups();
	bool collision_with_waterdrops();
	bool collision_with_steam();
	bool collision_with_stalactites();

	void activateStalactites();
	

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
	Bars* healthBar;
	Bars* expBar;
	Key* playerKey;
	Puntuacio* puntuation = new Puntuacio[14];
	Player *player;
	GooniePoints* gooniePoints;
	ShaderProgram texProgram;
	ViewPowerUp* viewpu = new ViewPowerUp[5];
	float currentTime;
	int estat;
	glm::mat4 projection;
	int level;
	int punts;
	int maxPunts;
	int health;
	int exp;
	int gooniesRescued;
	bool key;
	bool isInPortal;
	string levelmap;
	int firstSkullLevel, maxSkullLevel;
	int firstKeyLevel, maxKeyLevel;
	int firstPadlockLevel, maxPadlockLevel;
	int firstDoorLevel, maxDoorLevel;
	int firstObjectLevel, maxObjectLevel;
	int firstPowerUpLevel, maxPowerUpLevel;
	int firstWaterDropLevel, maxWaterDropLevel;
	int firstStalactiteLevel, maxStalactiteLevel;
	int x = 3;
	bool Helmet, GrayRaincoat, BlueSpellbook, YellowRaincoat, HyperShoes;
	bool god;
};


#endif // _SCENE_INCLUDE

