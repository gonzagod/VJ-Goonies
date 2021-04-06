#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Cascade.h"
#include "Game.h"
#include <crtdbg.h>

enum CascadeAnims
{
	FALLING, FIRST, LAST, FINAL,
};

void Cascade::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {

	alive = false;
	change = false;
	max_y = 0;
	first = false;
	cont = 0;
	cont_falling = 0;
	cont_waiting = 0;
	size = 0;
	time_cascade = 60;
	init_y = 0;

	spritesheet.loadFromFile("images/TheGoonies-MapTiles2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 16), glm::vec2(0.1875, 0.0625), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(FALLING, 8);
	sprite->addKeyframe(FALLING, glm::vec2(0.8125f, 0.375f));
	sprite->addKeyframe(FALLING, glm::vec2(0.8125f, 0.5f));

	sprite->setAnimationSpeed(FIRST, 8);
	sprite->addKeyframe(FIRST, glm::vec2(0.3125f, 0.4375f));

	sprite->setAnimationSpeed(LAST, 8);
	sprite->addKeyframe(LAST, glm::vec2(0.3125f, 0.375f));

	sprite->setAnimationSpeed(FINAL, 8);
	sprite->addKeyframe(FINAL, glm::vec2(0.8125f, 0.4375f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCascade.x), float(tileMapDispl.y + posCascade.y)));
}

void Cascade::update(int deltaTime) {
	sprite->update(deltaTime);
	if (sub_y == 0) {
		//_RPT2(0, "cascade %d con cont_waiting = %d\n", sub_y, cont_waiting);
	}
	if (cont_waiting == sub_y) {
		//_RPT1(0, "cascade %d alive\n", sub_y);
		alive = true;
	}
	if (alive && cont % 2 == 0) {
		if (cont_falling < time_cascade - sub_y * 2) {
			if (posCascade.y < max_y) {
				if (sub_y == 0 && sprite->animation() != FIRST) sprite->changeAnimation(FIRST);
				else if (sub_y > 0 && sprite->animation() != FALLING) sprite->changeAnimation(FALLING);
				posCascade.y += 16;
			}
			else if (sub_y == 0 && sprite->animation() != FINAL) sprite->changeAnimation(FINAL);
		}
		else {
			if (cont_falling == (time_cascade - sub_y * 2) + 1) {
				sprite->changeAnimation(LAST);
			}
			if (!first && (cont_falling == (time_cascade - sub_y * 2) + 2)) {
				alive = false;
			}
			else if (cont_falling > time_cascade - sub_y * 2 && first) {
				alive = false;
			}
		}
	}
	++cont;
	if (cont % 2 == 0) {
		++cont_waiting;
		if (alive) ++cont_falling;
	}
	if (cont == 200) {
		cont_waiting = 0;
		cont = 0;
		cont_falling = 0;
		posCascade.y = init_y;
		sprite->changeAnimation(FALLING);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCascade.x), float(tileMapDispl.y + posCascade.y)));
}

void Cascade::render()
{
	if (alive) {
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCascade.x), float(tileMapDispl.y + posCascade.y)));
		sprite->render();
	}
}

void Cascade::setPosition(const glm::vec2 &pos)
{
	posCascade = pos;
	init_y = pos.y;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCascade.x), float(tileMapDispl.y + posCascade.y)));
}

glm::ivec2 Cascade::getPosition()
{
	return posCascade;
}

bool Cascade::is_Alive()
{
	return alive;
}

void Cascade::player_hit() {
	alive = false;
}

void Cascade::setMax_y(int y) {
	max_y = y - sub_y*16;
}

void Cascade::setSub_y(int y)
{
	sub_y = y;
}

void Cascade::isFirst()
{
	first = true;
}

void Cascade::setSize(int m) {
	size = m;
}
