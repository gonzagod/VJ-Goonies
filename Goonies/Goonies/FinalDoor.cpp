#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "FinalDoor.h"
#include "Game.h"
#include <crtdbg.h> 



void FinalDoor::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = false;
	spritesheet.loadFromFile("images/FinalDoor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void FinalDoor::update(int deltaTime) {
	if (alive) {
		sprite->changeAnimation(1);	
	}
	else sprite->changeAnimation(0);
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));

}

void FinalDoor::render() {
	sprite->render();
}

void FinalDoor::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void FinalDoor::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 FinalDoor::getPosition()
{
	return posPJ;
}

void FinalDoor::open() {
	alive = true;
}


bool FinalDoor::isAlive() {
	return alive;
}