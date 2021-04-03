#pragma once
#ifndef _WATERDROP_INCLUDE
#define _WATERDROP_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class WaterDrop
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void collision();
	bool isAlive();
	glm::ivec2 getPosition();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	glm::ivec2 posStart;
	int startX, startY;
	bool alive;
	int estat;
	int cont;
	int y;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif

