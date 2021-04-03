#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <crtdbg.h> 


#define SCREEN_X 0
#define SCREEN_Y 0



#define INIT_PLAYER_X_TILES 17.5
#define INIT_PLAYER_Y_TILES 11

#define INIT_MSX_X_TILES -15
#define INIT_MSX2_X_TILES 40
#define INIT_MSX_Y_TILES 4

#define INIT_SKULL_X_TILES 24
#define INIT_SKULL_Y_TILES 14

#define GOONIE_INIT_X_TILES 8
#define GOONIE_INIT_Y_TILES 13

#define GOON_INIT_X_TILES 8
#define GOON_INIT_Y_TILES 13

#define EVIL_INIT_X_TILES 28
#define EVIL_INIT_Y_TILES 13

#define KONAMI_INIT_X_TILES 17
#define KONAMI_INIT_Y_TILES 14

#define LLETRES_INIT_X_TILES -20
#define LLETRES_INIT_Y_TILES -20

#define PUNTUATION_INIT_X_TILES 5
#define PUNTUATION_INIT_Y_TILES 0

#define HEALTHBAR_INIT_X_TILES 20
#define HEALTHBAR_INIT_Y_TILES 1

#define EXPBAR_INIT_X_TILES 20
#define EXPBAR_INIT_Y_TILES 2

#define INIT_ENEMY_X_TILES 34
#define INIT_ENEMY_Y_TILES 11

#define KEY_INIT_X_TILES 30
#define KEY_INIT_Y_TILES 24

#define GOONIE_POINTS_X_TILES 32
#define GOONIE_POINTS_Y_TILES 23

#define POWERUP_X_TILES 7
#define POWERUP_Y_TILES 23

static const int num_skulls_Scene = 21;
Skull* skullsScene = new Skull[num_skulls_Scene];
int skullsPerScreen[18] = { 0,0,0,1,2,3,0,2,2,1,0,1,0,2,1,2,2,2 };
int initSkullsPos[num_skulls_Scene][2] = { { 24,17 },{ 10,11 },{ 26,7  },{ 23,7  },{ 25,13 },{ 17,17 },
										   { 18,9  },{ 18,19 },{ 16,5  },{ 26,11 },
										   {  8,5  },{ 20,17 },
										   { 10,13 },{ 14,19 },{ 25,19 },
										   { 22,15 },{  6,17 },{ 17,11 },{ 20,17 },{  8,9 },{ 11,21 } };
int enemyPositions[4][2] = { {34,11}, {10,11}, {22,9}, {24,11} };
static const int num_keys_Scene = 14;
Key* keyScene = new Key[num_keys_Scene];
int keysPerScreen[18] = { 0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,2 };
int initKeysPos[num_keys_Scene][3] = { { 16,17,1 },{ 30,7,1 },{ 14,17,1 },{ 23,5,1 },{ 35,19,1 },{ 22,5,1 },{ 14,5,1 },{ 27,13,1 },{ 9,7,1 },{ 21,5,1 },{ 19,9,1 },{ 14,17,1 },{ 15,5,1 },{ 6,9,1 } };

static const int num_padlocks_Scene = 14;
Padlock* padlockScene = new Padlock[num_padlocks_Scene];
int padlocksPerScreen[18] = { 0,0,0,1,0,2,1,1,0,0,2,0,2,0,2,0,1,2 };
int initPadlocksPos[num_padlocks_Scene][3] = { { 27,17,1 },{ 32,13,1 },{ 32,12,1 },{ 7,11,1 },{ 25,19,1 },{ 15,11,1 },{ 15,10,1 },{ 21,17,1 },{ 21,16,1 },{ 32,5,1 },{ 32,4,1 },{ 24,17,1 },{ 24,9,1 },{ 24,8,1 } };

static const int num_door_Scene = 9;
Door* doorScene = new Door[num_door_Scene];
int doorPerScreen[18] = { 0,0,0,1,0,1,1,1,0,0,1,0,1,0,1,0,1,1 };
int DoorPos[num_door_Scene][3] = { { 28,15,1 },{ 33,11,1 },
{ 8,9,1 },{ 26,17,1 },
{ 16,9,1 },
{ 22,15,1 },{ 33,3,1 },
{ 25,15,1 },{ 25,7,1 } };

static const int num_objectes_porta_Scene = 9;
Goonie* objectesScene = new Goonie[num_objectes_porta_Scene];
int objectesPerScreen[18] = { 0,0,0,1,0,1,1,1,0,0,1,0,1,0,1,0,1,1 };
int objectPos[num_objectes_porta_Scene][3] = { { 29,17,1 },{ 34,13,1 },{ 9,11,1 },{ 27,19,1 },{ 17,11,1 },{ 23,17,1 },{ 34,5,1 },{ 26,17,1 },{ 26,9,1 } };

static const int num_power_ups = 5;
PowerUps* powerupsScene = new PowerUps[num_power_ups];
int powerUpsPerScreen[18] = { 0,0,0,1,0,0,1,0,0,1,1,0,0,0,1,0,0,0 };
int powerupsPos[num_power_ups][3] = { { 14,11,1 },{ 16,5,1 },{ 17,5,1 },{ 11,11,1 },{ 15,9,1 } };

static const int num_water_drop = 20;
WaterDrop* waterdropScene = new WaterDrop[num_water_drop];
int waterDropsPerScreen[18] = { 0,0,0,2,1,1,0,0,1,1,1,2,1,0,3,2,2,3 };
int initwaterdropsPos[num_water_drop][2] = { { 19,14 },{ 31,8 },{ 15,4 },{ 27,10 },
{ 11,8 },
{ 15,8 },{ 23,8 },{ 31,8 },{ 23,14 },
{ 7,10 },{ 11,16 },{ 27,12 },{ 31,16 },
{ 23,4 },{ 11,14 },{ 23,8 },{ 23,14 },{ 31,12 },{ 27,16 },{ 15,8 } };

Steam* steam = new Steam[6];
int steamPos[6][2] = { { 16,8 },{ 16,16 },{ 32,16 },{ 19,8 },{ 19,16 },{ 27,16 } };

