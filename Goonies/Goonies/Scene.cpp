#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <crtdbg.h> 


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 12.5
#define INIT_PLAYER_Y_TILES 8

#define INIT_SKULL_X_TILES 19
#define INIT_SKULL_Y_TILES 14

#define GOONIE_INIT_X_TILES -10
#define GOONIE_INIT_Y_TILES 10

#define GOON_INIT_X_TILES 8
#define GOON_INIT_Y_TILES 10

#define KONAMI_INIT_X_TILES 12
#define KONAMI_INIT_Y_TILES 14


Scene::Scene()
{
	map = NULL;
	player = NULL;
	skull1 = NULL;
	level = 1;
	estat = 1;
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
	map = TileMap::createTileMap("levels/FonsBlau.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	skull1 = new Skull();
	skull1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	skull1->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	skull1->setTileMap(map);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()-8));
	player->setTileMap(map);

	goon = new pjLoadingScreen();
	goon->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goon->setPosition(glm::vec2(GOON_INIT_X_TILES * map->getTileSize(), GOON_INIT_Y_TILES * map->getTileSize()));
	goon->setTileMap(map);

	goonie1 = new pjLoadingScreen();
	goonie1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie1->setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
	goonie1->setTileMap(map);

	goonie2 = new pjLoadingScreen();
	goonie2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie2->setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
	goonie2->setTileMap(map);

	goonie3 = new pjLoadingScreen();
	goonie3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie3->setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
	goonie3->setTileMap(map);

	goonie4 = new pjLoadingScreen();
	goonie4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie4->setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
	goonie4->setTileMap(map);

	goonie5 = new pjLoadingScreen();
	goonie5->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie5->setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
	goonie5->setTileMap(map);

	goonie6 = new pjLoadingScreen();
	goonie6->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie6->setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
	goonie6->setTileMap(map);


	evil = new pjLoadingScreen();
	evil->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	evil->setPosition(glm::vec2(GOONIE_INIT_X_TILES * map->getTileSize(), GOONIE_INIT_Y_TILES * map->getTileSize()));
	evil->setTileMap(map);

	konami = new pjLoadingScreen();
	konami->initKonami(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	konami->setPosition(glm::vec2(KONAMI_INIT_X_TILES * map->getTileSize(), KONAMI_INIT_Y_TILES * map->getTileSize()));


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
	switch (level) {
	case(0):

		break;
	case(1):
		konami->update(deltaTime,0,estat);
		break;
	case(2):
		goon->update(deltaTime, 1, estat);
		goonie1->update(deltaTime, 2, estat);
		goonie2->update(deltaTime, 3, estat);
		goonie3->update(deltaTime, 4, estat);
		goonie4->update(deltaTime, 5, estat);
		goonie5->update(deltaTime, 6, estat);
		goonie6->update(deltaTime, 7, estat);
		evil->update(deltaTime, 8, estat);
		break;
	case(3):
		skull1->update(deltaTime);
		break;
	case(4):
		break;
	case(5):
		break;
	default:
		break;
	}
	if (level >= 3) player->update(deltaTime);
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
			
			break;
		case(1):
			konami->render();
			break;
		case(2):
			goon->render();
			goonie1->render();
			goonie2->render();
			goonie3->render();
			goonie4->render();
			goonie5->render();
			goonie6->render();
			evil->render();
			break;
		case(3):
			skull1->render();
			break;
		case(4):
			break;
		case(5):
			break;
		default:
			break;
	}
	if (level >= 3) player->render();
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
		case(0):
			map = TileMap::createTileMap("levels/msx.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		case(1):
			map = TileMap::createTileMap("levels/FonsBlau.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		case(2):
			map = TileMap::createTileMap("levels/LoadingScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		case(3):
			map = TileMap::createTileMap("levels/Scene1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		case(4):
			map = TileMap::createTileMap("levels/Scene2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		default:
			break;
	}
	if (level >=3) player->setTileMap(map);
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



