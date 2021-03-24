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

#define INIT_MSX_X_TILES -7
#define INIT_MSX2_X_TILES 23
#define INIT_MSX_Y_TILES 0

#define INIT_SKULL_X_TILES 19
#define INIT_SKULL_Y_TILES 14

#define GOONIE_INIT_X_TILES -10
#define GOONIE_INIT_Y_TILES 10

#define GOON_INIT_X_TILES 8
#define GOON_INIT_Y_TILES 10

#define KONAMI_INIT_X_TILES 12
#define KONAMI_INIT_Y_TILES 14

#define LLETRES_INIT_X_TILES -20
#define LLETRES_INIT_Y_TILES -20


Scene::Scene()
{
	map = NULL;
	player = NULL;
	skull1 = NULL;
	level = 0;
	estat = 0;
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

	lletres = new pjLoadingScreen();
	lletres->initLletres(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	lletres->setPosition(glm::vec2(LLETRES_INIT_X_TILES * map->getTileSize(), LLETRES_INIT_Y_TILES * map->getTileSize()));


	playStart = new pjLoadingScreen();
	playStart->initPlayStart(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	playStart->setPosition(glm::vec2(LLETRES_INIT_X_TILES * map->getTileSize(), LLETRES_INIT_Y_TILES * map->getTileSize()));


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
	if (level <= 2 && Game::instance().getKey(32)) {
		estat = 22;
		level = 2;
	}
	switch (level) {
	case(0):
		msx->update(deltaTime, 0, estat);
		msx2->update(deltaTime, 1, estat);
		lletres->update(deltaTime, 11, estat);
		break;
	case(1):
		konami->update(deltaTime,2,estat);
		break;
	case(2):
		if (estat == 5) 			map = TileMap::createTileMap("levels/LoadingScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		if (estat == 22)			map = TileMap::createTileMap("levels/LoadingScreen2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		if (estat >= 4) goon->update(deltaTime, 3, estat);
		if (estat >= 6 && estat <= 14) goonie1->update(deltaTime, 4, estat);
		if (estat >= 7 && estat <= 15) goonie2->update(deltaTime, 5, estat);
		if (estat >= 8 && estat <= 16) goonie3->update(deltaTime, 6, estat);
		if (estat >= 9 && estat <= 17) goonie4->update(deltaTime, 7, estat);
		if (estat >= 10 && estat <= 18) goonie5->update(deltaTime, 8, estat);
		if (estat >= 11 && estat <= 19) goonie6->update(deltaTime, 9, estat);
		if (estat >= 12 && estat <= 21) evil->update(deltaTime, 10, estat);
		if (estat == 22 || estat == 23) playStart->update(deltaTime,12,estat);
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
			msx->render();
			msx2->render();
			lletres->render();
			break;
		case(1):
			konami->render();
			break;
		case(2):
			if (estat >= 5 && estat <= 21) goon->render();
			if (estat >= 6 && estat <= 14) goonie1->render();
			if (estat >= 7 && estat <= 15) goonie2->render();
			if (estat >= 8 && estat <= 16) goonie3->render();
			if (estat >= 9 && estat <= 17) goonie4->render();
			if (estat >= 10 && estat <= 18) goonie5->render();
			if (estat >= 11 && estat <= 19) goonie6->render();
			if (estat >= 12 && estat <= 21) evil->render();
			if (estat == 22 || estat == 23) playStart->render();
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
			map = TileMap::createTileMap("levels/LoadingScreen2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
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



