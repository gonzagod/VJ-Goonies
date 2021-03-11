#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include <crtdbg.h>


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define SPACEBAR 32


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, ATTACK_LEFT, ATTACK_RIGHT, CLIMB, DEAD
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;

	//Carreguem la spritesheet del personatge.
	spritesheet.loadFromFile("images/Goon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33, 0.25), &spritesheet, &shaderProgram);
	//Creem un vector de 9 posicions, amb els diferents moviments del personatge.
	sprite->setNumberAnimations(9);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.33f, 0.5f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.66f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.66f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.33f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.66f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.33f, 0.75f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.33f, 0.25f));

	//sprite->setAnimationSpeed(DEAD, 8);
	//sprite->addKeyframe(DEAD, glm::vec2(0.f, 0.6f));
	//sprite->addKeyframe(DEAD, glm::vec2(0.2f, 0.6f));
	//sprite->addKeyframe(DEAD, glm::vec2(0.4f, 0.6f));

	sprite->setAnimationSpeed(ATTACK_LEFT, 8);
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.66f, 0.75f));

	sprite->setAnimationSpeed(ATTACK_RIGHT, 8);
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.66f, 0.25f));

	sprite->setAnimationSpeed(CLIMB, 8);
	sprite->addKeyframe(CLIMB, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(CLIMB, glm::vec2(0.33f, 0.f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	//Reiniciem les variables només començar el update.
	bFalling = false;
	bJumping = false;
	bAttacking = false;
	
	//En cas d'haver atacat tornem a posició normal.
	if (sprite->animation() == ATTACK_LEFT) sprite->changeAnimation(STAND_LEFT);
	else if (sprite->animation() == ATTACK_RIGHT) sprite->changeAnimation(STAND_RIGHT);

	//Si no està sobre terra el personatge cau
	if (!map->esticSobreTerra(posPlayer, glm::ivec2(32, 32)))
	{
		bFalling = true;
	}

	//Si fem servir la tecla barra espaciadora, el personatge atacarà
	else if (Game::instance().getKey(SPACEBAR)) 
	{
		bAttacking = true;
		if (sprite->animation() == (JUMP_LEFT) || sprite->animation() == (MOVE_LEFT) || sprite->animation() == (STAND_LEFT))
		sprite->changeAnimation(ATTACK_LEFT);
		else if (sprite->animation() == (JUMP_RIGHT) || sprite->animation() == (MOVE_RIGHT) || sprite->animation() == (STAND_RIGHT))
		sprite->changeAnimation(ATTACK_RIGHT);
	}

	//Si premem fletxa esquerra, ens movem a la esquerra, sempre que no colisionem amb res
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !bClimbing && !bFalling)
	{
		//Si l'animació no era la correcta la posem
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);

		//Si no colisionem amb la paret, avancem
		if (!map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
		}
	}

	//Si premem fletxa dreta, ens movem a la dreta, sempre que no colisionem amb res
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !bClimbing && !bFalling)
	{
		//Si l'animació no era la correcta la posem
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);

		//Si no colisionem amb la paret, avancem
		if (!map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		//if (map->esticSobreTerra(posPlayer, glm::ivec2(32, 32)))
			//bJumping = true;

	    //Si just estem al inici d'una planta, pujarem.	
	    if (map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32))) 
		{
			bClimbing = true;
			posPlayer.y -= 1;
			sprite->changeAnimation(CLIMB);
		}
		//Si arribem al final de la planta, instantàment arribem al nivell de sobre
	    else if (bClimbing && map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x, posPlayer.y + 16), glm::ivec2(32, 32)))
		{
			bClimbing = false;
			posPlayer.y -= 16;
			sprite->changeAnimation(STAND_RIGHT);
		}

		//En cas que encara quedi planta per pujar, simplement pujem
		else if (bClimbing && map->climbingPlant(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.y -= 1;
		}

	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {

		//Si estem al inici d'una enredadera, podrem baixar.
		if (map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x, posPlayer.y + 16), glm::ivec2(32, 32))) {
			bClimbing = true;
			posPlayer.y += 1;
			sprite->changeAnimation(CLIMB);
		}

		//Si ja estavem a una enredadera seguirem baixant.
		else if (bClimbing && map->climbingPlant(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.y += 1;
		}

		//Si es el final d'una enredadera, simplement quedarem de peu
		else if (bClimbing && map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32)))
		{
			bClimbing = false;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}

	//En cas de no estar fent res per teclat ens quedarem en la "idle" position
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		else if (bJumping == false && sprite->animation() == JUMP_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (bJumping == false && sprite->animation() == JUMP_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	/*
	if(bJumping)
	{
	posPlayer.y -= 4;
	if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
	sprite->changeAnimation(JUMP_LEFT);
	else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
	sprite->changeAnimation(JUMP_RIGHT);
	}
	else
	{
	posPlayer.y += FALL_STEP;
	if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
	{
	//if(Game::instance().getSpecialKey(GLUT_KEY_UP))
	//{
	//bJumping = true;
	//jumpAngle = 0;
	//startY = posPlayer.y;
	//}
	}
	}*/

	//En cas de no estar sobre una tile de moviment, caurem.
	if (bFalling)
	{
		posPlayer.y += 2;
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	//En cas d'estar atacant, si impactem contra un enemic li farem mal.
	if (bAttacking)
	{
		if (map->attackFoundTargetRight(posPlayer, glm::ivec2(32,32)));
		else if (map->attackFoundTargetLeft(posPlayer, glm::ivec2(32, 32)));
	}

	_RPT1(0, "%d\n", posPlayer.x);
	_RPT1(0, "%d\n", posPlayer.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
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




