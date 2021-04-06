#pragma once
#ifndef _POWERUPS_INCLUDE
#define _POWERUPS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class PowerUps
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void collect(int x);
	bool isAlive();
	bool catched();
	void appear();
	glm::ivec2 getPosition();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	bool alive;
	bool visible;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif

