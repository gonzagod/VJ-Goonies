#pragma once
#ifndef _PUNTUACIO_INCLUDE
#define _PUNTUACIO_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class Puntuacio
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int numPersonatge, int points, int level);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	int puntuacio;
	int puntuacioMaxima;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif
