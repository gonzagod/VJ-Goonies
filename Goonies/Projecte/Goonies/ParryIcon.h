#pragma once
#ifndef _PARRYICON_INCLUDE
#define _PARRYICON_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class ParryIcon
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int x);
	void render();

	bool isAlive();
	glm::ivec2 getPosition();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void bullet(bool b);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	bool alive, bullet_icon;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif
