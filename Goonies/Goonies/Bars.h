#pragma once
#ifndef _BARS_INCLUDE
#define _BARS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class Bars
{

public:
	void initHealthBar(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void initExpBar(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int health);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	int puntuacio;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif
