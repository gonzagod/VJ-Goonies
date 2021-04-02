#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Stalactites.h"
#include "Game.h"
#include <crtdbg.h> 



void Stalactites::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	activated = false;
	cont = 0;
	spritesheet.loadFromFile("images/Stalactites.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(0.5, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(3, 8);
	sprite->addKeyframe(3, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(4, 8);
	sprite->addKeyframe(4, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(5, 8);
	sprite->addKeyframe(5, glm::vec2(0.f, 0.75f));

	sprite->changeAnimation(3);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void Stalactites::update(int deltaTime, int x) {
	
	if (activated) {
	switch (x) {
	case 0:
		if (map->esticSobreTerra(glm::vec2(posPJ.x - 16, posPJ.y - 16), glm::ivec2(32, 32))) {
			if (sprite->animation() != 0) sprite->changeAnimation(0);
			++cont;
			if (cont > 50) {
				alive = false;
			}
		}
		else {
			if (sprite->animation() != 3) sprite->changeAnimation(3);
			posPJ.y += 4;
		}
		break;
	case 1:
		if (map->esticSobreTerra(glm::vec2(posPJ.x - 16, posPJ.y - 16), glm::ivec2(32, 32))) {
			if (sprite->animation() != 1) sprite->changeAnimation(1);
			++cont;
			if (cont > 50) {
				alive = false;
			}
		}
		else {
			if (sprite->animation() != 4) sprite->changeAnimation(4);
			posPJ.y += 4;
		}
		break;
	case 2:
		if (map->esticSobreTerra(glm::vec2(posPJ.x - 16, posPJ.y - 16), glm::ivec2(32, 32))) {
			if (sprite->animation() != 2) sprite->changeAnimation(2);
			++cont;
			if (cont > 50) {
				alive = false;
			}
		}
		else {
			if (sprite->animation() != 5) sprite->changeAnimation(5);
			posPJ.y += 4;
		}
		break;
	}
	
	}
	else sprite->changeAnimation(x + 3);
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));


}

void Stalactites::render() {
	if (alive) sprite->render();
}

void Stalactites::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Stalactites::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 Stalactites::getPosition()
{
	return posPJ;
}

void Stalactites::activate() {
	activated = true;
}


bool Stalactites::isDangerous() {
	if (sprite->animation() > 2) return true;
	else return false;
}