static const int num_stalactites = 10;
Stalactites* stalactitesScene = new Stalactites[num_stalactites];
int stalactitesPerScreen[18] = { 0,0,0,1,0,0,0,2,0,0,2,1,1,1,0,1,1,0 };
int initStalactitesPos[num_stalactites][3] = { { 20,8,1 },{ 20,12,1 },{ 32,16,1 },{ 32,8,1 },{ 8,4,1 },{ 8,8,1 },{ 20,4,1 },{ 8,16,1 },{ 12,4,1 },{ 13,8,1 } };

Scene::Scene()
{
	map = NULL;
	player = NULL;
	key = false;
	level = 0;
	estat = 0;
	health = 20;
	exp = 0;
	god = false;
	HyperShoes = false;
	GrayRaincoat = false;
	YellowRaincoat = false;
	Helmet = false;
	BlueSpellbook = false;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/FonsBlau.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	firstSkullLevel = 0;
	maxSkullLevel = firstSkullLevel + skullsPerScreen[level];

	skullsScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	skullsScene[0].setPosition(glm::vec2(initSkullsPos[0][0] * map->getTileSize(), initSkullsPos[0][1] * map->getTileSize()));
	skullsScene[0].setTileMap(map);

	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize(), INIT_ENEMY_Y_TILES * map->getTileSize()));
	enemy->setTileMap(map);

	bullet = new Bullet();
	bullet->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	firstKeyLevel = 0;
	maxKeyLevel = firstKeyLevel + keysPerScreen[level];
	keyScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	keyScene[0].setPosition(glm::vec2(initKeysPos[0][0] * map->getTileSize(), initKeysPos[0][1] * map->getTileSize()));
	keyScene[0].setTileMap(map);

	firstPadlockLevel = 0;
	maxPadlockLevel = firstPadlockLevel + padlocksPerScreen[level];

	padlockScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	padlockScene[0].setPosition(glm::vec2(initPadlocksPos[0][0] * map->getTileSize(), initPadlocksPos[0][1] * map->getTileSize()));
	padlockScene[0].setTileMap(map);

	firstDoorLevel = 0;
	maxDoorLevel = firstDoorLevel + doorPerScreen[level];

	doorScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	doorScene[0].setPosition(glm::vec2(DoorPos[0][0] * map->getTileSize(), DoorPos[0][1] * map->getTileSize()));
	doorScene[0].setTileMap(map);

	firstObjectLevel = 0;
	maxObjectLevel = firstObjectLevel + objectesPerScreen[level];

	objectesScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	objectesScene[0].setPosition(glm::vec2(objectPos[0][0] * map->getTileSize(), objectPos[0][1] * map->getTileSize()));
	objectesScene[0].setTileMap(map);

	firstPowerUpLevel = 0;
	maxPowerUpLevel = firstPowerUpLevel + powerUpsPerScreen[level];

	powerupsScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	powerupsScene[0].setPosition(glm::vec2(powerupsPos[0][0] * map->getTileSize(), powerupsPos[0][1] * map->getTileSize()));
	powerupsScene[0].setTileMap(map);

	firstWaterDropLevel = 0;
	maxWaterDropLevel = firstWaterDropLevel + waterDropsPerScreen[level];

	waterdropScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	waterdropScene[0].setPosition(glm::vec2(initwaterdropsPos[0][0] * map->getTileSize(), initwaterdropsPos[0][1] * map->getTileSize()));
	waterdropScene[0].setTileMap(map);

	firstStalactiteLevel = 0;
	maxStalactiteLevel = firstStalactiteLevel + stalactitesPerScreen[level];

	stalactitesScene[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	stalactitesScene[0].setPosition(glm::vec2(initStalactitesPos[0][0] * map->getTileSize(), initStalactitesPos[0][1] * map->getTileSize()));
	stalactitesScene[0].setTileMap(map);

	for (int i = 0; i < 5; ++i) {
		viewpu[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		viewpu[i].setPosition(glm::vec2(POWERUP_X_TILES * map->getTileSize() + 32 * i, POWERUP_Y_TILES * map->getTileSize()));
		viewpu[i].setTileMap(map);
	}

	for (int i = 0; i < 6; ++i) {
		steam[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		steam[i].setPosition(glm::vec2(steamPos[i][0] * map->getTileSize(), steamPos[i][1] * map->getTileSize()));
		steam[i].setTileMap(map);
	}

	msx = new pjLoadingScreen();
	msx->initMsx(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	msx->setPosition(glm::vec2(INIT_MSX_X_TILES * map->getTileSize(), INIT_MSX_Y_TILES * map->getTileSize()));
	msx->setTileMap(map);

	msx2 = new pjLoadingScreen();
	msx2->initMsx(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	msx2->setPosition(glm::vec2(INIT_MSX2_X_TILES * map->getTileSize(), INIT_MSX_Y_TILES * map->getTileSize()));
	msx2->setTileMap(map);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	goon = new pjLoadingScreen();
	goon->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goon->setPosition(glm::vec2(GOON_INIT_X_TILES * map->getTileSize(), GOON_INIT_Y_TILES * map->getTileSize()));
	goon->setTileMap(map);

	for (int i = 0; i < 6; ++i) {
		goonie[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		goonie[i].setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
		goonie[i].setTileMap(map);
	}

	for (int i = 0; i < 6; ++i) {
		puntuation[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		puntuation[i].setPosition(glm::vec2(PUNTUATION_INIT_X_TILES * map->getTileSize() + 16 * (i + 4), PUNTUATION_INIT_Y_TILES * map->getTileSize() + 16));
		puntuation[i].setTileMap(map);
	}
	for (int i = 6; i < 12; ++i) {
		puntuation[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		puntuation[i].setPosition(glm::vec2(PUNTUATION_INIT_X_TILES * map->getTileSize() + 16 * (i - 2), PUNTUATION_INIT_Y_TILES * map->getTileSize() + 32));
		puntuation[i].setTileMap(map);
	}
	puntuation[12].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	puntuation[12].setPosition(glm::vec2(PUNTUATION_INIT_X_TILES * map->getTileSize() + 16 * (27), PUNTUATION_INIT_Y_TILES * map->getTileSize() + 32));
	puntuation[12].setTileMap(map);

	puntuation[13].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	puntuation[13].setPosition(glm::vec2(PUNTUATION_INIT_X_TILES * map->getTileSize() + 16 * (30), PUNTUATION_INIT_Y_TILES * map->getTileSize() + 32));
	puntuation[13].setTileMap(map);

	gooniePoints = new GooniePoints();
	gooniePoints->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	gooniePoints->setPosition(glm::vec2(GOONIE_POINTS_X_TILES* map->getTileSize() + 2, GOONIE_POINTS_Y_TILES * map->getTileSize()));
	gooniePoints->setTileMap(map);

	healthBar = new Bars();
	healthBar->initHealthBar(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	healthBar->setPosition(glm::vec2(HEALTHBAR_INIT_X_TILES * map->getTileSize(), HEALTHBAR_INIT_Y_TILES * map->getTileSize()));
	healthBar->setTileMap(map);

	expBar = new Bars();
	expBar->initExpBar(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	expBar->setPosition(glm::vec2(EXPBAR_INIT_X_TILES * map->getTileSize(), EXPBAR_INIT_Y_TILES * map->getTileSize()));
	expBar->setTileMap(map);

	playerKey = new Key();
	playerKey->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playerKey->setPosition(glm::ivec2(KEY_INIT_X_TILES * map->getTileSize(), KEY_INIT_Y_TILES * map->getTileSize()));
	playerKey->setTileMap(map);

	evil = new pjLoadingScreen();
	evil->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	evil->setPosition(glm::vec2(EVIL_INIT_X_TILES * map->getTileSize(), EVIL_INIT_Y_TILES * map->getTileSize()));
	evil->setTileMap(map);

	konami = new pjLoadingScreen();
	konami->initKonami(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	konami->setPosition(glm::vec2(KONAMI_INIT_X_TILES * map->getTileSize(), KONAMI_INIT_Y_TILES * map->getTileSize()));

	lletres = new pjLoadingScreen();
	lletres->initLletres(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	lletres->setPosition(glm::vec2(LLETRES_INIT_X_TILES * map->getTileSize(), LLETRES_INIT_Y_TILES * map->getTileSize()));


	playStart = new pjLoadingScreen();
	playStart->initPlayStart(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playStart->setPosition(glm::vec2(LLETRES_INIT_X_TILES * map->getTileSize(), LLETRES_INIT_Y_TILES * map->getTileSize()));


	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	//int i = goToScreen(3);
}

void Scene::restartGame() {
	level = 3;
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	key = false;
	health = 20;
	exp = 0;
	punts = 0;
	HyperShoes = false;
	GrayRaincoat = false;
	YellowRaincoat = false;
	Helmet = false;
	BlueSpellbook = false;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (punts > maxPunts) maxPunts = punts;
	if (Game::instance().getKey(48)) {
		powerupHelmet();
	}
	if (Game::instance().getKey(49)) {
		powerupHyperShoes();
	}
	if (Game::instance().getKey(50)) {
		powerupGrayRaincoat();
	}
	if (Game::instance().getKey(51)) {
		powerupBlueSpellbook();
	}
	if (Game::instance().getKey(52)) {
		powerupYellowRaincoat();
	}
	if (Game::instance().getKey(103)) { //g
		godMode();
	}
	if (Game::instance().getKey(104)) { //h
		if (level >= 3 && level < 18) nextScreen();
	}
	if (Game::instance().getKey(105)) { //i
		if (level > 4) prevScreen();
	}
	if ((level > 0 && level <= 2) && Game::instance().getKey(32)) {
	estat = 22;
	level = 2;
	}
	if (!portalStatus()) {
		switch (level) {
		case(0):
			msx->update(deltaTime, 0, estat);
			msx2->update(deltaTime, 1, estat);
			lletres->update(deltaTime, 6, estat);
			break;
		case(1):
			konami->update(deltaTime, 2, estat);
			break;
		case(2):
			if (estat == 5) 			map = TileMap::createTileMap("levels/LoadingScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			if (estat == 22)			map = TileMap::createTileMap("levels/LoadingScreen2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			if (estat >= 4) goon->update(deltaTime, 3, estat);
			if (estat >= 6 && estat <= 11) goonie[estat - 6].update(deltaTime, 4, estat);
			if (estat >= 12 && estat <= 21) evil->update(deltaTime, 5, estat);
			if (estat == 22 || estat == 23) playStart->update(deltaTime, 7, estat);
			break;
		default:
			if (!portalStatus()) {
				for (int i = firstSkullLevel; i < maxSkullLevel; ++i) {
					skullsScene[i].update(deltaTime);
				}
			}
			for (int j = firstKeyLevel; j < maxKeyLevel; ++j) {
				keyScene[j].update(deltaTime, 0);
			}
			for (int k = firstPadlockLevel; k < maxPadlockLevel; ++k) {
				padlockScene[k].update(deltaTime);
			}
			for (int l = firstDoorLevel; l < maxDoorLevel; ++l) {
				_RPT1(0, "DoorLevel = %d\n", l);
				if (l == 2 || l == 3) doorScene[l].update(deltaTime, 1);
				else if (l == 7 || l == 8) doorScene[l].update(deltaTime, 2);
				else doorScene[l].update(deltaTime, 0);
			}

			for (int m = firstObjectLevel; m < maxObjectLevel; ++m) {
				switch (m) {
					_RPT1(0, "ObjectLevel = %d\n", m);
				case 0:
					objectesScene[m].update(deltaTime, 0);
					break;
				case 2:
					objectesScene[m].update(deltaTime, 1);
					break;
				case 3:
					objectesScene[m].update(deltaTime, 4);
					break;
				case 7:
					objectesScene[m].update(deltaTime, 2);
					break;
				case 8:
					objectesScene[m].update(deltaTime, 5);
					break;
				default:
					objectesScene[m].update(deltaTime, 3);
					break;
				}

			}
			for (int n = firstPowerUpLevel; n < maxPowerUpLevel; ++n) {
				powerupsScene[n].update(deltaTime);
			}
			for (int o = firstWaterDropLevel; o < maxWaterDropLevel; ++o) {
				waterdropScene[o].update(deltaTime);
			}
			for (int p = firstStalactiteLevel; p < maxStalactiteLevel; ++p) {
				switch (p) {
				case 1:
					stalactitesScene[p].update(deltaTime, 1);
					break;
				case 2:
					stalactitesScene[p].update(deltaTime, 1);
					break;
				case 8:
					stalactitesScene[p].update(deltaTime, 2);
					break;
				case 9:
					stalactitesScene[p].update(deltaTime, 2);
					break;
				default:
					stalactitesScene[p].update(deltaTime, 0);
					break;
				}
			}
			break;
		}
	}
	if (!portalStatus()) {
		switch (level) {
		case(12):
			for (int i = 0; i < 3; ++i) {
				steam[i].update(deltaTime, 0);
			}
			for (int i = 3; i < 6; ++i) {
				steam[i].update(deltaTime, 1);
			}
			break;
		default:
			break;
		}
	}
	if (level >= 3) {
		for (int i = 0; i < 8; ++i) {
			puntuation[i].update(deltaTime, i, maxPunts, level);
		}
		for (int i = 8; i < 14; ++i) {
			puntuation[i].update(deltaTime, i, punts, level);
		}
		healthBar->update(deltaTime, health);
		expBar->update(deltaTime, exp);
		player->update(deltaTime);
		playerKey->update(deltaTime, 1);
		gooniePoints->update(deltaTime, gooniesRescued);

		for (int i = 0; i < 5; ++i) {
			switch (i) {
			case 0:
				if (GrayRaincoat) viewpu[i].update(deltaTime, 0);
				break;
			case 1:
				if (Helmet) viewpu[i].update(deltaTime, 1);
				break;
			case 2:
				if (HyperShoes) viewpu[i].update(deltaTime, 2);
				break;
			case 3:
				if (YellowRaincoat) viewpu[i].update(deltaTime, 3);
				break;
			case 4:
				if (BlueSpellbook) viewpu[i].update(deltaTime, 4);
				break;
			}
		}

		glm::ivec2 PlayerPos = getPlayerPosition();
		enemy->setPlayerPos(PlayerPos, level);
		int enemy_level = enemy->getLevelEnemy();
		setEnemyMap(enemy_level);
		enemy->update(deltaTime);
		glm::ivec2 EnemyPos = enemy->getPosition();
		if (enemy->isShot()) {
			bool b_dir = enemy->getBulletDir();
			bullet->setTileMap(map);
			if (b_dir) bullet->setPosition(glm::vec2(EnemyPos.x + 32, EnemyPos.y+4));
			else bullet->setPosition(glm::vec2(EnemyPos.x - 16, EnemyPos.y+4));
			bullet->setDirection(b_dir);
		}

		if (bullet->is_Alive()) bullet->update(deltaTime);

		bool attack_side = true; //True = LEFT ||False = Right
		int num_enemy = 0;
		bool player_attacking = player->isAttacking(attack_side);
		bool hit = false;
		bool hit_side = true; //True = LEFT ||False = Right
		if (player_attacking) {
			_RPT1(0, "attack_side = %d\n", attack_side);
			hit = colision_with_enemies(attack_side, num_enemy, 8, hit_side);
		}
		else hit = colision_with_enemies(attack_side, num_enemy, 0, hit_side);
		if (hit) {
			if (num_enemy == 22) {
				bool bullet_hit = player->got_hit();
				if (bullet_hit) bullet->player_hit();
			}
			else {
				if (player_attacking && attack_side == hit_side) {
					if (num_enemy < 21) skullsScene[num_enemy].die();
					else if (num_enemy == 21) enemy->get_damage();
				}
				else {
					bool fratelli_hit = false;
					if (num_enemy < 21) bool enemy_hit = player->got_hit();
					else if (num_enemy == 21 && enemy->can_dmg()) fratelli_hit = player->got_hit();
					if (fratelli_hit) enemy->collided_player();
				}
			}
		}
		bool colisio = collision_with_keys();
		colisio = collision_with_padlocks();
		colisio = collision_with_objects_door();
		colisio = collision_with_powerups();
		colisio = collision_with_waterdrops();
		colisio = collision_with_steam();
		colisio = collision_with_stalactites();
		activateStalactites();
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();

	switch (level)
	{
	case(0):
		msx->render();
		msx2->render();
		lletres->render();
		break;
	case(1):
		konami->render();
		break;
	case(2):
		if (estat >= 5 && estat <= 21) goon->render();
		if (estat >= 6 && estat <= 11) {
			for (int i = 0; i < estat - 5; ++i) {
				goonie[i].render();
			}
		}
		else if (estat >= 12 && estat <= 13) {
			for (int i = 0; i < 6; ++i) {
				goonie[i].render();
			}
		}

		else if (estat >= 14 && estat <= 18) {
			for (int i = 5; i > estat - 14; --i) {
				goonie[i].render();
			}
		}

		if (estat >= 12 && estat <= 21) evil->render();
		if (estat == 22 || estat == 23) playStart->render();
		break;
	case(12):
		for (int i = 0; i < 3; ++i) {
			steam[i].render();
		}
		for (int i = 3; i < 6; ++i) {
			steam[i].render();
		}
		break;
	default:
		break;

	}
	if (level >= 3) {
		for (int i = 0; i < 14; ++i) {
			puntuation[i].render();
		}
		healthBar->render();
		expBar->render();
		playerKey->render(1);
		gooniePoints->render();
		for (int j = firstKeyLevel; j < maxKeyLevel; ++j) {
			keyScene[j].render(0);
		}
		for (int k = firstPadlockLevel; k < maxPadlockLevel; ++k) {
			padlockScene[k].render();
		}
		for (int l = firstDoorLevel; l < maxDoorLevel; ++l) {
			doorScene[l].render();
		}
		for (int m = firstObjectLevel; m < maxObjectLevel; ++m) {
			objectesScene[m].render();
		}
		for (int n = firstPowerUpLevel; n < maxPowerUpLevel; ++n) {
			powerupsScene[n].render();
		}
		for (int o = firstWaterDropLevel; o < maxWaterDropLevel; ++o) {
			waterdropScene[o].render();
		}
		for (int p = firstStalactiteLevel; p < maxStalactiteLevel; ++p) {
			stalactitesScene[p].render();
		}
		if (!portalStatus()) {
			for (int i = firstSkullLevel; i < maxSkullLevel; ++i) {
				skullsScene[i].render();
			}
		}

		for (int i = 0; i < 5; ++i) {
			switch (i) {
			case 0:
				if (GrayRaincoat) viewpu[i].render();
				break;
			case 1:
				if (Helmet) viewpu[i].render();
				break;
			case 2:
				if (HyperShoes) viewpu[i].render();
				break;
			case 3:
				if (YellowRaincoat) viewpu[i].render();
				break;
			case 4:
				if (BlueSpellbook) viewpu[i].render();
				break;
			}
		}
		int enemyLevel = enemy->getLevelEnemy();
		if(enemyLevel == level && enemy->is_Alive()) enemy->render();
		if (bullet->is_Alive()) bullet->render();
		player->render();
	}
}

int Scene::nextScreen()
{
	++level;
	firstSkullLevel = maxSkullLevel;
	maxSkullLevel += skullsPerScreen[level];
	firstKeyLevel = maxKeyLevel;
	maxKeyLevel += keysPerScreen[level];
	firstPadlockLevel = maxPadlockLevel;
	maxPadlockLevel += padlocksPerScreen[level];
	firstDoorLevel = maxDoorLevel;
	maxDoorLevel += doorPerScreen[level];
	firstObjectLevel = maxObjectLevel;
	maxObjectLevel += objectesPerScreen[level];
	firstPowerUpLevel = maxPowerUpLevel;
	maxPowerUpLevel += powerUpsPerScreen[level];
	firstWaterDropLevel = maxWaterDropLevel;
	maxWaterDropLevel += waterDropsPerScreen[level];
	for (int i = firstStalactiteLevel; i < maxStalactiteLevel; ++i) {
		if (initStalactitesPos[i][2] == 0) stalactitesScene[i].disappear();
	}
	firstStalactiteLevel = maxStalactiteLevel;
	maxStalactiteLevel += stalactitesPerScreen[level];
	_RPT1(0, "New firstSkullLevel = %d\n", firstSkullLevel);
	_RPT1(0, "New maxSkullLevel = %d\n", maxSkullLevel);
	updateScene(false);
	return level;
}

int Scene::prevScreen()
{
	--level;
	firstSkullLevel -= skullsPerScreen[level];
	maxSkullLevel = firstSkullLevel + skullsPerScreen[level];
	firstKeyLevel -= keysPerScreen[level];
	maxKeyLevel = firstKeyLevel + keysPerScreen[level];
	firstPadlockLevel -= padlocksPerScreen[level];
	maxPadlockLevel = firstPadlockLevel + padlocksPerScreen[level];
	firstDoorLevel -= doorPerScreen[level];
	maxDoorLevel = firstDoorLevel + doorPerScreen[level];
	firstObjectLevel -= objectesPerScreen[level];
	maxObjectLevel = firstObjectLevel + objectesPerScreen[level];
	firstPowerUpLevel -= powerUpsPerScreen[level];
	maxPowerUpLevel = firstPowerUpLevel + powerUpsPerScreen[level];
	firstWaterDropLevel -= waterDropsPerScreen[level];
	maxWaterDropLevel = firstWaterDropLevel + waterDropsPerScreen[level];
	for (int i = firstStalactiteLevel; i < maxStalactiteLevel; ++i) {
		if (initStalactitesPos[i][2] == 0) stalactitesScene[i].disappear();
	}
	firstStalactiteLevel -= stalactitesPerScreen[level];
	maxStalactiteLevel = firstStalactiteLevel + stalactitesPerScreen[level];
	_RPT1(0, "New firstSkullLevel = %d\n", firstSkullLevel);
	_RPT1(0, "New maxSkullLevel = %d\n", maxSkullLevel);
	updateScene(false);
	return level;
}

int Scene::goToScreen(int x) {
	level = x;
	if (level == 0) firstSkullLevel = 0;
	else {
		int sumSkulls = 0;
		for (int i = 0; i < level; ++i) sumSkulls += skullsPerScreen[i];
		firstSkullLevel = sumSkulls;
	}if (level == 0) firstKeyLevel = 0;
	else {
		int numKeys = 0;
		for (int j = 0; j < level; ++j) numKeys += keysPerScreen[j];
		firstKeyLevel = numKeys;
	}

	if (level == 0) firstPadlockLevel = 0;
	else {
		int numPadlocks = 0;
		for (int k = 0; k < level; ++k) numPadlocks += padlocksPerScreen[k];
		firstPadlockLevel = numPadlocks;
	}
	if (level == 0) firstDoorLevel = 0;
	else {
		int numDoors = 0;
		for (int l = 0; l < level; ++l) numDoors += doorPerScreen[l];
		firstDoorLevel = numDoors;
	}
	if (level == 0) firstObjectLevel = 0;
	else {
		int numObjectes = 0;
		for (int m = 0; m < level; ++m) numObjectes += objectesPerScreen[m];
		firstObjectLevel = numObjectes;
	}
	if (level == 0) firstPowerUpLevel = 0;
	else {
		int numPowerUp = 0;
		for (int n = 0; n < level; ++n) numPowerUp += powerUpsPerScreen[n];
		firstPowerUpLevel = numPowerUp;
	}
	if (level == 0) firstWaterDropLevel = 0;
	else {
		int numWaterDrops = 0;
		for (int o = 0; o < level; ++o) numWaterDrops += waterDropsPerScreen[o];
		firstWaterDropLevel = numWaterDrops;
	}
	if (level == 0) firstStalactiteLevel = 0;
	else {
		int numStalactite = 0;
		for (int p = 0; p < level; ++p) numStalactite += stalactitesPerScreen[p];
		firstStalactiteLevel = numStalactite;
	}
	maxSkullLevel = firstSkullLevel + skullsPerScreen[level];
	maxKeyLevel = firstKeyLevel + keysPerScreen[level];
	maxPadlockLevel = firstPadlockLevel + padlocksPerScreen[level];
	maxDoorLevel = firstDoorLevel + doorPerScreen[level];
	maxObjectLevel = firstObjectLevel + objectesPerScreen[level];
	maxPowerUpLevel = firstPowerUpLevel + powerUpsPerScreen[level];
	maxWaterDropLevel = firstWaterDropLevel + waterDropsPerScreen[level];
	maxStalactiteLevel = firstStalactiteLevel + stalactitesPerScreen[level];
	_RPT1(0, "New firstSkullLevel = %d\n", firstSkullLevel);
	_RPT1(0, "New maxSkullLevel = %d\n", maxSkullLevel);
	updateScene(true);
	return level;
}

int Scene::addPoints(int points)
{
	punts += points;
	return punts;
}

int Scene::modifyHP(int healthPoints) {
	health += healthPoints;
	if (health > 20) health = 20;
	return health;
}

int Scene::modifyExp(int expPoints) {
	exp += expPoints;
	if (exp >= 20) {
		exp = exp % 20;
		modifyHP(4);
	}
	return exp;
}

int Scene::addGoonies() {
	++gooniesRescued;
	addPoints(2000);
	return gooniesRescued;
}

bool Scene::noHealth() {
	if (health <= 0) return true;
	else return false;
}

bool Scene::addKey() {
	addPoints(200);
	key = true;
	return key;
}

bool Scene::removeKey() {
	key = false;
	return key;
}

bool Scene::keyStatus() {
	return key;
}

bool Scene::portalStatus() {
	if (player->portalStatus()) return true;
	else return false;

}

void Scene::powerupHelmet() {
	player->powerupHelmet();
	Helmet = true;
}

void Scene::powerupBlueSpellbook() {
	player->powerupBlueSpellbook();
	BlueSpellbook = true;
}

void Scene::powerupGrayRaincoat() {
	player->powerupGrayRaincoat();
	GrayRaincoat = true;
}

void Scene::powerupHyperShoes() {
	player->powerupHyperShoes();
	HyperShoes = true;
}

void Scene::powerupYellowRaincoat() {
	player->powerupYellowRaincoat();
	YellowRaincoat = true;
}

void Scene::godMode() {
	player->godMode();
	god = true;
}

void Scene::updateScene(bool portal)
{

	switch (level)
	{
	case(0):
		map = TileMap::createTileMap("levels/msx.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(1):
		map = TileMap::createTileMap("levels/FonsBlau.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(2):
		map = TileMap::createTileMap("levels/LoadingScreen2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(3):
		map = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(4):
		map = TileMap::createTileMap("levels/Scene2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(5):
		map = TileMap::createTileMap("levels/Scene3.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(6):
		map = TileMap::createTileMap("levels/Scene4.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(7):
		map = TileMap::createTileMap("levels/Scene5.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(8):
		map = TileMap::createTileMap("levels/Scene6.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(9):
		map = TileMap::createTileMap("levels/Scene7.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(10):
		map = TileMap::createTileMap("levels/Scene8.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(11):
		map = TileMap::createTileMap("levels/Scene9.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(12):
		map = TileMap::createTileMap("levels/Scene10.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(13):
		map = TileMap::createTileMap("levels/Scene11.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(14):
		map = TileMap::createTileMap("levels/Scene12.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(15):
		map = TileMap::createTileMap("levels/Scene13.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(16):
		map = TileMap::createTileMap("levels/Scene14.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case(17):
		map = TileMap::createTileMap("levels/Scene15.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	default:
		break;
	}
	if (level >= 3) {
		player->setTileMap(map);
		 
		for (int i = firstSkullLevel; i < maxSkullLevel; ++i) {
			skullsScene[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			skullsScene[i].setPosition(glm::vec2(initSkullsPos[i][0] * map->getTileSize(), initSkullsPos[i][1] * map->getTileSize()));
			skullsScene[i].setTileMap(map);
		}

		for (int j = firstKeyLevel; j < maxKeyLevel; ++j) {
			if (initKeysPos[j][2] == 1) {
				keyScene[j].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				keyScene[j].setPosition(glm::vec2(initKeysPos[j][0] * map->getTileSize(), initKeysPos[j][1] * map->getTileSize()));
				keyScene[j].setTileMap(map);
			}
		}
		for (int k = firstPadlockLevel; k < maxPadlockLevel; ++k) {
			if (initPadlocksPos[k][2] == 1) {
				padlockScene[k].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				padlockScene[k].setPosition(glm::vec2(initPadlocksPos[k][0] * map->getTileSize(), initPadlocksPos[k][1] * map->getTileSize()));
				padlockScene[k].setTileMap(map);
			}
		}

		for (int l = firstDoorLevel; l < maxDoorLevel; ++l) {
			if (DoorPos[l][2] == 1) {
				doorScene[l].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				doorScene[l].setPosition(glm::vec2(DoorPos[l][0] * map->getTileSize(), DoorPos[l][1] * map->getTileSize()));
				doorScene[l].setTileMap(map);
			}
		}
		for (int m = firstObjectLevel; m < maxObjectLevel; ++m) {
			if (objectPos[m][2] == 1) {
				objectesScene[m].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				objectesScene[m].setPosition(glm::vec2(objectPos[m][0] * map->getTileSize(), objectPos[m][1] * map->getTileSize()));
				objectesScene[m].setTileMap(map);
				if (DoorPos[m][2] == 0) objectesScene[m].appear();
			}
		}
		for (int n = firstPowerUpLevel; n < maxPowerUpLevel; ++n) {
			if (powerupsPos[n][2] == 1) {
				powerupsScene[n].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				powerupsScene[n].setPosition(glm::vec2(powerupsPos[n][0] * map->getTileSize(), powerupsPos[n][1] * map->getTileSize()));
				powerupsScene[n].setTileMap(map);
				if (!powerupsScene[n].catched()) powerupsScene[n].appear();
			}
		}
		for (int o = firstWaterDropLevel; o < maxWaterDropLevel; ++o) {
			waterdropScene[o].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			waterdropScene[o].setPosition(glm::vec2(initwaterdropsPos[o][0] * map->getTileSize() + 2, initwaterdropsPos[o][1] * map->getTileSize()));
			waterdropScene[o].setTileMap(map);
		}

		for (int p = firstStalactiteLevel; p < maxStalactiteLevel; ++p) {
			if (initStalactitesPos[p][2] == 1) {
				stalactitesScene[p].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				stalactitesScene[p].setPosition(glm::vec2(initStalactitesPos[p][0] * map->getTileSize(), initStalactitesPos[p][1] * map->getTileSize()));
				stalactitesScene[p].setTileMap(map);
			}
		}

		if (portal && (level == 3 || level == 6 || level == 12 || level == 15)) {
			enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			enemy->setLevelEnemy(level);
			glm::ivec2 newEnemyPos;
			int array_pos = level / 3 - 1;
			if (level > 6) --array_pos;
			enemy->setPosition(glm::vec2(enemyPositions[array_pos][0] * map->getTileSize(), enemyPositions[array_pos][1] * map->getTileSize()));
		}

		int enemyLevel = enemy->getLevelEnemy();
		setEnemyMap(enemyLevel);
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::colision_with_enemies(bool attack_side, int& num_enemy, int attack_dist, bool& hit_side)
{
	int x_left = 0;
	int x_right = 0;
	if (attack_side) x_left = attack_dist;
	else x_right = attack_dist;
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstSkullLevel; i < maxSkullLevel; ++i) {
		glm::ivec2 SkullPos = skullsScene[i].getPosition();
		num_enemy = i;
		if (skullsScene[i].isAlive()) {
			if (PlayerPos.y >(SkullPos.y - 32) && PlayerPos.y < (SkullPos.y + 16)) {
				if (PlayerPos.x >(SkullPos.x - (16 + x_right)) && PlayerPos.x < (SkullPos.x + (16 + x_left))) {
					hit_side = SkullPos.x < PlayerPos.x;
					return true;
				}
			}
		}
	}
	int enemy_level = enemy->getLevelEnemy();
	if (level == enemy_level) {
		glm::ivec2 posEnemy = enemy->getPosition();
		if (!enemy->is_Stun()) {
			if (PlayerPos.y >(posEnemy.y - 16) && PlayerPos.y < (posEnemy.y + 32)) {
				if (PlayerPos.x >(posEnemy.x - (16 + x_right)) && PlayerPos.x < (posEnemy.x + (16 + x_left))) {
					hit_side = posEnemy.x < PlayerPos.x;
					num_enemy = 21;
					return true;
				}
			}
		}
	}

	glm::ivec2 posBullet = bullet->getPosition();
	if (bullet->is_Alive()) {
		if (PlayerPos.y > (posBullet.y - 16) && PlayerPos.y < (posBullet.y + 32)) {
			if (PlayerPos.x > (posBullet.x - (16 + x_right)) && PlayerPos.x < (posBullet.x + (16 + x_left))) {
				num_enemy = 22;
				return true;
			}
		}
	}

	return false;
}

glm::ivec2 Scene::getPlayerPosition()
{
	glm::ivec2 playerPos = player->getPosition();
	int enemyLevel = enemy->getLevelEnemy();
	if (level != enemyLevel) {
		if (level > enemyLevel) {
			if ((level >= 3 && level <= 5) || (level >= 9 && level <= 11)) playerPos.x = 1000;
			else if ((level >= 6 && level <= 8) || (level >= 15 && level <= 17)) playerPos.y = 1000;
			else if (level >= 12 && level <= 14) {
				if (enemyLevel == 12) playerPos.y = 1000;
				else if (enemyLevel == 13) playerPos.x = 1000;
			}
		}
		else if (level < enemyLevel) {
			if ((level >= 3 && level <= 5) || (level >= 9 && level <= 11)) playerPos.x = 0;
			else if ((level >= 6 && level <= 8) || (level >= 15 && level <= 17)) playerPos.y = 0;
			else if (level >= 12 && level <= 14) {
				if (enemyLevel == 13) playerPos.y = 0;
				else if (enemyLevel == 14) playerPos.x = 0;
			}
		}
	}
	return playerPos;
}

void Scene::setEnemyMap(int enemy_level) {
	switch (enemy_level)
	{
	case(0):
		map_enemy = TileMap::createTileMap("levels/msx.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(1):
		map_enemy = TileMap::createTileMap("levels/FonsBlau.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(2):
		map_enemy = TileMap::createTileMap("levels/LoadingScreen2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(3):
		map_enemy = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(4):
		map_enemy = TileMap::createTileMap("levels/Scene2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(5):
		map_enemy = TileMap::createTileMap("levels/Scene3.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(6):
		map_enemy = TileMap::createTileMap("levels/Scene4.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(7):
		map_enemy = TileMap::createTileMap("levels/Scene5.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(8):
		map_enemy = TileMap::createTileMap("levels/Scene6.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(9):
		map_enemy = TileMap::createTileMap("levels/Scene7.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(10):
		map_enemy = TileMap::createTileMap("levels/Scene8.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(11):
		map_enemy = TileMap::createTileMap("levels/Scene9.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(12):
		map_enemy = TileMap::createTileMap("levels/Scene10.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(13):
		map_enemy = TileMap::createTileMap("levels/Scene11.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(14):
		map_enemy = TileMap::createTileMap("levels/Scene12.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(15):
		map_enemy = TileMap::createTileMap("levels/Scene13.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(16):
		map_enemy = TileMap::createTileMap("levels/Scene14.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	case(17):
		map_enemy = TileMap::createTileMap("levels/Scene15.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	default:
		map_enemy = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram2);
		break;
	}
	enemy->setTileMap(map_enemy);
}

bool Scene::collision_with_keys()
{
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstKeyLevel; i < maxKeyLevel; ++i) {
		glm::ivec2 KeyPos = keyScene[i].getPosition();
		int keys = i;
		if (keyScene[i].isAlive()) {
			if ((PlayerPos.x >= KeyPos.x - 16 && PlayerPos.x <= KeyPos.x + 16) && (PlayerPos.y >= KeyPos.y - 16 && PlayerPos.y <= KeyPos.y + 16)) {
				initKeysPos[i][2] = 0;
				keyScene[i].collect();
				switch (i) {
				case 0:
					powerupsScene[0].appear();
					powerupsPos[0][2] = 0;
					break;
				case 3:
					powerupsScene[1].appear();
					powerupsPos[1][2] = 0;
					break;
				case 6:
					powerupsScene[2].appear();
					powerupsPos[2][2] = 0;
					break;
				case 7:
					powerupsScene[3].appear();
					powerupsPos[3][2] = 0;
					break;
				case 10:
					powerupsScene[4].appear();
					powerupsPos[4][2] = 0;
					break;
				default:
					break;
				}
				return true;
			}
		}
	}
	return false;
}

bool Scene::collision_with_padlocks()
{
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstPadlockLevel; i < maxPadlockLevel; ++i) {
		glm::ivec2 PadlockPos = padlockScene[i].getPosition();
		int padlock = i;
		int numDoor = 0;
		for (int j = 0; j < level; ++j) {
			numDoor += doorPerScreen[j];
		}
		int numpadlock = padlocksPerScreen[level];
		if (padlockScene[i].isAlive() && Game::instance().keyStatus()) {
			if ((PlayerPos.x >= PadlockPos.x - 8 && PlayerPos.x <= PadlockPos.x + 8) && (PlayerPos.y >= PadlockPos.y - 16 && PlayerPos.y <= PadlockPos.y + 16)) {
				initPadlocksPos[i][2] = 0;
				padlockScene[i].collect();
				if (numpadlock == 2) {
					if (initPadlocksPos[firstPadlockLevel][2] == 0 && initPadlocksPos[maxPadlockLevel - 1][2] == 0)
					{
						doorScene[numDoor].open();
						objectesScene[numDoor].appear();
						DoorPos[numDoor][2] = 0;
					}
				}
				else if (initPadlocksPos[i][2] == 0) {
					doorScene[numDoor].open();
					objectesScene[numDoor].appear();
					DoorPos[numDoor][2] = 0;
				}
				return true;
			}
		}
	}
	return false;
}

bool Scene::collision_with_objects_door()
{
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstObjectLevel; i < maxObjectLevel; ++i) {
		glm::ivec2 PosObjecte = objectesScene[i].getPosition();
		if (objectesScene[i].isAlive()) {
			if ((PlayerPos.x >= PosObjecte.x - 16 && PlayerPos.x <= PosObjecte.x + 16) && (PlayerPos.y >= PosObjecte.y - 16 && PlayerPos.y <= PosObjecte.y + 16)) {
				objectPos[i][2] = 0;
				objectesScene[i].rescue();
				return true;
			}
		}
	}
	return false;
}

bool Scene::collision_with_powerups()
{
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstPowerUpLevel; i < maxPowerUpLevel; ++i) {
		glm::ivec2 PosObjecte = powerupsScene[i].getPosition();
		if (powerupsScene[i].isAlive()) {
			if ((PlayerPos.x >= PosObjecte.x - 16 && PlayerPos.x <= PosObjecte.x + 16) && (PlayerPos.y >= PosObjecte.y - 16 && PlayerPos.y <= PosObjecte.y + 16)) {
				powerupsPos[i][2] = 0;
				powerupsScene[i].collect(i);
				return true;
			}
		}
	}
	return false;
}

bool Scene::collision_with_waterdrops()
{
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstWaterDropLevel; i < maxWaterDropLevel; ++i) {
		glm::ivec2 WaterDropPos = waterdropScene[i].getPosition();
		if (waterdropScene[i].isAlive()) {
			if ((PlayerPos.x >= WaterDropPos.x - 16 && PlayerPos.x <= WaterDropPos.x) && (PlayerPos.y >= WaterDropPos.y - 12 && PlayerPos.y <= WaterDropPos.y + 12)) {
				waterdropScene[i].collision();
				player->got_hit_by_water();
				return true;
			}
		}
	}
	return false;
}

bool Scene::collision_with_steam()
{
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = 0; i < 6; ++i) {
		if (steam[i].isDangerous()) {
			if ((PlayerPos.x >= steamPos[i][0] * 16 - 16 && PlayerPos.x <= steamPos[i][0] * 16 + 16) && (PlayerPos.y >= steamPos[i][1] * 16 - 16 && PlayerPos.y <= steamPos[i][1] * 16 + 16)) {
				player->got_hit_by_steam();
				return true;
			}
		}
	}
	return false;
}

void Scene::activateStalactites() {
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstStalactiteLevel; i < maxStalactiteLevel; ++i) {
		glm::ivec2 StalactitePos = stalactitesScene[i].getPosition();
		if ((PlayerPos.x >= StalactitePos.x - 16 && PlayerPos.x <= StalactitePos.x + 16) && map->noHiHaTerra(PlayerPos, StalactitePos)) {
			stalactitesScene[i].activate();
			initStalactitesPos[i][2] = 0;
		}
	}
}

bool Scene::collision_with_stalactites() {
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = firstStalactiteLevel; i < maxStalactiteLevel; ++i) {
		glm::ivec2 StalactitePos = stalactitesScene[i].getPosition();
		if (stalactitesScene[i].isDangerous()) {
			if ((PlayerPos.x >= StalactitePos.x - 12 && PlayerPos.x <= StalactitePos.x + 12) && (PlayerPos.y >= StalactitePos.y && PlayerPos.y <= StalactitePos.y)) {
				player->got_hit_by_stalactite();
				return true;
			}
		}
	}
	return false;
}
