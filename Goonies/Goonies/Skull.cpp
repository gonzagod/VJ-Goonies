#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Skull.h"
#include "Game.h"
#include <crtdbg.h> 


enum SkullAnims
{
	MOVE_LEFT, MOVE_RIGHT, RESPAWN, DEAD
};

int jump_array[20] = { 5,5,5,4,4,4,3,2,1,0,0,1,2,3,4,4,4,5,5,5 };

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

	alive = true;
	dying = false;
	ready = false;
	cont_spawn = 0;
	cont_dying = 0;
	first_move = false; //true -> RIGHT || false -> LEFT
	jumper = false;
	jumping_cont = 0;
	max_x = 0;
	min_x = 0;
}

void Skull::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() != RESPAWN && sprite->animation() != DEAD && alive) ready = true;
	if (sprite->animation() == RESPAWN && cont_spawn > 75) {
		if (first_move) sprite->changeAnimation(MOVE_RIGHT);
		else sprite->changeAnimation(MOVE_LEFT);
	}
	else if (sprite->animation() == RESPAWN) ++cont_spawn;
	else if (sprite->animation() == MOVE_RIGHT) {
		if (posSkull.x >= max_x) sprite->changeAnimation(MOVE_LEFT);
		else posSkull.x += 3;
	}
	else if (sprite->animation() == MOVE_LEFT) {
		if (posSkull.x <= min_x) sprite->changeAnimation(MOVE_RIGHT);
		else posSkull.x -= 3;
	}

	if (jumper && ready) {
		if (jumping_cont > 19) jumping_cont = 0;
		if (jumping_cont > 10) posSkull.y += jump_array[jumping_cont];
		else posSkull.y -= jump_array[jumping_cont];
		++jumping_cont;
	}

	if (cont_dying == 16) {
		cont_dying = 0;
		alive = false;
		dying = false;
		ready = false;
	}
	if (dying) ++cont_dying;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSkull.x), float(tileMapDispl.y + posSkull.y)));

	
	//_RPT1(0,"%d\n", posSkull.x);
	//_RPT1(0, "%d\n", posSkull.y);
}

void Skull::render()
{
	if (alive) sprite->render();
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

glm::ivec2 Skull::getPosition()
{
	return posSkull;
}

void Skull::die() {
	Game::instance().addPoints(50);
	Game::instance().modifyExp(2);
	dying = true;
	sprite->changeAnimation(DEAD);
}

bool Skull::isAlive() {
	return (alive && !dying);
}

bool Skull::isReady() {
	return ready;
}

void Skull::setFirstMove(bool side) {
	first_move = side;
}

void Skull::setJumper(bool jump)
{
	jumper = jump;
}

void Skull::setDistance(int min, int max) {
	min_x = min;
	max_x = max;
}

