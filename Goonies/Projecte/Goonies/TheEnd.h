#pragma once
#ifndef _THEEND_INCLUDE
#define _THEEND_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class TheEnd
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

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

