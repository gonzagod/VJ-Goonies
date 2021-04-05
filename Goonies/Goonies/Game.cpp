#include <irrKlang.h>
using namespace irrklang;

#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "windows.h"
#include <crtdbg.h> 

ISoundEngine *SoundEngine = createIrrKlangDevice();

int chrono = 0;

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
	++chrono;

	return bPlay;
}

int Game::nextScreen()
{
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

void Game::play_power_up()
{
	SoundEngine->play2D("sounds/power_up.wav", false);
}

void Game::play_parry()
{
	SoundEngine->play2D("sounds/parry.wav", false);
}

void Game::play_skull_spawn()
{
	SoundEngine->play2D("sounds/skull_spawn.wav", false);
}

void Game::play_damage_player()
{
	SoundEngine->play2D("sounds/damage.wav", false);
}

void Game::play_rescue_goonie()
{
	SoundEngine->stopAllSounds();
	SoundEngine->play2D("sounds/05_-_Goonies_-_MSX_-_Rescued_Goonie.wav", false);
}

void Game::play_level1_3_cut()
{
	SoundEngine->stopAllSounds();
	SoundEngine->play2D("sounds/level1_3_cut.wav", true);
}

void Game::play_portal()
{
	SoundEngine->stopAllSounds();
	SoundEngine->play2D("sounds/portal.wav", false);
}

void Game::play_level_blue()
{
	SoundEngine->stopAllSounds();
	SoundEngine->play2D("sounds/04_-_Goonies_-_MSX_-_Stage_Music.wav", true);
}

void Game::play_shot()
{
	SoundEngine->play2D("sounds/shot.wav", false);
}

void Game::play_low_health()
{
	SoundEngine->play2D("sounds/low_health.wav", false);
}

void Game::play_game_over()
{
	SoundEngine->stopAllSounds();
	SoundEngine->play2D("sounds/game_over.wav", false);
}

void Game::play_the_end()
{
	SoundEngine->stopAllSounds();
	SoundEngine->play2D("sounds/the_end.wav", false);
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





