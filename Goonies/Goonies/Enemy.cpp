#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"
#include <crtdbg.h>

int jumping_enemy_array[24] = { 8,6,6,4,4,4,2,2,2,2,0,0,0,0 };

bool last_state_before_climb = false; //true -> STAND_RIGHT || false -> STAND_LEFT

enum EnemyAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, ATTACK_LEFT, ATTACK_RIGHT, CLIMB, STUN, CLIMB_ANIM1, CLIMB_ANIM2, LOOK,
};

enum EnemyState
{
	NONE, WAIT, LOOKING_AROUND, ATTACKING_LEFT, ATTACKING_RIGHT, JUMPING_LEFT, JUMPING_RIGHT, WALKING_LEFT,
	WALKING_RIGHT, STUNS, LOOKING_PLAYER, CLIMBING, DESC,
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	bJumping = false;
	bAttacking = false;
	jump_colision = false;
	damaged = false;
	stun_cont = 0;
	attack_cont = 0;
	enemy_speed = 2;
	falling_add = 2;
	falling_cont = 4;
	falling_seq = 0;
	state = NONE;
	state_cont = 0;
	prev_state = NONE;
	looking_loop_cont = 3;
	cont_until_look = 0;
	max_cont_look = 110;
	next_time_climb = false;
	next_time_desc = false;
	jump_cont = 550;
	level_enemy = 1;
	timing = 0;
	alive = false;
	bullet_shot = false;
	bullet_dir = false;

	//Carreguem la spritesheet del personatge.
	spritesheet.loadFromFile("images/enemy_default.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	//Creem un vector de 13 posicions, amb els diferents moviments del enemic.
	sprite->setNumberAnimations(13);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(STUN, 8);
	sprite->addKeyframe(STUN, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(STUN, glm::vec2(0.25f, 0.75f));

	sprite->setAnimationSpeed(ATTACK_LEFT, 8);
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.5f, 0.75f));

