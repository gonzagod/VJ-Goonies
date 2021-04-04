#ifndef _CASCADE_INCLUDE
#define _CASCADE_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Cascade
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	bool is_Alive();
	void player_hit();
	void setMax_y(int y);
	void setSub_y(int y);
	void isFirst();
	void setSize(int m);

private:
	bool alive, change, first;
	int max_y, cont_falling, cont_waiting, sub_y, max_waiting, cont, size, time_cascade, init_y;
	glm::ivec2 tileMapDispl, posCascade;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif // _CASCADE_INCLUDE