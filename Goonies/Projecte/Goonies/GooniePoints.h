#pragma once
#ifndef _GOONIEPOINTS_INCLUDE
#define _GOONIEPOINTS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class GooniePoints
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int gooniePoints);
	void render();

	void collect();
	bool isAlive();
	glm::ivec2 getPosition();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	bool alive;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif