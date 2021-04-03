#ifndef _BULLET_INCLUDE
#define _BULLET_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Bullet
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	bool is_Alive();
	void player_hit();
	void setDirection(bool side);

private:
	bool movingR, movingL, alive;
	int bullet_speed;
	glm::ivec2 tileMapDispl, posBullet;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif // _BULLET_INCLUDE


