#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Door.h"
#include "Game.h"
#include <crtdbg.h> 



void Door::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	spritesheet.loadFromFile("images/Door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 64), glm::vec2(1,0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.f, 0.5f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void Door::update(int deltaTime, int x) {
	if (alive) {

		switch (x) {
		case 0:
			sprite->changeAnimation(0);
			break;
		case 1:
			sprite->changeAnimation(1);
			break;
		case 2:
			sprite->changeAnimation(2);
			break;
		default:
			break;
		}
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
	}
	
	
}

void Door::render() {
	if (alive) sprite->render();
}

void Door::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Door::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 Door::getPosition()
{
	return posPJ;
}

void Door::open() {
	alive = false;
}


bool Door::isAlive() {
	return alive;
}