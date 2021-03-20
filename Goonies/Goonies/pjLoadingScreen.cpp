#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "pjLoadingScreen.h"
#include "Game.h"
#include <crtdbg.h> 


enum pjLoadingScreenAnimations
{
	MOVE_LEFT_GOONIE, MOVE_LEFT_GOON, MOVE_LEFT_EVIL, MOVE_RIGHT_GOONIE, MOVE_RIGHT_GOON, MOVE_RIGHT_EVIL, IDLE_GOONIE, IDLE_GOON, IDLE_EVIL, STUN
};

enum logoAnimation {
	KONAMI_UP, KONAMI_SOFT
};


enum estats {
	MSX, KONAMI, KONAMI2, GOON, GOONIE1, GOONIE2, GOONIE3, GOONIE4, GOONIE5, GOONIE6, EVIL, STUN_GOON, GOONIE1_GONE, GOONIE2_GONE, GOONIE3_GONE, GOONIE4_GONE, GOONIE5_GONE, GOONIE6_GONE, EVIL_LAUGH, GOON_TURNBACK, PLAY_START
};

void pjLoadingScreen::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/PJ_inici.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(MOVE_RIGHT_GOONIE, 8);
	sprite->addKeyframe(MOVE_RIGHT_GOONIE, glm::vec2(0.2f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT_GOONIE, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(IDLE_GOONIE, 8);
	sprite->addKeyframe(IDLE_GOONIE, glm::vec2(0.6f, 0.75f));

	sprite->setAnimationSpeed(MOVE_LEFT_EVIL, 8);
	sprite->addKeyframe(MOVE_LEFT_EVIL, glm::vec2(0.6f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT_EVIL, glm::vec2(0.4f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT_EVIL, 8);
	sprite->addKeyframe(MOVE_RIGHT_EVIL, glm::vec2(0.8f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT_EVIL, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(IDLE_EVIL, 8);
	sprite->addKeyframe(IDLE_EVIL, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(MOVE_RIGHT_GOON, 8);
	sprite->addKeyframe(MOVE_RIGHT_GOON, glm::vec2(0.4f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT_GOON, glm::vec2(0.6f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT_GOON, glm::vec2(0.8f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT_GOON, glm::vec2(0.6f, 0.25f));

	sprite->setAnimationSpeed(MOVE_LEFT_GOON, 8);
	sprite->addKeyframe(MOVE_LEFT_GOON, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT_GOON, glm::vec2(0.8f, 0.f));
	sprite->addKeyframe(MOVE_LEFT_GOON, glm::vec2(0.6f, 0.f));
	sprite->addKeyframe(MOVE_LEFT_GOON, glm::vec2(0.8f, 0.f));

	sprite->setAnimationSpeed(STUN, 8);
	sprite->addKeyframe(STUN, glm::vec2(0.4f, 0.75f));
	sprite->addKeyframe(STUN, glm::vec2(0.8f, 0.75f));

	sprite->setAnimationSpeed(IDLE_GOON, 8);
	sprite->addKeyframe(IDLE_GOON, glm::vec2(0.f, 0.0f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void pjLoadingScreen::initKonami(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

	spritesheet.loadFromFile("images/Konami.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 128), glm::vec2(1, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(KONAMI_UP, 8);
	sprite->addKeyframe(KONAMI_UP, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(KONAMI_SOFT, 8);
	sprite->addKeyframe(KONAMI_SOFT, glm::vec2(0.f, 0.f));
	
	sprite->changeAnimation(KONAMI_UP);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
	
	}

void pjLoadingScreen::update(int deltaTime, int numPersonatge, int &estat)
{
	if (numPersonatge == 0) {
			if (estat == KONAMI) {
			if (sprite->animation() != KONAMI_UP) sprite->changeAnimation(KONAMI_UP);
			posPJ.y -= 2;
			if (posPJ.y == 108) estat = KONAMI2;
		}
		else if (estat == KONAMI2) {
			if (sprite->animation() != KONAMI_SOFT) sprite->changeAnimation(KONAMI_SOFT);
			cont++;
			if (cont == 100) {
				estat = GOON;
				int level = Game::instance().nextScreen();
			}
		}
	}
	else if (numPersonatge == 1) {
		if (estat == GOON) {
			if (sprite->animation() != MOVE_RIGHT_GOON) sprite->changeAnimation(MOVE_RIGHT_GOON);
			posPJ.x += 4;
			if (posPJ.x == 360) estat = GOONIE1;
		}
		else if (estat >= STUN_GOON && estat < EVIL_LAUGH) {
			if (sprite->animation() != STUN) sprite->changeAnimation(STUN);
		}
		else if (estat == EVIL_LAUGH) {
			if (sprite->animation() != MOVE_LEFT_GOON) sprite->changeAnimation(MOVE_LEFT_GOON);
			posPJ.x -= 4;
			if (posPJ.x == 100) {
				estat == PLAY_START;
				int level = Game::instance().nextScreen();
			}
		}
		else if (sprite->animation() != IDLE_GOON) sprite->changeAnimation(IDLE_GOON);
	}
	else if (numPersonatge == 2) {
		if (estat == GOONIE1) {
			if (!moved) {
				posPJ.x += 188;
				moved = true;
			}
			if (sprite->animation() != MOVE_RIGHT_GOONIE) sprite->changeAnimation(MOVE_RIGHT_GOONIE);
			posPJ.x += 4;
			if (posPJ.x == 320) estat = GOONIE2;
		}
		else if (sprite->animation() != IDLE_GOONIE) sprite->changeAnimation(IDLE_GOONIE);
		else if (estat == GOONIE1_GONE) posPJ.x -= 500;
	}
	else if (numPersonatge == 3) {
		if (estat == GOONIE2) {
			if (!moved) {
				posPJ.x += 188;
				moved = true;
			}
			if (sprite->animation() != MOVE_RIGHT_GOONIE) sprite->changeAnimation(MOVE_RIGHT_GOONIE);
			posPJ.x += 4;
			if (posPJ.x == 288) estat = GOONIE3;
		}
		else if (sprite->animation() != IDLE_GOONIE) sprite->changeAnimation(IDLE_GOONIE);
		else if (estat == GOONIE2_GONE) posPJ.x -= 500;
	}
	else if (numPersonatge == 4) {
		if (estat == GOONIE3) {
			if (!moved) {
				posPJ.x += 188;
				moved = true;
			}
			if (sprite->animation() != MOVE_RIGHT_GOONIE) sprite->changeAnimation(MOVE_RIGHT_GOONIE);
			posPJ.x += 4;
			if (posPJ.x == 256) estat = GOONIE4;
		}
		else if (sprite->animation() != IDLE_GOONIE) sprite->changeAnimation(IDLE_GOONIE);
		else if (estat == GOONIE3_GONE) posPJ.x -= 500;
	}
	else if (numPersonatge == 5) {
		if (estat == GOONIE4) {
			if (!moved) {
				posPJ.x += 188;
				moved = true;
			}
			if (sprite->animation() != MOVE_RIGHT_GOONIE) sprite->changeAnimation(MOVE_RIGHT_GOONIE);
			posPJ.x += 4;
			if (posPJ.x == 224) estat = GOONIE5;
		}
		else if (sprite->animation() != IDLE_GOONIE) sprite->changeAnimation(IDLE_GOONIE);
		else if (estat == GOONIE4_GONE) posPJ.x -= 500;

	}
	else if (numPersonatge == 6) {
		if (estat == GOONIE5) {
			if (!moved) {
				posPJ.x += 188;
				moved = true;
			}
			if (sprite->animation() != MOVE_RIGHT_GOONIE) sprite->changeAnimation(MOVE_RIGHT_GOONIE);
			posPJ.x += 4;
			if (posPJ.x == 192) estat = GOONIE6;
		}
		else if (sprite->animation() != IDLE_GOONIE) sprite->changeAnimation(IDLE_GOONIE);
		else if (estat == GOONIE5_GONE) posPJ.x -= 500;
	}
	else if (numPersonatge == 7) {
		if (estat == GOONIE6) {
			if (!moved) {
				posPJ.x += 188;
				moved = true;
			}
			if (sprite->animation() != MOVE_RIGHT_GOONIE) sprite->changeAnimation(MOVE_RIGHT_GOONIE);
			posPJ.x += 4;
			if (posPJ.x == 160) estat = EVIL;
		}
		else if (sprite->animation() != IDLE_GOONIE) sprite->changeAnimation(IDLE_GOONIE);
		else if (estat == GOONIE6_GONE) posPJ.x -= 500;
	}
	else if (numPersonatge == 8) {
		if (estat >= EVIL && estat < GOONIE6_GONE) {
			if (!moved) {
				posPJ.x += 528;
				moved = true;
			}
			estat = STUN_GOON;
			if (sprite->animation() != MOVE_LEFT_EVIL) sprite->changeAnimation(MOVE_LEFT_EVIL);
			posPJ.x -= 2;
			if (posPJ.x == 320) estat = GOONIE1_GONE;
			if (posPJ.x == 288) estat = GOONIE2_GONE;
			if (posPJ.x == 256) estat = GOONIE3_GONE;
			if (posPJ.x == 224) estat = GOONIE4_GONE;
			if (posPJ.x == 192) estat = GOONIE5_GONE;
			if (posPJ.x == 160) estat = GOONIE6_GONE;
		}
		else if (estat == GOONIE6_GONE) {
			cont++;
			if (sprite->animation() != IDLE_EVIL) sprite->changeAnimation(IDLE_EVIL);
			if (cont == 100) estat = EVIL_LAUGH;
		}
		else if (estat == EVIL_LAUGH) {
			if (sprite->animation() != MOVE_LEFT_EVIL) sprite->changeAnimation(MOVE_LEFT_EVIL);
			posPJ.x -= 2;
			if (posPJ.x == 100) posPJ.x -= 500;
		}

	}

	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
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

