#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "TheEnd.h"
#include "Game.h"
#include <crtdbg.h> 



void TheEnd::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	spritesheet.loadFromFile("images/gameWin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(512, 320), glm::vec2(1, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 4);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void TheEnd::update(int deltaTime) {
	
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void TheEnd::render() {
	if (alive) sprite->render();
}

void TheEnd::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void TheEnd::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}