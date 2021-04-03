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

	void powerupHyperShoes();
	void powerupGrayRaincoat();
	void powerupYellowRaincoat();
	void powerupBlueSpellbook();
	void powerupHelmet();
	void godMode();

	bool got_hit();
	bool got_hit_by_water();
	bool got_hit_by_stalactite();
	bool got_hit_by_steam();
	bool isAttacking(bool& side);
	bool portalStatus();

private:
	bool bJumping, bAttacking, bFalling, bClimbing, jump_colision;
	bool movingR, movingL, up_key_released, damaged, invencible, space_key_released;
	bool HyperShoes, Helmet, GrayRaincoat, BlueSpellbook, YellowRaincoat;
	bool isGodMode, isInPortal;
	int cont;
	glm::ivec2 tileMapDispl, posPlayer;
	int jump_cont, startY, hit_cont, attack_cont, player_speed, falling_cont, falling_add, falling_seq;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	void dmg_sprite_manager();
};


#endif // _PLAYER_INCLUDE


