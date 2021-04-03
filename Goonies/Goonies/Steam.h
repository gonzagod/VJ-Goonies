#pragma once
#ifndef _STEAM_INCLUDE
#define _STEAM_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class Steam
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int x);
	void render();

	bool isDangerous();
	glm::ivec2 getPosition();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	int cont, estat;
	bool alive;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif
