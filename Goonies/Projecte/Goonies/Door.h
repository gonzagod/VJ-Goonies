#pragma once
#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class Door
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int x);
	void render();

	void open();
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

