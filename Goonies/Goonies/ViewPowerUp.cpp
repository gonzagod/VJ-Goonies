#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "ViewPowerUp.h"
#include "Game.h"
#include <crtdbg.h> 



void ViewPowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	spritesheet.loadFromFile("images/PowerUps.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	//Gray Raincoat
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	//Helmet
	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.25f));

	//HyperShoes
	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.f, 0.75f));

	//YellowRaincoat
	sprite->setAnimationSpeed(3, 8);
	sprite->addKeyframe(3, glm::vec2(0.5f, 0.f));

	//BlueSpellBook 
	sprite->setAnimationSpeed(4, 8);
	sprite->addKeyframe(4, glm::vec2(0.5f, 0.5f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void ViewPowerUp::update(int deltaTime, int x) {
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
		case 3:
			sprite->changeAnimation(3);
			break;
		case 4:
			sprite->changeAnimation(4);
			break;
		default:
			break;
		}
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
	}


}

void ViewPowerUp::render() {
	if (alive) sprite->render();
}

void ViewPowerUp::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void ViewPowerUp::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 ViewPowerUp::getPosition()
{
	return posPJ;
}

void ViewPowerUp::open() {
	alive = false;
}


bool ViewPowerUp::isAlive() {
	return alive;
}