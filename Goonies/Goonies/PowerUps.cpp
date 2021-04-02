#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "PowerUps.h"
#include "Game.h"
#include <crtdbg.h> 



void PowerUps::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	visible = false;
	spritesheet.loadFromFile("images/PowerUpBag.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void PowerUps::update(int deltaTime) {
	if (visible) {
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
	}
}

void PowerUps::render() {
	if (visible) sprite->render();
}

void PowerUps::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void PowerUps::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 PowerUps::getPosition()
{
	return posPJ;
}

void PowerUps::collect(int x) {
	alive = false;
	visible = false;
	switch (x) {
	case 0:
		//Casc antiestalactites
		Game::instance().powerupHelmet();
		break;
	case 1:
		Game::instance().powerupHyperShoes();
		break;
	case 2:
		Game::instance().powerupBlueSpellbook();
		break;
	case 3:
		Game::instance().powerupGrayRaincoat();
		break;
	case 4:
		Game::instance().powerupYellowRaincoat();
		break;
	default:
		break;
	}
}

void PowerUps::appear() {
	alive = true;
	visible = true;
}

bool PowerUps::catched() {
	return alive;
}

bool PowerUps::isAlive() {
	return visible;
}