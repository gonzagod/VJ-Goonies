#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Puntuacio.h"
#include "Game.h"
#include <crtdbg.h> 

enum LletresNums {
	CERO, UN, DOS, TRES, QUATRE, CINC, SIS, SET, VUIT, NOU
};

void Puntuacio::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/LletresNums.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.2, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(CERO, 8);
	sprite->addKeyframe(CERO, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(UN, 8);
	sprite->addKeyframe(UN, glm::vec2(0.2f, 0.f));

	sprite->setAnimationSpeed(DOS, 8);
	sprite->addKeyframe(DOS, glm::vec2(0.4f, 0.f));

	sprite->setAnimationSpeed(TRES, 8);
	sprite->addKeyframe(TRES, glm::vec2(0.6f, 0.f));

	sprite->setAnimationSpeed(QUATRE, 8);
	sprite->addKeyframe(QUATRE, glm::vec2(0.8f, 0.f));

	sprite->setAnimationSpeed(CINC, 8);
	sprite->addKeyframe(CINC, glm::vec2(0.f, 0.2f));

	sprite->setAnimationSpeed(SIS, 8);
	sprite->addKeyframe(SIS, glm::vec2(0.2f, 0.2f));

	sprite->setAnimationSpeed(SET, 8);
	sprite->addKeyframe(SET, glm::vec2(0.4f, 0.2f));

	sprite->setAnimationSpeed(VUIT, 8);
	sprite->addKeyframe(VUIT, glm::vec2(0.6f, 0.2f));

	sprite->setAnimationSpeed(NOU, 8);
	sprite->addKeyframe(NOU, glm::vec2(0.8f, 0.2f));

	
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void Puntuacio::update(int deltaTime, int numPersonatge, int points, int level) {
	switch (numPersonatge) {
	case 0:
		sprite->changeAnimation((points/100000) % 10);
		break;
	case 1:
		sprite->changeAnimation((points/10000) % 10);
		break;
	case 2:
		sprite->changeAnimation((points/1000) % 10);
		break;
	case 3:
		sprite->changeAnimation((points/100) % 10);
		break;
	case 4:
		sprite->changeAnimation((points/10) % 10);
		break;
	case 5:
		sprite->changeAnimation(points % 10);
		break;
	case 6:
		sprite->changeAnimation((points / 100000) % 10);
		break;
	case 7:
		sprite->changeAnimation((points / 10000) % 10);
		break;
	case 8:
		sprite->changeAnimation((points / 1000) % 10);
		break;
	case 9:
		sprite->changeAnimation((points / 100) % 10);
		break;
	case 10:
		sprite->changeAnimation((points / 10) % 10);
		break;
	case 11:
		sprite->changeAnimation(points % 10);
		break;
	case 12:
		sprite->changeAnimation((level/3));
		break;
	case 13:
		sprite->changeAnimation((level + 1) % 3);
		break;
	default:
		break;

	}

	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void Puntuacio::render() {
	sprite->render();
}

void Puntuacio::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Puntuacio::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