	sprite->setAnimationSpeed(ATTACK_RIGHT, 8);
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(CLIMB, 8);
	sprite->addKeyframe(CLIMB, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(CLIMB, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(CLIMB_ANIM1, 8);
	sprite->addKeyframe(CLIMB_ANIM1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(CLIMB_ANIM2, 8);
	sprite->addKeyframe(CLIMB_ANIM2, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(LOOK, 4);
	sprite->addKeyframe(LOOK, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(LOOK, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime)
{
	if (level_enemy > 3) alive = true;
	else if (level_enemy == 3) {
		if (timing <= 150) ++timing;
		if (timing > 150) alive = true;
	}

	sprite->update(deltaTime);
	//Reiniciem les variables només començar el update.
	bFalling = false;

	if (state != STUNS && level_enemy == level_player) chase = true;

	if (map->esticSobreTerra(posEnemy, glm::ivec2(32, 32)) && !bClimbing)
	{
		bFalling = false;
		bJumping = false;
		jump_colision = false;
		falling_add = 2;
		falling_cont = 4;
		falling_seq = 0;
		if (cont_until_look >= max_cont_look && state != STUNS) {
			state_cont = 0;
			prev_state = state;
			state = LOOKING_AROUND;
		}

		int offsetPos_y = posEnemy.y % 16;
		if (offsetPos_y > 3) {
			posEnemy.y -= offsetPos_y;
		}

		if (damaged) {
			state = STUNS;
			state_cont = 0;
			damaged = false;
		}
	}

	if ((!map->esticSobreTerra(posEnemy, glm::ivec2(32, 32)) && !bJumping && !bClimbing))
	{
		bFalling = true;
	}
	else {
		if (looking_loop_cont >= 1 && (abs(posEnemy.y - posPlayer.y) <= 8) && state != STUNS && !bClimbing && chase) {
			state = LOOKING_PLAYER;
			state_cont = 0;
			cont_until_look = 0;
			looking_loop_cont = 0;
			next_time_climb = false;
			next_time_desc = false;
		}

		if (alive) ++state_cont;
		if (level_enemy == 3 && alive) ++jump_cont;

		switch (state)
		{
		case 0: //NONE
			if (waiting_time <= state_cont) {
				state_cont = 0;
				waiting = false;
				state = LOOKING_AROUND;
			}
			break;
		case 2: //LOOK AROUND
			cont_until_look = 0;
			if (state_cont <= 24) {
				if (sprite->animation() != LOOK) sprite->changeAnimation(LOOK);
			}
			else {
				++looking_loop_cont;
				int max_loop = 2;
				if (level_enemy != level_player && chase && abs(posEnemy.y - posPlayer.y) > 8) max_loop = 0;
				if (looking_loop_cont >= max_loop && ((posEnemy.y - posPlayer.y) > 8) && chase) {
					next_time_climb = true;
				}
				else if (looking_loop_cont >= max_loop && ((posPlayer.y - posEnemy.y) > 8) && chase) {
					next_time_desc = true;
				}
				if (prev_state == 0 || prev_state == 9) {
					prev_state = state;
					if (posEnemy.x < posPlayer.x) {
						if (chase) state = WALKING_RIGHT;
						else state = WALKING_LEFT;
					}
					else state = WALKING_LEFT;
				}
				else if (prev_state == 5 || prev_state == 7) {
					prev_state = state;
					if (looking_loop_cont > 3) {
						if (posEnemy.x < posPlayer.x) {
							if (chase) state = WALKING_RIGHT;
							else state = WALKING_LEFT;
						}
						else state = WALKING_LEFT;
					}
					else state = WALKING_LEFT;
				}
				else if (prev_state == 6 || prev_state == 8) {
					prev_state = state;
					if (looking_loop_cont > 3) {
						if (posEnemy.x > posPlayer.x) {
							if (chase) state = WALKING_LEFT;
							else state = WALKING_RIGHT;
						}
						else state = WALKING_RIGHT;
					}
					else state = WALKING_RIGHT;
				}
				else if (prev_state == 11) {
					prev_state = state;
					if (last_state_before_climb) state = WALKING_RIGHT;
					else state = WALKING_LEFT;
				}

				if (abs(posEnemy.y - posPlayer.y) <= 8 && chase) {
					state_cont = 0;
					state = LOOKING_PLAYER;
					cont_until_look = 0;
					looking_loop_cont = 0;
					next_time_climb = false;
					next_time_desc = false;
				}
				movingL = false;
				movingR = false;
				state_cont = 0;
			}
			break;
		case 3: //ATTACKING LEFT
			if (state_cont <= 24) {
				bAttacking = true;
				if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(ATTACK_LEFT);
				if (state_cont == 8) shoot(false);
				else if (state_cont == 9) bullet_shot = false;
			}
			else {
				movingL = false;
				movingR = false;
				bAttacking = false;
				state_cont = 0;
				sprite->changeAnimation(STAND_LEFT);
				prev_state = state;
				state = WALKING_LEFT;
			}
			break;
		case 4: //ATTACKING RIGHT
			if (state_cont <= 24) {
				if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(ATTACK_RIGHT);
				if (state_cont == 8) shoot(true);
				else if (state_cont == 9) bullet_shot = false;
			}
			else {
				movingL = false;
				movingR = false;
				state_cont = 0;
				sprite->changeAnimation(STAND_RIGHT);
				prev_state = state;
				state = WALKING_RIGHT;
			}
			break;
		case 5: //JUMPING LEFT
			++cont_until_look;
			jump_cont = 0;
			bJumping = true;
			if (movingL) {
				if (!map->collisionMoveLeft(posEnemy, glm::ivec2(16, 32))) {
					posEnemy.x -= enemy_speed + 1;
				}
				else {
					jump_colision = true;
					movingL = false;
				}
			}
			if (state_cont <= 14)
			{
				if (sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);
				if (!map->collisionMoveUp(posEnemy, glm::ivec2(16, 32))) {
					posEnemy.y -= jumping_enemy_array[state_cont - 1];
				}
				else {
					bFalling = true;
					bJumping = false;
					state_cont = 0;
				}
			}
			else
			{
				if (jump_colision) sprite->changeAnimation(STAND_LEFT);
				bFalling = true;
				bJumping = false;
				state_cont = 0;
			}
			prev_state = state;
			break;
		case 6: //JUMPING RIGHT
			++cont_until_look;
			jump_cont = 0;
			bJumping = true;
			if (movingR) {
				if (!map->collisionMoveRight(posEnemy, glm::ivec2(16, 32))) {
					posEnemy.x += enemy_speed + 1;
				}
				else {
					jump_colision = true;
					movingR = false;
				}
			}
			if (state_cont <= 14)
			{
				if (sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
				if (!map->collisionMoveUp(posEnemy, glm::ivec2(16, 32))) {
					posEnemy.y -= jumping_enemy_array[state_cont - 1];
				}
				else {
					bFalling = true;
					bJumping = false;
					state_cont = 0;
				}
			}
			else
			{
				if (jump_colision) sprite->changeAnimation(STAND_LEFT);
				bFalling = true;
				bJumping = false;
				state_cont = 0;
			}
			prev_state = state;
			break;
		case 7: //WALKING LEFT
			++cont_until_look;
			prev_state = WALKING_LEFT;
			if (state_cont <= 104) {
				movingL = true;
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
				if (!map->collisionMoveLeft(posEnemy, glm::ivec2(16, 32)))
				{
					posEnemy.x -= enemy_speed; //Moviment menys fluit però més similar al joc real.
				}
				else {
					movingL = false;
					prev_state = WALKING_RIGHT;
					state = WALKING_RIGHT;
				}

				if (jump_cont >= 600) {
					state = JUMPING_LEFT;
					state_cont = 0;
				}

				if (next_time_climb && map->finalPartOfPlantDescending(posEnemy, glm::ivec2(32, 32), &posEnemy.x) && !bJumping)
				{
					bClimbing = true;
					if (prev_state == WALKING_LEFT) last_state_before_climb = false;
					else last_state_before_climb = true;
					posEnemy.y -= enemy_speed; //Moviment menys fluit però més similar al joc real.
					sprite->changeAnimation(CLIMB_ANIM1);
					state_cont = 0;
					state = CLIMBING;
				}
				else if (next_time_desc &&
					map->finalPartOfPlantClimbing(glm::ivec2(posEnemy.x, posEnemy.y + 16), glm::ivec2(32, 32), &posEnemy.x) && !bJumping) {
					bClimbing = true;
					if (prev_state == WALKING_LEFT) last_state_before_climb = false;
					else last_state_before_climb = true;
					posEnemy.y += 32;
					sprite->changeAnimation(CLIMB_ANIM2);
					state_cont = 0;
					state = DESC;
				}
			}
			else
			{
				state_cont = 0;
				state = LOOKING_AROUND;
			}
			break;
		case 8: //WALKING RIGHT
			++cont_until_look;
			prev_state = WALKING_RIGHT;
			if (state_cont <= 104) {
				movingR = true;
				if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
				if (!map->collisionMoveRight(posEnemy, glm::ivec2(16, 32)))
				{
					posEnemy.x += enemy_speed; //Moviment menys fluit però més similar al joc real.
				}
				else {
					movingR = false;
					prev_state = WALKING_LEFT;
					state = WALKING_LEFT;
				}

				if (jump_cont >= 600) {
					state = JUMPING_RIGHT;
					state_cont = 0;
				}

				if (next_time_climb && map->finalPartOfPlantDescending(posEnemy, glm::ivec2(32, 32), &posEnemy.x) && !bJumping)
				{
					bClimbing = true;
					if (prev_state == WALKING_LEFT) last_state_before_climb = false;
					else last_state_before_climb = true;
					posEnemy.y -= enemy_speed; //Moviment menys fluit però més similar al joc real.
					sprite->changeAnimation(CLIMB_ANIM1);
					state_cont = 0;
					state = CLIMBING;
				}
				else if (next_time_desc &&
					map->finalPartOfPlantClimbing(glm::ivec2(posEnemy.x, posEnemy.y + 16), glm::ivec2(32, 32), &posEnemy.x) && !bJumping) {
					bClimbing = true;
					if (prev_state == WALKING_LEFT) last_state_before_climb = false;
					else last_state_before_climb = true;
					posEnemy.y += 32;
					sprite->changeAnimation(CLIMB_ANIM2);
					state_cont = 0;
					state = DESC;
				}
			}
			else
			{
				state_cont = 0;
				state = LOOKING_AROUND;
			}
			break;
		case 9: //STUNS
			if (state_cont <= 96) {
				if (sprite->animation() != STUN)sprite->changeAnimation(STUN);
				looking_loop_cont = 0;
				next_time_climb = false;
				next_time_desc = false;
				cont_until_look = 0;
			}
			else {
				movingL = false;
				movingR = false;
				state_cont = 0;
				prev_state = state;
				state = LOOKING_AROUND;
				if (level_player != level_enemy) chase = false;
			}
			break;
		case 10: //LOOKING_PLAYER
			if (state_cont <= 10) {
				if (state_cont == 1) lookAtPlayer();
			}
			else {
				movingL = false;
				movingR = false;
				state_cont = 0;
				prev_state = state;
				if (sprite->animation() == STAND_LEFT) state = ATTACKING_LEFT;
				else state = ATTACKING_RIGHT;
			}
			break;
		case 11: //CLIMBING
			++cont_until_look;
			bClimbing = true;

			if ((posEnemy.y / 8) % 2) sprite->changeAnimation(CLIMB_ANIM2);
			else sprite->changeAnimation(CLIMB_ANIM1);

			if (map->finalPartOfPlantClimbing(glm::ivec2(posEnemy.x, posEnemy.y + 16), glm::ivec2(32, 32), &posEnemy.x))
			{
				bClimbing = false;
				//Perquè estigui a una posició múltiple de 16.
				//int miss = posEnemy.y % 16;
				posEnemy.y -= 16;
				if (last_state_before_climb) state = WALKING_RIGHT;
				else  state = WALKING_LEFT;
				prev_state = CLIMBING;
				state_cont = 0;
			}
			else if (map->climbingPlant(posEnemy, glm::ivec2(32, 32)) && !bJumping)
			{
				posEnemy.y -= enemy_speed; //Moviment menys fluit però més similar al joc real.
			}
			break;
		case 12: //DESC
			++cont_until_look;
			bClimbing = true;

			if ((posEnemy.y / 8) % 2) sprite->changeAnimation(CLIMB_ANIM2);
			else sprite->changeAnimation(CLIMB_ANIM1);

			if (bClimbing && map->finalPartOfPlantDescending(posEnemy, glm::ivec2(32, 32), &posEnemy.x) && !bJumping)
			{
				bClimbing = false;
				if (last_state_before_climb) state = WALKING_RIGHT;
				else  state = WALKING_LEFT;
				prev_state = CLIMBING;
				state_cont = 0;
			}
			else if (map->climbingPlant(posEnemy, glm::ivec2(32, 32)) && !bJumping)
			{
				posEnemy.y += enemy_speed; //Moviment menys fluit però més similar al joc real.
			}
			break;
		default:
			++state_cont;
			break;
		}
	}

	if (bFalling && !bJumping && !bClimbing)
	{
		posEnemy.y += falling_add;
		++falling_seq;
		if (movingR && sprite->animation() == JUMP_RIGHT) {
			state = WALKING_RIGHT;
			if (!map->collisionMoveRight(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.x += enemy_speed + 1;
			}
			else {
				jump_colision = true;
				movingR = false;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else if (movingL && sprite->animation() == JUMP_LEFT) {
			state = WALKING_LEFT;
			if (!map->collisionMoveLeft(posEnemy, glm::ivec2(16, 32))) {
				posEnemy.x -= enemy_speed + 1;
			}
			else {
				jump_colision = true;
				movingL = false;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		if (sprite->animation() == MOVE_LEFT) sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)	sprite->changeAnimation(STAND_RIGHT);
	}

	if (falling_seq >= falling_cont) {
		falling_seq = 0;
		if (falling_add < 8) falling_add += 2;
		if (falling_cont > 1) --falling_cont;
	}

	if (map->nextScreen(posEnemy, glm::ivec2(32, 32))) {
		++level_enemy;
		if (posEnemy.x < 544) {
			posEnemy.y = 64;
		}
		else posEnemy.x = 96;
	}

	if (map->prevScreen(posEnemy, glm::ivec2(32, 32))) {
		--level_enemy;
		if (posEnemy.x > 160) {
			posEnemy.y = 320;
		}
		else posEnemy.x = 548;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::render()
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y - 4)));
	sprite->render();
}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

glm::ivec2 Enemy::getPosition()
{
	return posEnemy;
}

void Enemy::setPlayerPos(glm::ivec2 PlayerPos, int level_p) {
	posPlayer = PlayerPos;
	level_player = level_p;
}

void Enemy::lookAtPlayer() {
	if (posEnemy.x < posPlayer.x) sprite->changeAnimation(STAND_RIGHT);
	else sprite->changeAnimation(STAND_LEFT);
}

void Enemy::shoot(bool side) {
	if (level_enemy == level_player) {
		bullet_shot = true;
		bullet_dir = side;
	}
	else {
		bullet_shot = false;
	}
}

int Enemy::getLevelEnemy() {
	return level_enemy;
}

void Enemy::setLevelEnemy(int enemy_level) {
	level_enemy = enemy_level;
}

bool Enemy::is_Stun()
{
	return damaged;
}

void Enemy::get_damage()
{
	damaged = true;
}

bool Enemy::can_dmg()
{
	return state != STUNS;
}

bool Enemy::is_Alive() 
{
	return alive;
}

bool Enemy::getBulletDir()
{
	return bullet_dir;
}

bool Enemy::isShot()
{
	return bullet_shot;
}

void Enemy::collided_player()
{
	if (state == WALKING_LEFT) {
		movingL = false;
		prev_state = WALKING_RIGHT;
		state = WALKING_RIGHT;
	}
	else {
		movingR = false;
		prev_state = WALKING_LEFT;
		state = WALKING_LEFT;
	}
}
