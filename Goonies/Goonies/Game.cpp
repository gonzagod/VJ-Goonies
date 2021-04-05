#include <irrKlang.h>
using namespace irrklang;

#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <crtdbg.h> 

ISoundEngine *SoundEngine = createIrrKlangDevice();

void Game::init()
{
	bPlay = true;
	points = 0;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
	
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);

	return bPlay;
}

int Game::nextScreen()
{
	//SoundEngine->play2D("sounds/08_-_Goonies_-_MSX_-_Stage_Clear", false);
	return scene.nextScreen();
}

int Game::prevScreen()
{
	return scene.prevScreen();
}

int Game::goToScreen(int level) {
	return scene.goToScreen(level);
}

int Game::addPoints(int points) {
	return scene.addPoints(points);
}

int Game::modifyHP(int healthPoints) {
	return scene.modifyHP(healthPoints);
}

int Game::modifyExp(int expPoints) {
	return scene.modifyExp(expPoints);
}

int Game::addGoonies() {
	return scene.addGoonies();
}

bool Game::addKey() {
	SoundEngine->play2D("sounds/key.wav", false);
	return scene.addKey();
}

bool Game::removeKey() {
	SoundEngine->play2D("sounds/paddlock.wav", false);
	return scene.removeKey();
}

bool Game::keyStatus() {
	return scene.keyStatus();
}

void Game::player_shoot(bool side)
{
	scene.player_shoots(side);
}

void Game::play_goonies1(bool play)
{
	if (play) SoundEngine->play2D("sounds/01_-_Goonies_-_MSX_-_Title.wav", true);
	else SoundEngine->stopAllSounds();
}

void Game::play_sound1_3(bool play)
{
	if(play) SoundEngine->play2D("sounds/02_-_Goonies_-_MSX_-_The_Goonies_'R'_Good_Enough.wav", true);
	else SoundEngine->stopAllSounds();
}

void Game::play_jump()
{
	SoundEngine->play2D("sounds/jump.wav", false);
}

void Game::play_skull_die()
{
	SoundEngine->play2D("sounds/skull_die.wav", false);
}

void Game::play_potion()
{
	SoundEngine->play2D("sounds/potion.wav", false);
}

bool Game::noHealth() {
	return scene.noHealth();
}

void Game::powerupHelmet() {
	scene.powerupHelmet();
}

void Game::powerupGrayRaincoat() {
	scene.powerupGrayRaincoat();
}

void Game::powerupHyperShoes() {
	scene.powerupHyperShoes();
}

void Game::powerupYellowRaincoat() {
	scene.powerupYellowRaincoat();
}

void Game::powerupBlueSpellbook() {
	scene.powerupBlueSpellbook();
}

void Game::gameOver() {
	scene.gameOver(0);
}

void Game::gameWin() {
	scene.gameWin();
}

int Game::howManyGoonies() {
	return scene.howManyGoonies();
}

void Game::restartGame() {
	if (points > higherPuntuation) higherPuntuation = points;
	points = 0;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.restartGame();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::updateEnemyMap()
{
	scene.updateEnemyMap();
}





