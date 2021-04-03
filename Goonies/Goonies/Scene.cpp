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

static const int num_skulls_Scene = 21;
Skull* skullsScene = new Skull[num_skulls_Scene];
int skullsPerScreen[18] = { 0,0,0,1,2,3,0,2,2,1,0,1,0,2,1,2,2,2 };
int initSkullsPos[num_skulls_Scene][2] = { { 24,17 },{ 10,11 },{ 26,7  },{ 23,7  },{ 25,13 },{ 17,17 },
										   { 18,9  },{ 18,19 },{ 16,5  },{ 26,11 },
										   {  8,5  },{ 20,17 },
										   { 10,13 },{ 14,19 },{ 25,19 },
										   { 22,15 },{  6,17 },{ 17,11 },{ 20,17 },{  8,9 },{ 11,21 } };
int enemyPositions[4][2] = { {34,11}, {10,11}, {22,9}, {24,11} };

Scene::Scene()
{
	map = NULL;
	player = NULL;
	// skull1 = NULL;
	level = 0;
	estat = 0;
	health = 20;
	exp = 0;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	/*if (skull1 != NULL)
	delete skull1;*/
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

	healthBar = new Bars();
	healthBar->initHealthBar(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	healthBar->setPosition(glm::vec2(HEALTHBAR_INIT_X_TILES * map->getTileSize(), HEALTHBAR_INIT_Y_TILES * map->getTileSize()));
	healthBar->setTileMap(map);

	expBar = new Bars();
	expBar->initExpBar(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	expBar->setPosition(glm::vec2(EXPBAR_INIT_X_TILES * map->getTileSize(), EXPBAR_INIT_Y_TILES * map->getTileSize()));
	expBar->setTileMap(map);

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
	int i = goToScreen(3);
}

void Scene::restartGame() {
	level = 3;
	health = 20;
	exp = 0;
	punts = 0;
	init();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (punts > maxPunts) maxPunts = punts;
	if ((level > 0 && level <= 2) && Game::instance().getKey(32)) {
	estat = 22;
	level = 2;
	}
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
		for (int i = firstSkullLevel; i < maxSkullLevel; ++i) {
			skullsScene[i].update(deltaTime);
		}

		break;
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
	default:
		break;
	}
	if (level >= 3) {
		for (int i = 0; i < 14; ++i) {
			puntuation[i].render();
		}
		healthBar->render();
		expBar->render();
		player->render();
		int enemyLevel = enemy->getLevelEnemy();
		if(enemyLevel == level && enemy->is_Alive()) enemy->render();
		if (bullet->is_Alive()) bullet->render();

		for (int i = firstSkullLevel; i < maxSkullLevel; ++i) {
			skullsScene[i].render();
		}
	}
}

int Scene::nextScreen()
{
	++level;
	firstSkullLevel = maxSkullLevel;
	maxSkullLevel += skullsPerScreen[level];
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
	}
	maxSkullLevel = firstSkullLevel + skullsPerScreen[level];
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

bool Scene::noHealth() {
	if (health <= 0) return true;
	else return false;
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