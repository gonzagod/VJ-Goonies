#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
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

enum msxAnimation {
	MSX_LLETRES, MSX_FONS
};

enum estats {
	MSX, MSX2, KONAMI, KONAMI2, LLETRES_GOONIES, GOON, GOONIE1, GOONIE2, GOONIE3, GOONIE4, GOONIE5, GOONIE6, EVIL, STUN_GOON, GOONIE1_GONE, GOONIE2_GONE, GOONIE3_GONE, GOONIE4_GONE, GOONIE5_GONE, GOONIE6_GONE, EVIL_LAUGH, GOON_TURNBACK, PLAY_START, PLAY_START2
};

enum lletres {
	LLETRES0, LLETRES1, LLETRES2, LLETRES3, LLETRES4, LLETRES5, LLETRES6
};

enum PlayStart {
	PLAYSTART
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

void pjLoadingScreen::initMsx(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/MsX.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(256, 256), glm::vec2(1, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MSX_LLETRES, 8);
	sprite->addKeyframe(MSX_LLETRES, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MSX_FONS, 8);
	sprite->addKeyframe(MSX_FONS, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(MSX_LLETRES);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void pjLoadingScreen::initLletres(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/msxLletres.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(256, 16), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(LLETRES0, 8);
	sprite->addKeyframe(LLETRES0, glm::vec2(0.f, 0.0f));
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}

void pjLoadingScreen::initPlayStart(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/PlayStart.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(80, 8), glm::vec2(1, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(PLAYSTART, 8);
	sprite->addKeyframe(PLAYSTART, glm::vec2(0.f, 0.0f));
	sprite->addKeyframe(PLAYSTART, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(PLAYSTART, glm::vec2(0.f, 0.5f));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPJ.x), float(tileMapDispl.y + posPJ.y)));
}
    
void pjLoadingScreen::update(int deltaTime, int numPersonatge, int &estat)
{
	
	switch (numPersonatge) {
		case 0:
			if (estat == MSX) {
				if (sprite->animation() != MSX_FONS) sprite->changeAnimation(MSX_FONS);
				posPJ.x += 8;
				if (posPJ.x == 128) {
					waiting = true;
					endwait = clock() + 2 * CLOCKS_PER_SEC;
					estat = MSX2;
				}
			}
			else if (estat == MSX2) {

				if (waiting) {
					if (clock() > endwait) waiting = false;
				}

				else if (!waiting) {
					estat = KONAMI;
					int level = Game::instance().nextScreen();
				}

			}
			break;

		case 1:
			if (estat == MSX) {
				if (sprite->animation() != MSX_LLETRES) sprite->changeAnimation(MSX_LLETRES);
				posPJ.x -= 8;
			}
			break;

		case 2:
			if (estat == KONAMI) {
				if (sprite->animation() != KONAMI_UP) sprite->changeAnimation(KONAMI_UP);
				posPJ.y -= 2;
				if (posPJ.y == 156) {
					waiting = true;
					endwait = clock() + 2 * CLOCKS_PER_SEC;
					estat = KONAMI2;
				}
			}
			else if (estat == KONAMI2) {
				if (sprite->animation() != KONAMI_SOFT) sprite->changeAnimation(KONAMI_SOFT);

				if (waiting) {
					if (clock() > endwait) waiting = false;
				}

				else if (!waiting) {
					estat = LLETRES_GOONIES;
					int level = Game::instance().nextScreen();
				}
			}
			break;

		case 3:
			if (estat == LLETRES_GOONIES && !waiting) {
				endwait = clock() + 2 * CLOCKS_PER_SEC;
				waiting = true;
			}
			else if (estat == LLETRES_GOONIES && waiting) {
				if (clock() > endwait) {
					waiting = false;
					estat = GOON;
				}
			}
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
					endwait = clock() + 4 * CLOCKS_PER_SEC;
					estat = PLAY_START;
				}
			}
			else if (sprite->animation() != IDLE_GOON) sprite->changeAnimation(IDLE_GOON);
			break;

		case 4:
			if (sprite->animation() != MOVE_RIGHT_GOONIE) sprite->changeAnimation(MOVE_RIGHT_GOONIE);
			posPJ.x += 4;
			if (posPJ.x == (320 - (estat - 6) * 32)) {
				++estat;
				sprite->changeAnimation(IDLE_GOONIE);
			}
			break;
		case 5:
			if (estat >= EVIL && estat < GOONIE6_GONE) {
				if (estat == EVIL) estat = STUN_GOON;
				if (sprite->animation() != MOVE_LEFT_EVIL) sprite->changeAnimation(MOVE_LEFT_EVIL);
				posPJ.x -= 2;
				if (posPJ.x == 320) estat = GOONIE1_GONE;
				if (posPJ.x == 288) estat = GOONIE2_GONE;
				if (posPJ.x == 256) estat = GOONIE3_GONE;
				if (posPJ.x == 224) estat = GOONIE4_GONE;
				if (posPJ.x == 192) estat = GOONIE5_GONE;
				if (posPJ.x == 160) {
					waiting = true;
					endwait = clock() + 2 * CLOCKS_PER_SEC;
					estat = GOONIE6_GONE;
				}
			}
			else if (estat == GOONIE6_GONE) {
				if (sprite->animation() != IDLE_EVIL) sprite->changeAnimation(IDLE_EVIL);
				if (waiting) {
					if (clock() > endwait) waiting = false;
				}

				else if (!waiting) {
					estat = EVIL_LAUGH;
				}

			}
			else if (estat == EVIL_LAUGH) {
				if (sprite->animation() != MOVE_LEFT_EVIL) sprite->changeAnimation(MOVE_LEFT_EVIL);
				posPJ.x -= 2;
				if (posPJ.x == 100) posPJ.x -= 500;
			}
			break;
		
		case 6:
			if (estat == MSX2) {
				sprite->changeAnimation(LLETRES0);
				posPJ.x = 136;
				posPJ.y = 272;
			}
			break;

		case 7:
			if (estat == PLAY_START) {
				if (!waiting) {
					posPJ.x = 216;
					posPJ.y = 272;
					endwait = clock() + 2 * CLOCKS_PER_SEC;
					waiting = true;
				}

				else if (waiting && clock() > endwait) {
					if (Game::instance().getKey(32)) estat = PLAY_START2;
				}
				if (sprite->animation() != PLAYSTART) sprite->changeAnimation(PLAYSTART);
			}
			else if (estat == PLAY_START2) {
				int level = Game::instance().nextScreen();
			}
			break;

		default:
			break;

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

