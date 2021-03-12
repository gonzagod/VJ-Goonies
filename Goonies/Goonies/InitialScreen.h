#pragma once
#ifndef _INITIALSCREEN_INCLUDE
#define _INITIALSCREEN_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "pjLoadingScreen.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class InitialScreen
{

public:
	InitialScreen();
	~InitialScreen();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	pjLoadingScreen *goonie1;
	pjLoadingScreen *goonie2;
	pjLoadingScreen *goonie3;
	pjLoadingScreen *goonie4;
	pjLoadingScreen *goonie5;
	pjLoadingScreen *goonie6;
	pjLoadingScreen *goon;
	pjLoadingScreen *evil;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int level = 1;
	string levelmap;

};


#endif // _SCENE_INCLUDE

