#ifndef _PJLOADINGSCREEN_INCLUDE
#define _PJLOADINGSCREEN_INCLUDE

#include "Sprite.h"
#include "TileMap.h"




class pjLoadingScreen
{

public:
	void initGoonie(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void initGoon(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void initEvil(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif#pragma once
