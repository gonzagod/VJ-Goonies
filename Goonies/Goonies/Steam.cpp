#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Steam.h"
#include "Game.h"
#include <crtdbg.h> 

enum anim {
	NOTHING, START_LEFT, START_RIGHT, STEAM_LEFT, STEAM_RIGHT
};

void Steam::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	cont = 0;
	estat = 0;
	spritesheet.loadFromFile("images/Steam.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(NOTHING, 8);
	sprite->addKeyframe(NOTHING, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(START_LEFT, 8);
	sprite->addKeyframe(START_LEFT, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(START_LEFT, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(START_RIGHT, 8);
	sprite->addKeyframe(START_RIGHT, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(START_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(STEAM_LEFT, 8);
	sprite->addKeyframe(STEAM_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(STEAM_LEFT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(STEAM_RIGHT, 8);
	sprite->addKeyframe(STEAM_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STEAM_RIGHT, glm::vec2(0.f, 0.25f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void Steam::update(int deltaTime, int x) {
	if (alive) {
		++cont;
		switch (x) {
		case 0:
			switch (estat) {
			case 0:
				if (sprite->animation() != NOTHING) sprite->changeAnimation(NOTHING);
				if (cont > 100) estat = 1;
				break;
			case 1:
				if (sprite->animation() != START_LEFT) sprite->changeAnimation(START_LEFT);
				if (cont > 200) estat = 2;
				break;
			case 2:
				if (sprite->animation() != STEAM_LEFT) sprite->changeAnimation(STEAM_LEFT);
				if (cont > 300) {
					estat = 0;
					cont = 0;
				}
				break;
			}
			break;
		case 1:
			switch (estat) {
			case 0:
				if (sprite->animation() != NOTHING) sprite->changeAnimation(NOTHING);
				if (cont > 100) estat = 1;
				break;
			case 1:
				if (sprite->animation() != START_RIGHT) sprite->changeAnimation(START_RIGHT);
				if (cont > 200) estat = 2;
				break;
			case 2:
				if (sprite->animation() != STEAM_RIGHT) sprite->changeAnimation(STEAM_RIGHT);
				if (cont > 300) {
					estat = 0;
					cont = 0;
				}
				break;
			}
		default:
			break;
		}
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
	}
}

void Steam::render() {
	if (alive) sprite->render();
}

void Steam::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Steam::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 Steam::getPosition()
{
	return posPJ;
}

bool Steam::isDangerous() {
	if (estat == 2)	return true;
	else return false;
}