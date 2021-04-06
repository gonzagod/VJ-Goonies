#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Key.h"
#include "Game.h"
#include <crtdbg.h> 


	
void Key::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	spritesheet.loadFromFile("images/Objectes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.125), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.75f, 0.125f));
	sprite->addKeyframe(0, glm::vec2(0.75f, 0.25f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void Key::update(int deltaTime, int x) {
	switch (x) {
	case 0:
		if (alive) {
			sprite->update(deltaTime);
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
		}
		break;
	case 1:
		if (Game::instance().keyStatus()) {
			sprite->update(deltaTime);
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
		}
		break;
	default:
		break;
	}
}

void Key::render(int x) {
	switch (x) {
	case 0:
		if (alive) sprite->render();
		break;
	case 1:
		if (Game::instance().keyStatus()) sprite->render();
		break;
	default:
		break;
	}
}

void Key::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Key::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 Key::getPosition()
{
	return posPJ;
}

void Key::collect() {

	if (!Game::instance().keyStatus())
	{
		Game::instance().addKey();
		alive = false;
	}
}


bool Key::isAlive() {
	return alive;
}