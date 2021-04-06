#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "WaterDrop.h"
#include "Game.h"
#include "TileMap.h"
#include <crtdbg.h> 



void WaterDrop::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	estat = 0;
	cont = 0;
	spritesheet.loadFromFile("images/WaterDrop.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(12, 16), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 2);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.75f, 0.f));


	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void WaterDrop::update(int deltaTime) {
	if (alive) {
		switch (estat) {
		case 0:
			++cont;
			y = 0;
			if (cont > 15) {
				estat = 1;
			}
			sprite->changeAnimation(0);
			break;
		case 1:
			posPJ.y += 4;
			y += 4;
			sprite->changeAnimation(1);
			if (map->esticSobreTerra(glm::vec2(posPJ.x - 16,posPJ.y-16), glm::ivec2(32, 32))) estat = 2;
			break;
		case 2:
			sprite->changeAnimation(2);
			--cont;
			if (cont < 5) {
				setPosition(glm::vec2(posPJ.x,posPJ.y - y));
				cont = 0;
				estat = 0;
				sprite->changeAnimation(0);
			}
			break;
		default:
			break;
		}
	
	}
	else {
		++cont;
		if (cont > 0) alive = true;
	}
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void WaterDrop::render() {
	if (alive) sprite->render();
}

void WaterDrop::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void WaterDrop::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 WaterDrop::getPosition()
{
	return posPJ;
}

void WaterDrop::collision() {
	cont = -50;
	setPosition(glm::vec2(posPJ.x, posPJ.y - y));
	estat = 0;
	sprite->changeAnimation(0);
	alive = false;
}


bool WaterDrop::isAlive() {
	return alive;
}