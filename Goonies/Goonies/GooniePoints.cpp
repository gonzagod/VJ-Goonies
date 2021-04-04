#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "GooniePoints.h"
#include "Game.h"
#include <crtdbg.h> 



void GooniePoints::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	spritesheet.loadFromFile("images/GooniePoints.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 32), glm::vec2(1,0.125), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(7);

	for (int i = 0; i < 7; ++i) {
		sprite->setAnimationSpeed(i, 4);
		sprite->addKeyframe(i, glm::vec2(0.f, 0.75f -i*0.125f));
		if (i == 6) sprite->addKeyframe(i, glm::vec2(0.f, 0.75f));
	}

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void GooniePoints::update(int deltaTime, int gooniePoints) {
	if (sprite->animation() != gooniePoints) sprite->changeAnimation(gooniePoints);
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void GooniePoints::render() {
	if (alive) sprite->render();
}

void GooniePoints::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void GooniePoints::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 GooniePoints::getPosition()
{
	return posPJ;
}

void GooniePoints::collect() {

	if (!Game::instance().keyStatus())
	{
		Game::instance().addKey();
		alive = false;
	}
}


bool GooniePoints::isAlive() {
	return alive;
}