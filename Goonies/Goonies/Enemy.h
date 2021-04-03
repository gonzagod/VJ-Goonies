#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Bullet.h"

class Enemy
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();

	void setPlayerPos(glm::ivec2 PlayerPos, int level_p);
	int getLevelEnemy();
	void setLevelEnemy(int enemy_level);
	bool is_Stun();
	void get_damage();
	bool can_dmg();
	bool is_Alive();
	bool getBulletDir();
	bool isShot();
	void collided_player();

private:
	bool bJumping, bAttacking, bFalling, bClimbing, jump_colision, waiting;
	bool movingR, movingL, damaged, next_time_climb, chase, next_time_desc, alive;
	glm::ivec2 tileMapDispl, posEnemy, posPlayer;
	int startY, stun_cont, attack_cont, enemy_speed, falling_cont,
		falling_add, falling_seq, waiting_time, state_cont, 
		looking_loop_cont, cont_until_look, max_cont_look, jump_cont, timing;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	void lookAtPlayer();
	int state, prev_state, level_enemy, level_player;
	bool bullet_shot, bullet_dir;
	void shoot(bool side);
};


#endif // _ENEMY_INCLUDE
