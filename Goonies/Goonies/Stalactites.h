#pragma once
#ifndef _STALACTITES_INCLUDE
#define _STALACTITES_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class Stalactites
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int x);
	void render();

	void activate();
	bool isDangerous();
	glm::ivec2 getPosition();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	bool alive;
	bool activated;
	int cont;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif

