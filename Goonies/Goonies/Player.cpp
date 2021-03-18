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


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, ATTACK_LEFT, ATTACK_RIGHT, CLIMB, DEAD
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;

	spritesheet.loadFromFile("images/Goon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33, 0.25), &spritesheet, &shaderProgram);
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x ), float(tileMapDispl.y + posPlayer.y )));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	bFalling = false;
	bJumping = false;
	if (!map->esticSobreTerra(posPlayer, glm::ivec2(32, 32)))
	{
		bFalling = true;
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !bClimbing && !bFalling)
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
	
		if (!map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !bClimbing && !bFalling)
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
	
		if (!map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
		}
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		if (map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32))) {
			bClimbing = true;
			posPlayer.y -= 1;
			sprite->changeAnimation(CLIMB);
		}
		else if (bClimbing && map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x,posPlayer.y + 16), glm::ivec2(32, 32)))
		{
			bClimbing = false;
			posPlayer.y -= 16;
			sprite->changeAnimation(STAND_RIGHT);
		}
		else if (bClimbing && map->climbingPlant(posPlayer, glm::ivec2(32, 32))) 
		{
			posPlayer.y -= 1;
		}
		
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		if (map->finalPartOfPlantClimbing(glm::ivec2(posPlayer.x,posPlayer.y+16), glm::ivec2(32, 32))) {
			bClimbing = true;
			posPlayer.y += 1;
			sprite->changeAnimation(CLIMB);
		}
		else if (bClimbing && map->climbingPlant(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.y += 1;
		}
		else if (bClimbing && map->finalPartOfPlantDescending(posPlayer, glm::ivec2(32, 32)))
		{
			bClimbing = false;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}


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

	if (bFalling)
	{
			posPlayer.y += 2;
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
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




