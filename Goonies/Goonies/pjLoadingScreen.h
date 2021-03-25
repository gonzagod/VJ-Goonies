#ifndef _PJLOADINGSCREEN_INCLUDE
#define _PJLOADINGSCREEN_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <time.h>




class pjLoadingScreen
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void initKonami(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void initMsx(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void initLletres(const glm::ivec2&tileMapPos, ShaderProgram& shaderProgram);
	void initPlayStart(const glm::ivec2&tileMapsPos, ShaderProgram& shaderProgram);
	void update(int deltaTime,int numPersonatge,int &estat);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPJ;
	int startX, startY;
	int cont;
	bool moved;
	bool waiting = false;
	bool alive;
	clock_t endwait;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif#pragma once
