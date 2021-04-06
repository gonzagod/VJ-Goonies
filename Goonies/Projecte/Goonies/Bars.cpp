#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "Bars.h"
#include "Game.h"
#include <crtdbg.h> 


void Bars::initHealthBar(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/HealthBar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(160, 14), glm::vec2(1, 0.04), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(21);

	for (int i = 0; i < 22; ++i) {
		sprite->setAnimationSpeed(i, 8);
		sprite->addKeyframe(i, glm::vec2(0.f, 0.8f - 0.04f*i));
	}

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void Bars::initExpBar(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/ExpBar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(160, 14), glm::vec2(1, 0.04), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(21);

	for (int i = 0; i < 21; ++i) {
		sprite->setAnimationSpeed(i, 8);
		sprite->addKeyframe(i, glm::vec2(0.f, 0.8f - 0.04f*i));
	}

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void Bars::update(int deltaTime, int health) {

	sprite->changeAnimation(health);

	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void Bars::render() {
	sprite->render();
}

void Bars::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bars::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

