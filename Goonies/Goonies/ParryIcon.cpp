#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "ParryIcon.h"
#include "Game.h"
#include <crtdbg.h> 


void ParryIcon::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	alive = true;
	bullet_icon = false;
	spritesheet.loadFromFile("images/parry_icon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(16);

	//0
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	//1
	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.2f, 0.f));

	//2
	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.4f, 0.f));

	//3
	sprite->setAnimationSpeed(3, 8);
	sprite->addKeyframe(3, glm::vec2(0.6f, 0.f));

	//4 
	sprite->setAnimationSpeed(4, 8);
	sprite->addKeyframe(4, glm::vec2(0.f, 0.25f));

	//5
	sprite->setAnimationSpeed(5, 8);
	sprite->addKeyframe(5, glm::vec2(0.2f, 0.25f));

	//6
	sprite->setAnimationSpeed(6, 8);
	sprite->addKeyframe(6, glm::vec2(0.4f, 0.25f));

	//7
	sprite->setAnimationSpeed(7, 8);
	sprite->addKeyframe(7, glm::vec2(0.6f, 0.25f));

	//8
	sprite->setAnimationSpeed(8, 8);
	sprite->addKeyframe(8, glm::vec2(0.f, 0.5f));

	//9
	sprite->setAnimationSpeed(9, 8);
	sprite->addKeyframe(9, glm::vec2(0.2f, 0.5f));

	//10
	sprite->setAnimationSpeed(10, 8);
	sprite->addKeyframe(10, glm::vec2(0.4f, 0.5f));

	//11
	sprite->setAnimationSpeed(11, 8);
	sprite->addKeyframe(11, glm::vec2(0.6f, 0.5f));

	//12
	sprite->setAnimationSpeed(12, 8);
	sprite->addKeyframe(12, glm::vec2(0.f, 0.75f));

	//13
	sprite->setAnimationSpeed(13, 8);
	sprite->addKeyframe(13, glm::vec2(0.2f, 0.75f));

	//14
	sprite->setAnimationSpeed(14, 8);
	sprite->addKeyframe(14, glm::vec2(0.4f, 0.75f));
	sprite->addKeyframe(14, glm::vec2(0.8f, 0.f));
	sprite->addKeyframe(14, glm::vec2(0.8f, 0.25f));
	sprite->addKeyframe(14, glm::vec2(0.8f, 0.5f));

	//15
	sprite->setAnimationSpeed(15, 8);
	sprite->addKeyframe(15, glm::vec2(0.6f, 0.75f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}



void ParryIcon::update(int deltaTime, int x) {
	if (alive) {
		if (!bullet_icon) {
			int anim = x/8;
			if(sprite->animation() != anim) sprite->changeAnimation(anim);
		}
		else {
			sprite->changeAnimation(15);
		}
		
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
	}


}

void ParryIcon::render() {
	if (alive) sprite->render();
}

void ParryIcon::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void ParryIcon::setPosition(const glm::vec2& pos)
{
	posPJ = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

glm::ivec2 ParryIcon::getPosition()
{
	return posPJ;
}

bool ParryIcon::isAlive() {
	return alive;
}

void ParryIcon::bullet(bool b) {
	bullet_icon = b;
}