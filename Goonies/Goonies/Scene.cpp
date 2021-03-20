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
	skull1 = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (skull1 != NULL)
		delete skull1;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	skull1 = new Skull();
	skull1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	skull1->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	skull1->setTileMap(map);

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
	skull1->update(deltaTime);
	player->update(deltaTime);
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
			skull1->render();
			break;
		case(2):
			break;
		default:
			break;
	}
}

int Scene::nextScreen()
{
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



