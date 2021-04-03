#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include <crtdbg.h>

#define SPACEBAR 32

int jumping_array[24] = {8,6,6,4,4,4,2,2,2,2,0,0,0,0};

enum PlayerAnims
{
	STAND_RIGHT, STAND_LEFT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, ATTACK_LEFT, ATTACK_RIGHT, CLIMB, DEAD, CLIMB_ANIM1, CLIMB_ANIM2, ATTACK_AIR_LEFT, ATTACK_AIR_RIGHT,
};

bool last_anim_before_climb = true; //true -> STAND_RIGHT || false -> STAND_LEFT


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	bAttacking = false;
	jump_cont = 0; //Salt sembla correcte, però velocitat massa ràpida
	up_key_released = true;
	jump_colision = false;
	damaged = false;
	hit_cont = 0;
	attack_cont = 0;
	invencible = false;
	space_key_released = true;
	player_speed = 2;
	falling_add = 2;
	falling_cont = 4;
	falling_seq = 0;

	//Carreguem la spritesheet del personatge.
	spritesheet.loadFromFile("images/Goon_128.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	//Creem un vector de 14 posicions, amb els diferents moviments del personatge.
	sprite->setNumberAnimations(14);

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
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.25f, 0.75f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.25f, 0.25f));

	//sprite->setAnimationSpeed(DEAD, 8);
	//sprite->addKeyframe(DEAD, glm::vec2(0.f, 0.6f));
	//sprite->addKeyframe(DEAD, glm::vec2(0.2f, 0.6f));
	//sprite->addKeyframe(DEAD, glm::vec2(0.4f, 0.6f));

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

	sprite->setAnimationSpeed(ATTACK_AIR_LEFT, 8);
	sprite->addKeyframe(ATTACK_AIR_LEFT, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(ATTACK_AIR_RIGHT, 8);
	sprite->addKeyframe(ATTACK_AIR_RIGHT, glm::vec2(0.75f, 0.f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	//Reiniciem les variables només començar el update.
	bFalling = false;
	

	if (!Game::instance().getSpecialKey(GLUT_KEY_UP) && !bJumping) up_key_released = true;
	if (!Game::instance().getKey(SPACEBAR)) space_key_released = true;

	if (map->esticSobreTerra(posPlayer, glm::ivec2(32, 32)))
	{
		bFalling = false;
		bJumping = false;
		jump_colision = false;
		movingL = false;
		movingR = false;
		falling_add = 2;
		falling_cont = 4;
		falling_seq = 0;
		if (!bClimbing) {
			int offsetPos_y = posPlayer.y % 16;
			if (offsetPos_y >= 3) posPlayer.y -= offsetPos_y;
		}
	}

	//Damage taken
	if (damaged) {
		if (hit_cont < 22) dmg_sprite_manager();
		else {
			damaged = false;
			hit_cont = 0;
			invencible = false;
			spritesheet.loadFromFile("images/Goon_128.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite->changeSpriteSheet(&spritesheet);
		}
	}

	//En cas d'haver atacat tornem a posició normal.
	if (sprite->animation() == ATTACK_LEFT && attack_cont == 5) {
		sprite->changeAnimation(STAND_LEFT);
		attack_cont = 0;
		bAttacking = false;
	}
	else if (sprite->animation() == ATTACK_RIGHT && attack_cont == 5) {
		sprite->changeAnimation(STAND_RIGHT);
		attack_cont = 0;
		bAttacking = false;
	}
	else if (sprite->animation() == ATTACK_AIR_LEFT && attack_cont == 5) {
		sprite->changeAnimation(JUMP_LEFT);
		attack_cont = 0;
		bAttacking = false;
	}
	else if (sprite->animation() == ATTACK_AIR_RIGHT && attack_cont == 5) {
		sprite->changeAnimation(JUMP_RIGHT);
		attack_cont = 0;
		bAttacking = false;
	}

	//Si no està sobre terra el personatge cau
	if ((!map->esticSobreTerra(posPlayer, glm::ivec2(32, 32)) && !bJumping && !bClimbing))
	{
		bFalling = true;
	}

	//Si fem servir la tecla barra espaciadora, el personatge atacarà


	//Si premem fletxa esquerra, ens movem a la esquerra, sempre que no colisionem amb res
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !bClimbing && !bFalling && !bJumping && !bAttacking)
	{
		movingL = true;
		//Si l'animació no era la correcta la posem
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);

		//Si no colisionem amb la paret, avancem
		if (!map->collisionMoveLeft(posPlayer, glm::ivec2(16, 32)) && !bClimbing)
		{
			posPlayer.x -= player_speed; //Moviment menys fluit però més similar al joc real.
		}

		if (Game::instance().getSpecialKey(GLUT_KEY_UP) && up_key_released)
		{
			if (map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32), &posPlayer.x))
			{
				bClimbing = true;
				last_anim_before_climb = false;
				posPlayer.y -= player_speed; //Moviment menys fluit però més similar al joc real.
				sprite->changeAnimation(CLIMB_ANIM1);
			}
			else {
				jump_cont = 0;
				bJumping = true;
				up_key_released = false;
			}
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x, posPlayer.y + 16), glm::ivec2(32, 32), &posPlayer.x) && !bJumping) {
				bClimbing = true;
				last_anim_before_climb = false;
				posPlayer.y += 32;
				sprite->changeAnimation(CLIMB_ANIM2);
			}
		}
	}

	//Si premem fletxa dreta, ens movem a la dreta, sempre que no colisionem amb res
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !bClimbing && !bFalling && !bJumping && !bAttacking)
	{
		movingR = true;

		//Si l'animació no era la correcta la posem
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);

		//Si no colisionem amb la paret, avancem
		if (!map->collisionMoveRight(posPlayer, glm::ivec2(16, 32)) && !bClimbing)
		{
			posPlayer.x += player_speed; //Moviment menys fluit però més similar al joc real.
		}

		if (Game::instance().getSpecialKey(GLUT_KEY_UP) && up_key_released)
		{
			if (map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32), &posPlayer.x))
			{
				bClimbing = true;
				last_anim_before_climb = true;
				posPlayer.y -= player_speed; //Moviment menys fluit però més similar al joc real.
				sprite->changeAnimation(CLIMB_ANIM1);
			}
			else {
				jump_cont = 0;
				bJumping = true;
				up_key_released = false;
			}
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x, posPlayer.y + 16), glm::ivec2(32, 32), &posPlayer.x) && !bJumping) {
				bClimbing = true;
				last_anim_before_climb = true;
				posPlayer.y += 32;
				sprite->changeAnimation(CLIMB_ANIM2);
			}
		}
		/*else {
		_RPTF0(0, "choca ");
		_RPT1(0, "%d\n", posPlayer.x);
		}*/
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !bJumping && up_key_released)
	{

		if (bClimbing) {
			if ((posPlayer.y / 8) % 2) sprite->changeAnimation(CLIMB_ANIM2);
			else sprite->changeAnimation(CLIMB_ANIM1);
		}
		//Si just estem al inici d'una planta, pujarem.	
		if (map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32), &posPlayer.x) && !bJumping)
		{
			bClimbing = true;
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) last_anim_before_climb = false;
			else last_anim_before_climb = true;
			posPlayer.y -= player_speed; //Moviment menys fluit però més similar al joc real.
			sprite->changeAnimation(CLIMB_ANIM1);
		}
		//Si arribem al final de la planta, instantàment arribem al nivell de sobre
		else if (bClimbing && map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x, posPlayer.y + 16), glm::ivec2(32, 32), &posPlayer.x))
		{
			bClimbing = false;
			up_key_released = false;
			//Perquè estigui a una posició múltiple de 16.
			int miss = posPlayer.y % 16;
			posPlayer.y -= 8;
			if (last_anim_before_climb) sprite->changeAnimation(STAND_RIGHT);
			else  sprite->changeAnimation(STAND_LEFT);
		}

		//En cas que encara quedi planta per pujar, simplement pujem
		else if (bClimbing && map->climbingPlant(posPlayer, glm::ivec2(32, 32)) && !bJumping)
		{
			posPlayer.y -= player_speed; //Moviment menys fluit però més similar al joc real.
		}
		else if (map->esticSobreTerra(posPlayer, glm::ivec2(32, 32)) && !bClimbing) {
			up_key_released = false;
			jump_cont = 0;
			bJumping = true;
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {

		if (bClimbing) {
			if ((posPlayer.y / 8) % 2) sprite->changeAnimation(CLIMB_ANIM2);
			else sprite->changeAnimation(CLIMB_ANIM1);
		}

		//Si estem al inici d'una enredadera, podrem baixar.
		if (map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x, posPlayer.y + 16), glm::ivec2(32, 32), &posPlayer.x) && !bJumping) {
			bClimbing = true;
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) last_anim_before_climb = false;
			else last_anim_before_climb = true;
			posPlayer.y += 32;
			sprite->changeAnimation(CLIMB_ANIM2);
		}

		//Si ja estavem a una enredadera seguirem baixant.
		else if (bClimbing && map->climbingPlant(posPlayer, glm::ivec2(32, 32)) && !bJumping)
		{
			posPlayer.y += player_speed; //Moviment menys fluit però més similar al joc real.
		}

		//Si es el final d'una enredadera, simplement quedarem de peu
		else if (bClimbing && map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32), &posPlayer.x) && !bJumping)
		{
			bClimbing = false;
			if (last_anim_before_climb) sprite->changeAnimation(STAND_RIGHT);
			else  sprite->changeAnimation(STAND_LEFT);
		}
	}

	//En cas de no estar fent res per teclat ens quedarem en la "idle" position
	else {
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		else if (!bJumping && sprite->animation() == JUMP_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (!bJumping && sprite->animation() == JUMP_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		else if (bJumping && !jump_colision) {
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
				sprite->changeAnimation(JUMP_LEFT);
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
				sprite->changeAnimation(JUMP_RIGHT);
		}
	}

	if (Game::instance().getKey(SPACEBAR) && space_key_released && !bClimbing)
	{
		bAttacking = true;
		space_key_released = false;
		if (sprite->animation() == (MOVE_LEFT) || sprite->animation() == (STAND_LEFT))
			sprite->changeAnimation(ATTACK_LEFT);
		else if (sprite->animation() == (MOVE_RIGHT) || sprite->animation() == (STAND_RIGHT))
			sprite->changeAnimation(ATTACK_RIGHT);
		else if (sprite->animation() == (JUMP_LEFT))
			sprite->changeAnimation(ATTACK_AIR_LEFT);
		else if (sprite->animation() == (JUMP_RIGHT))
			sprite->changeAnimation(ATTACK_AIR_RIGHT);
	}

	if (bJumping) {
		if (movingR) {
			if (!map->collisionMoveRight(posPlayer, glm::ivec2(16, 32))) {
				posPlayer.x += player_speed + 1;
			}
			else {
				jump_colision = true;
				movingR = false;
			}
		}
		else if (movingL) {
			if (!map->collisionMoveLeft(posPlayer, glm::ivec2(16, 32))) {
				posPlayer.x -= player_speed + 1;
			}
			else {
				jump_colision = true;
				movingL = false;
			}
		}
		if (jump_cont < 14)
		{
			if (!map->collisionMoveUp(posPlayer, glm::ivec2(16, 32))) {
				posPlayer.y -= jumping_array[jump_cont];
			}
			else {
				bFalling = true;
				bJumping = false;
				jump_cont = 0;
			}
		}
		else
		{
			if (jump_colision) {
				if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_RIGHT);
				else if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_LEFT);
			}
			bFalling = true;
			bJumping = false;
			jump_cont = 0;
		}
		
		++jump_cont;
	}

	//En cas de no estar sobre una tile de moviment, caurem.
	if (bFalling && !bJumping && !bClimbing)
	{
		posPlayer.y += falling_add;
		++falling_seq;
		if (movingR && (sprite->animation() == JUMP_RIGHT || sprite->animation() == ATTACK_AIR_RIGHT)) {
			if (!map->collisionMoveRight(posPlayer, glm::ivec2(16, 32))) {
				posPlayer.x += player_speed+1;
			}
			else {
				jump_colision = true;
				movingR = false;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else if (movingL && (sprite->animation() == JUMP_LEFT || sprite->animation() == ATTACK_AIR_LEFT)) {
			if (!map->collisionMoveLeft(posPlayer, glm::ivec2(16, 32))) {
				posPlayer.x -= player_speed+1;
			}
			else {
				jump_colision = true;
				movingL = false;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}


	if (map->nextScreen(posPlayer, glm::ivec2(32, 32))) {
		int level = Game::instance().nextScreen();
		if (posPlayer.x < 544) {
			posPlayer.y = 64;
		}
		else posPlayer.x = 96;
	}

	if (map->prevScreen(posPlayer, glm::ivec2(32, 32))) {
		int level = Game::instance().prevScreen();
		if (posPlayer.x > 160) {
			posPlayer.y = 320;
		}
		else posPlayer.x = 548;
	}

	if (map->portal(posPlayer, glm::ivec2(32, 32))) {
		int num = map->quinPortal(posPlayer, glm::ivec2(32, 32));
		int level = 0;
		switch (num) {
		case 1:
			level = Game::instance().goToScreen(6);
			posPlayer.x = 496;
			posPlayer.y = 176;
			break;
		case 2:
			level = Game::instance().goToScreen(9);
			posPlayer.x = 108;
			posPlayer.y = 176;
			break;
		case 3:
			level = Game::instance().goToScreen(13);
			posPlayer.x = 176;
			posPlayer.y = 144;
			break;
		case 4:
			level = Game::instance().goToScreen(15);
			posPlayer.x = 480;
			posPlayer.y = 112;
			break;
		case 5:
			level = Game::instance().goToScreen(12);
			posPlayer.x = 496;
			posPlayer.y = 144;
			break;
		case 6:
			level = Game::instance().goToScreen(5);
			posPlayer.x = 320;
			posPlayer.y = 112;
			break;
		case 7:
			level = Game::instance().goToScreen(5);
			posPlayer.x = 496;
			posPlayer.y = 112;
			break;
		case 8:
			level = Game::instance().goToScreen(11);
			posPlayer.x = 400;
			posPlayer.y = 176;
			break;
		case 9:
			level = Game::instance().goToScreen(14);
			posPlayer.x = 368;
			posPlayer.y = 304;
			break;
		case 10:
			level = Game::instance().goToScreen(8);
			posPlayer.x = 336;
			posPlayer.y = 80;
			break;
		default:
			break;
		}

	}

	if (bAttacking) ++attack_cont;
	if (falling_seq >= falling_cont) {
		falling_seq = 0;
		if(falling_add < 8) falling_add += 2;
		if (falling_cont > 1) --falling_cont;
	}

	//_RPT1(0, "%d\n", posPlayer.x);
	//_RPT1(0, "%d\n", posPlayer.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y - 4)));
	sprite->render();

}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition()
{
	return posPlayer;
}

bool Player::got_hit()
{
	if (!invencible) {
		Game::instance().modifyHP(-2);
		if (Game::instance().noHealth()) {
		Game::instance().restartGame();
		}
		damaged = true;
		invencible = true;
		return true;
	}
	return false;
}

void Player::dmg_sprite_manager()
{
	if (hit_cont % 2) spritesheet.loadFromFile("images/Goon_128_hit_B.png", TEXTURE_PIXEL_FORMAT_RGBA);
	else spritesheet.loadFromFile("images/Goon_128_hit_W.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite->changeSpriteSheet(&spritesheet);
	++hit_cont;
}

bool Player::isAttacking(bool& side) {
	side = (sprite->animation() == ATTACK_LEFT || sprite->animation() == ATTACK_AIR_LEFT);
	return bAttacking;
}
