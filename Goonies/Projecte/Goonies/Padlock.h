#pragma once
#ifndef _PADLOCK_INCLUDE
#define _PADLOCK_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class Padlock
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
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
