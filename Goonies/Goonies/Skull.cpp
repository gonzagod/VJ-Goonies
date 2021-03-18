#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Skull.h"
#include "Game.h"
#include <crtdbg.h> 


int cont = 0;

enum SkullAnims
{
	MOVE_LEFT, MOVE_RIGHT, RESPAWN, DEAD
};

void Skull::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Skull.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33, 0.33), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.66f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.33f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.33f, 0.f));

	sprite->setAnimationSpeed(RESPAWN, 3);
	sprite->addKeyframe(RESPAWN, glm::vec2(0.33f, 0.33f));
	sprite->addKeyframe(RESPAWN, glm::vec2(0.66f, 0.33f));

	sprite->setAnimationSpeed(DEAD, 8);
	sprite->addKeyframe(DEAD, glm::vec2(0.f, 0.66f));

	sprite->changeAnimation(RESPAWN);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSkull.x), float(tileMapDispl.y + posSkull.y)));
}

void Skull::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() == RESPAWN && cont > 100) sprite->changeAnimation(MOVE_LEFT);
	else if (sprite->animation() == RESPAWN) ++cont;
	else if (sprite->animation() == MOVE_RIGHT) {
		if (map->collisionMoveRight(posSkull, glm::ivec2(32, 32))) sprite->changeAnimation(MOVE_LEFT);
		else posSkull.x += 2;
	}
	else if (sprite->animation() == MOVE_LEFT) {
		if (map->collisionMoveLeft(posSkull, glm::ivec2(32, 32))) sprite->changeAnimation(MOVE_RIGHT);
		else posSkull.x -= 2;
	}
	else sprite->changeAnimation(DEAD);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSkull.x), float(tileMapDispl.y + posSkull.y)));

	//_RPT1(0,"%d\n", posSkull.x);
	//_RPT1(0, "%d\n", posSkull.y);
}

void Skull::render()
{
	sprite->render();
}

void Skull::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Skull::setPosition(const glm::vec2& pos)
{
	posSkull = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSkull.x), float(tileMapDispl.y + posSkull.y)));
}




