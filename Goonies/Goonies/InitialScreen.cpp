#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "InitialScreen.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 12
#define INIT_PLAYER_Y_TILES 8

#define INIT_SKULL_X_TILES 19
#define INIT_SKULL_Y_TILES 14


InitialScreen::InitialScreen()
{
	map = NULL;
	goon = NULL;
	goonie1 = NULL;
	goonie2 = NULL;
	goonie3 = NULL;
	goonie4 = NULL;
	goonie5 = NULL;
	goonie6 = NULL;
	evil = NULL;
}

InitialScreen::~InitialScreen()
{
	if (map != NULL)
		delete map;
	if (goon != NULL)
		delete goon;
	if (goonie1 != NULL)
		delete goonie1;
	if (goonie2 != NULL)
		delete goonie2;
	if (goonie3 != NULL)
		delete goonie3;
	if (goonie4 != NULL)
		delete goonie4;
	if (goonie5 != NULL)
		delete goonie5;
	if (goonie6 != NULL)
		delete goonie6;
	if (evil != NULL)
		delete evil;
}


void InitialScreen::init()
{
	initShaders();

	map = TileMap::createTileMap("levels/LoadingScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	goon = new pjLoadingScreen();
	goon->initGoon(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goon->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	goon->setTileMap(map);

	goonie1 = new pjLoadingScreen();
	goonie1->initGoonie(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie1->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	goonie1->setTileMap(map);

	goonie2 = new pjLoadingScreen();
	goonie2->initGoonie(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie2->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	goonie2->setTileMap(map);

	goonie3 = new pjLoadingScreen();
	goonie3->initGoonie(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie3->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	goonie3->setTileMap(map);

	goonie4 = new pjLoadingScreen();
	goonie4->initGoonie(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie4->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	goonie4->setTileMap(map);

	goonie5 = new pjLoadingScreen();
	goonie5->initGoonie(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie5->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	goonie5->setTileMap(map);

	goonie6 = new pjLoadingScreen();
	goonie6->initGoonie(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	goonie6->setPosition(glm::vec2(INIT_SKULL_X_TILES * map->getTileSize(), INIT_SKULL_Y_TILES * map->getTileSize()));
	goonie6->setTileMap(map);


	evil = new pjLoadingScreen();
	evil->initEvil(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	evil->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	evil->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void InitialScreen::update(int deltaTime)
{
	currentTime += deltaTime;
	if (Game::instance().getKey(49)) {
		level = 1;
	}
	if (Game::instance().getKey(49)) {
		level = 2;
	}
	goon->update(deltaTime);
	goonie1->update(deltaTime);
	goonie2->update(deltaTime);
	goonie3->update(deltaTime);
	goonie4->update(deltaTime);
	goonie5->update(deltaTime);
	goonie6->update(deltaTime);
	evil->update(deltaTime);
}

void InitialScreen::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	goon->render();
	goonie1->render();
	goonie2->render();
	goonie3->render();
	goonie4->render();
	goonie5->render();
	goonie6->render();
	evil->render();
}

void InitialScreen::initShaders()
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



