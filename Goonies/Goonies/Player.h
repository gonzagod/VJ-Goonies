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
	void give_bullet();
	int getParryCont();
	bool hasBullet();

	bool got_hit(int num_enemy);
	bool got_hit_by_water();
	bool got_hit_by_stalactite();
	bool got_hit_by_steam();
	bool isAttacking(bool& side);
	bool isParrying(bool& side);
	bool portalStatus();

private:
	bool bJumping, bAttacking, bFalling, bClimbing, jump_colision, bParrying, bShooting;
	bool movingR, movingL, up_key_released, damaged, invencible, space_key_released, parry_key_released, got_bullet;
	bool HyperShoes, Helmet, GrayRaincoat, BlueSpellbook, YellowRaincoat;
	bool isGodMode, isInPortal;
	int cont;
	glm::ivec2 tileMapDispl, posPlayer;
	int jump_cont, startY, hit_cont, attack_cont, player_speed,	falling_cont, falling_add,
		falling_seq, parry_cont, shot_cont, parry_again_cont, shoot_cont;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	void dmg_sprite_manager();
	bool cant_move, canParry;
};


#endif // _PLAYER_INCLUDE


