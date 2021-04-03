#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"
#include "Game.h"
#include <crtdbg.h>

enum BulletAnims
{
	ANIM,
};

void Bullet::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	movingL = false;
	movingR = false;
	alive = false;
	bullet_speed = 4;

	spritesheet.loadFromFile("images/TheGoonies-MapTiles2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.0625, 0.0625), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(ANIM, 8);
	sprite->addKeyframe(ANIM, glm::vec2(0.375f, 0.875f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x), float(tileMapDispl.y + posBullet.y)));
}

void Bullet::update(int deltaTime) {

	if (movingL) {
		if (!map->collisionMoveLeft(posBullet, glm::ivec2(16, 10)))
		{
			posBullet.x -= bullet_speed; //Moviment menys fluit però més similar al joc real.
		}
		else {
			movingL = false;
			alive = false;
		}
	}
	else if (movingR) {
		if (!map->collisionMoveRight(posBullet, glm::ivec2(16, 10)))
		{
			posBullet.x += bullet_speed; //Moviment menys fluit però més similar al joc real.
		}
		else {
			movingR = false;
			alive = false;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x), float(tileMapDispl.y + posBullet.y)));
}

void Bullet::render()
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x), float(tileMapDispl.y + posBullet.y)));
	sprite->render();
}

void Bullet::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Bullet::setPosition(const glm::vec2 &pos)
{
	posBullet = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x), float(tileMapDispl.y + posBullet.y)));
}

glm::ivec2 Bullet::getPosition()
{
	return posBullet;
}

bool Bullet::is_Alive()
{
	return alive;
}

void Bullet::player_hit() {
	alive = false;
}

void Bullet::setDirection(bool side)
{
	//true -> STAND_RIGHT || false -> STAND_LEFT
	if (side) {
		movingR = true;
		movingL = false;
	}
	else {
		movingL = true;
		movingR = false;
	}
	alive = true;
}
