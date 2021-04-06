#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Padlock.h"
#include "Game.h"
#include <crtdbg.h> 



void Padlock::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	spritesheet.loadFromFile("images/Objectes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.125), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.375f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void Padlock::update(int deltaTime) {
	if (alive) {
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
	}
}

void Padlock::render() {	
	if (alive) sprite->render();
}

void Padlock::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Padlock::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 Padlock::getPosition()
{
	return posPJ;
}

void Padlock::collect() {

	if (Game::instance().keyStatus())
	{
		Game::instance().removeKey();
		alive = false;
	}
}


bool Padlock::isAlive() {
	return alive;
}