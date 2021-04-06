#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Goonie.h"
#include "Game.h"
#include <crtdbg.h> 

enum tipusObjecte {
	POCIO1, POCIO2, POCIO3, GOONIE1, GOONIE2, GOONIE3
};

void Goonie::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = false;
	spritesheet.loadFromFile("images/ObjectesPorta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(POCIO1, 8);
	sprite->addKeyframe(POCIO1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(POCIO2, 8);
	sprite->addKeyframe(POCIO2, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(POCIO3, 8);
	sprite->addKeyframe(POCIO3, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(GOONIE1, 8);
	sprite->addKeyframe(GOONIE1, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(GOONIE2, 8);
	sprite->addKeyframe(GOONIE2, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(GOONIE3, 8);
	sprite->addKeyframe(GOONIE3, glm::vec2(0.25f, 0.5f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void Goonie::update(int deltaTime, int x) {
	if (alive) {
		sprite->changeAnimation(x);
		}
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void Goonie::render() {
	if (alive) sprite->render();
}

void Goonie::appear() {
	alive = true;
}

void Goonie::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Goonie::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 Goonie::getPosition()
{
	return posPJ;
}

void Goonie::rescue() {
	if (sprite->animation() < 3) {
		Game::instance().play_power_up();
		Game::instance().modifyHP(4);
		Game::instance().addPoints(500);
	}
	else {
		Game::instance().play_rescue_goonie();
		Game::instance().addGoonies();
	}
	alive = false;
}


bool Goonie::isAlive() {
	return alive;
}