#ifndef _SKULL_INCLUDE
#define _SKULL_INCLUDE

#include "Sprite.h"
#include "TileMap.h"




class Skull
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	void die();
	bool isAlive();
	bool isReady();
	void setFirstMove(bool side);
	void setJumper(bool jump);
	void setDistance(int min, int max);

private:
	glm::ivec2 tileMapDispl, posSkull;
	int startX, startY, max_x, min_x;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool alive, dying, ready, first_move, jumper;
	int cont_spawn, cont_dying, jumping_cont;
};

#endif