#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "pjLoadingScreen.h"
#include "Game.h"
#include <crtdbg.h> 


enum pjLoadingScreenAnimations
{
	MOVE_LEFT, MOVE_RIGHT, IDLE, STUN
};

void pjLoadingScreen::initGoonie(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/PJ_inici.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0.6f, 0.75f));


	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void pjLoadingScreen::initGoon(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/PJ_inici.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 0.25f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.8f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.6f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.8f, 0.f));

	sprite->setAnimationSpeed(STUN, 8);
	sprite->addKeyframe(STUN, glm::vec2(0.4f, 0.75f));
	sprite->addKeyframe(STUN, glm::vec2(0.8f, 0.75f));

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0.f, 0.0f));


	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void pjLoadingScreen::initEvil(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/PJ_inici.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.8f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(IDLE, 8);
	sprite->addKeyframe(IDLE, glm::vec2(0.f, 0.75f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void pjLoadingScreen::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void pjLoadingScreen::render()
{
	sprite->render();
}

void pjLoadingScreen::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void pjLoadingScreen::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}




