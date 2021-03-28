#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();

	bool got_hit();
	bool isAttacking(bool& side);

private:
	bool bJumping, bAttacking, bFalling, bClimbing, jump_colision;
	bool movingR, movingL, up_key_released, damaged, invencible, space_key_released;
	glm::ivec2 tileMapDispl, posPlayer;
	int jump_force, jump_force_moving, startY, hit_cont, attack_cont;
	double jump_velocity;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	void dmg_sprite_manager();
};


#endif // _PLAYER_INCLUDE


