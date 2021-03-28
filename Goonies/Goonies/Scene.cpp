#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 12.5
#define INIT_PLAYER_Y_TILES 8

#define INIT_SKULL_X_TILES 19
#define INIT_SKULL_Y_TILES 14


Scene::Scene()
{
	map = NULL;
	player = NULL;
	//skullsScene1[0] = NULL;
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
	map = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	firstSkulli = 0;
	//skullsScene1[0] = new Skull();
	skullsScene1[0].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	skullsScene1[0].setPosition(glm::vec2(initSkullsPos[0][0] * map->getTileSize(), initSkullsPos[0][1] * map->getTileSize()));
	skullsScene1[0].setTileMap(map);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()-8));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (Game::instance().getKey(49)) {
		map = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	}
	if (Game::instance().getKey(50)) {
		map = TileMap::createTileMap("levels/Scene2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	}
	int maxSkullToRender = 0;
	for (int i = 0; i < level; ++i) {
		maxSkullToRender += skullsPerScreen1[i];
	}
	for (int i = 0; i < maxSkullToRender; ++i) {
		skullsScene1[i].update(deltaTime);
	}

	player->update(deltaTime);
	bool attack_side = true; //True = LEFT ||False = Right
	int enemy = 0;
	bool player_attacking = player->isAttacking(attack_side);
	bool hit = false;
	bool hit_side = true; //True = LEFT ||False = Right
	if (player_attacking) {
		_RPT1(0, "attack_side = %d\n", attack_side);
		hit = colision_with_enemies(attack_side, enemy, 8, hit_side);
	}
	else hit = colision_with_enemies(attack_side, enemy, 0, hit_side);
	if (hit) {
		if (player_attacking && attack_side == hit_side) {
			skullsScene1[enemy].die();
		}
		else {
			bool enemy_hit = player->got_hit();
			_RPT2(0, "enemy_hit = %d , side = %d\n", enemy_hit, hit_side);
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
	player->render();
	
	switch (level)
	{
		case(1):
			skullsScene1[0].render();
			break;
		default:
			for (int i = 1; i < skullsPerScreen1[level - 1] +1; ++i) {
				skullsScene1[i].render();
			}
			break;
	}
}

int Scene::nextScreen()
{
	firstSkulli += skullsPerScreen1[level - 1];
	++level;
	updateScene();
	return level;
}

int Scene::prevScreen()
{
	--level;
	updateScene();
	return level;
}


void Scene::updateScene()
{
	switch (level)
	{
		case(1):
			map = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		case(2):
			map = TileMap::createTileMap("levels/Scene2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			for (int i = 1; i < skullsPerScreen1[level - 1] + 1; ++i) {
				skullsScene1[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				skullsScene1[i].setPosition(glm::vec2(initSkullsPos[i][0] * map->getTileSize(), initSkullsPos[i][1] * map->getTileSize()));
				skullsScene1[i].setTileMap(map);
			}
			break;
		default:
			break;
	}
	player->setTileMap(map);
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

bool Scene::colision_with_enemies(bool attack_side, int& enemy, int attack_dist, bool& hit_side)
{
	int x_left = 0;
	int x_right = 0;
	if (attack_side) x_left = attack_dist;
	else x_right = attack_dist;
	glm::ivec2 PlayerPos = player->getPosition();
	for (int i = 0; i < skullsPerScreen1[level - 1]; ++i) {
		glm::ivec2 SkullPos = skullsScene1[firstSkulli + i].getPosition();
		enemy = firstSkulli + i;
		if (skullsScene1[firstSkulli + i].isAlive()) {
			if (PlayerPos.y > (SkullPos.y - 32) && PlayerPos.y < (SkullPos.y + 16)) {
				if (PlayerPos.x > (SkullPos.x - (16+x_right)) && PlayerPos.x < (SkullPos.x + (16+x_left))) {
					hit_side = SkullPos.x < PlayerPos.x;
					return true;
				}
			}
		}
	}
	return false;
}



