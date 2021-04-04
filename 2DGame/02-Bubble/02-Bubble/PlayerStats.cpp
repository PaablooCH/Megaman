#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerStats.h"

#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_HEIGHT 10

#define HEALTH_ICON_WIDTH 10
#define HEALTH_ICON_HEIGHT 10

/*
enum HealthState
{
	FULL1, NINET1, EIGHTE1, SEVENT1, SIXT1, FIF1, FOURT1, THIR1, TWE1, ELE1, TEN1, NINE1, EIGHT1, SEVEN1, SIX1, FIVE1, FOUR1, THREE1, TWO1, ONE1
} health_states;

enum ExpState
{
	FULL2, NINET2, EIGHTE2, SEVENT2, SIXT2, FIF2, FOURT2, THIR2, TWE2, ELE2, TEN2, NINE2, EIGHT2, SEVEN2, SIX2, FIVE2, FOUR2, THREE2, TWO2, ONE2
} exp_states;
*/
enum Anims
{
	BLOCK, BLOCK2, BLOCK3, BLOCK4, BLOCK5, BLOCK6, BLOCK7
};

PlayerStats::~PlayerStats()
{
	delete spriteHeart;
	spriteHeart = nullptr;
	delete spriteExp;
	spriteExp = nullptr;
	delete spriteHealth;
	spriteHealth = nullptr;
	delete spriteExpBar;
	spriteExpBar = nullptr;
	delete spriteKey;
	spriteKey = nullptr;
	delete spriteNumberKey;
	spriteNumberKey = nullptr;
	delete spriteNumberBull;
	spriteNumberBull = nullptr;
	delete spriteX;
	spriteX = nullptr;
	delete spritePowerUp;
	spritePowerUp = nullptr;
	delete spriteGirlsRescued;
	spriteGirlsRescued = nullptr;
	delete gRescued;
	gRescued = nullptr;
	delete powerUp;
	powerUp = nullptr;
}

void PlayerStats::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	//health_states = FULL1;
	//exp_states = FULL2;

	spritesheet.loadFromFile("images/HUD.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteHeart = Sprite::createSprite(glm::ivec2(HEALTH_ICON_WIDTH, HEALTH_ICON_HEIGHT), glm::vec2(78.f / 2000.f, 75.f / 480.f), &spritesheet, &shaderProgram);
	spriteHeart->setNumberAnimations(1);

	spriteHeart->setAnimationSpeed(BLOCK, 1);
	spriteHeart->addKeyframe(BLOCK, glm::vec2(162.f / 2000.f, 323.f / 480.f));

	spriteHeart->changeAnimation(0);
	tileMapDispl = tileMapPos;
	posHeart.x = tileMapDispl.x;
	posHeart.y = tileMapDispl.y;
	spriteHeart->setPosition(posHeart);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteExp = Sprite::createSprite(glm::ivec2(HEALTH_ICON_WIDTH, HEALTH_ICON_HEIGHT), glm::vec2(64.f / 2000.f, 64.f / 480.f), &spritesheet, &shaderProgram);
	spriteExp->setNumberAnimations(1);

	spriteExp->setAnimationSpeed(BLOCK, 1);
	spriteExp->addKeyframe(BLOCK, glm::vec2(88.f / 2000.f, 329.f / 480.f));

	spriteExp->changeAnimation(0);
	posExp.x = tileMapDispl.x;
	posExp.y = HEALTH_BAR_HEIGHT + 4;
	spriteExp->setPosition(posExp);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spriteHealth = Sprite::createSprite(glm::ivec2(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT), glm::vec2(55.f / 2000.f, 77.f / 480.f), &spritesheet, &shaderProgram);
	spriteHealth->setNumberAnimations(1);

	spriteHealth->setAnimationSpeed(BLOCK, 1);
	spriteHealth->addKeyframe(BLOCK, glm::vec2(944.f / 2000.f, 160.f / 480.f));

	spriteHealth->changeAnimation(0);
	posHealthBar.x = tileMapDispl.x + HEALTH_ICON_WIDTH + 1;
	posHealthBar.y = tileMapDispl.y;
	spriteHealth->setPosition(posHealthBar);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteExpBar = Sprite::createSprite(glm::ivec2(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT), glm::vec2(55.f / 2000.f, 77.f / 480.f), &spritesheet, &shaderProgram);
	spriteExpBar->setNumberAnimations(1);

	spriteExpBar->setAnimationSpeed(BLOCK, 1);
	spriteExpBar->addKeyframe(BLOCK, glm::vec2(413.f / 2000.f, 161.f / 480.f));

	spriteExpBar->changeAnimation(0);
	posExpBar.x = posHealthBar.x;
	posExpBar.y = posHealthBar.y + HEALTH_BAR_HEIGHT + 4;
	spriteExpBar->setPosition(posExpBar);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteGirlsRescued = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(80.f / 2000.f, 80.f / 480.f), &spritesheet, &shaderProgram);
	spriteGirlsRescued->setNumberAnimations(2);

	spriteGirlsRescued->setAnimationSpeed(BLOCK, 1);
	spriteGirlsRescued->addKeyframe(BLOCK, glm::vec2(0 / 2000.f, 240.f / 480.f));

	spriteGirlsRescued->setAnimationSpeed(BLOCK2, 1);
	spriteGirlsRescued->addKeyframe(BLOCK2, glm::vec2(0 / 2000.f, 320.f / 480.f));

	spriteGirlsRescued->changeAnimation(0);
	posGirl.x = posHealthBar.x;
	posGirl.y = posExpBar.y + HEALTH_BAR_HEIGHT + 4;
	spriteGirlsRescued->setPosition(posGirl);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteKey = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(62.f / 2000.f, 62.f / 480.f), &spritesheet, &shaderProgram);
	spriteKey->setNumberAnimations(1);

	spriteKey->setAnimationSpeed(BLOCK, 1);
	spriteKey->addKeyframe(BLOCK, glm::vec2(89.f / 2000.f, 249.f / 480.f));

	spriteKey->changeAnimation(0);
	posKey.x = posGirl.x + 7 * HEALTH_BAR_WIDTH;
	posKey.y = posGirl.y;
	spriteKey->setPosition(posKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteNumberKey = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(63.f / 2000.f, 68.f / 480.f), &spritesheet, &shaderProgram);
	spriteNumberKey->setNumberAnimations(7);

	spriteNumberKey->setAnimationSpeed(BLOCK, 1);
	spriteNumberKey->addKeyframe(BLOCK, glm::vec2(791.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK2, 1);
	spriteNumberKey->addKeyframe(BLOCK2, glm::vec2(855.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK3, 1);
	spriteNumberKey->addKeyframe(BLOCK3, glm::vec2(926.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK4, 1);
	spriteNumberKey->addKeyframe(BLOCK4, glm::vec2(992.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK5, 1);
	spriteNumberKey->addKeyframe(BLOCK5, glm::vec2(1064.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK6, 1);
	spriteNumberKey->addKeyframe(BLOCK6, glm::vec2(1130.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK7, 1);
	spriteNumberKey->addKeyframe(BLOCK7, glm::vec2(1202.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->changeAnimation(0);
	posNumberKey.x = posX.x + 10;
	posNumberKey.y = posKey.y;
	spriteNumberKey->setPosition(posNumberKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteX = Sprite::createSprite(glm::ivec2(10, 10), glm::vec2(54.f / 2000.f, 72.f / 480.f), &spritesheet, &shaderProgram);
	spriteX->setNumberAnimations(1);

	spriteX->setAnimationSpeed(BLOCK, 1);
	spriteX->addKeyframe(BLOCK, glm::vec2(1508.f / 2000.f, 89.f / 480.f));

	spriteX->changeAnimation(0);
	posX.x = posKey.x + 15;
	posX.y = posKey.y + 5;
	spriteX->setPosition(posX);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spritePowerUp = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(80.f / 2000.f, 79.f / 480.f), &spritesheet, &shaderProgram);
	spritePowerUp->setNumberAnimations(6);

	spritePowerUp->setAnimationSpeed(BLOCK, 1);
	spritePowerUp->addKeyframe(BLOCK, glm::vec2(0.f, 401.f / 480.f));

	spritePowerUp->setAnimationSpeed(BLOCK2, 1);
	spritePowerUp->addKeyframe(BLOCK2, glm::vec2(403.f / 2000.f, 401.f / 480.f));

	spritePowerUp->setAnimationSpeed(BLOCK3, 1);
	spritePowerUp->addKeyframe(BLOCK3, glm::vec2(84.f / 2000.f, 401.f / 480.f));

	spritePowerUp->setAnimationSpeed(BLOCK4, 1);
	spritePowerUp->addKeyframe(BLOCK4, glm::vec2(235.f / 2000.f, 401.f / 480.f));

	spritePowerUp->setAnimationSpeed(BLOCK5, 1);
	spritePowerUp->addKeyframe(BLOCK5, glm::vec2(323.f / 2000.f, 401.f / 480.f));

	spritePowerUp->setAnimationSpeed(BLOCK6, 1);
	spritePowerUp->addKeyframe(BLOCK6, glm::vec2(640.f / 2000.f, 398.f / 480.f));

	spritePowerUp->changeAnimation(0);
	posPowerUp.x = posNumberKey.x + 2 * HEALTH_BAR_WIDTH;
	posPowerUp.y = posNumberKey.y;
	spritePowerUp->setPosition(posPowerUp);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteNumberBull = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(63.f / 2000.f, 68.f / 480.f), &spritesheet, &shaderProgram);
	spriteNumberBull->setNumberAnimations(6);

	spriteNumberBull->setAnimationSpeed(BLOCK, 1);
	spriteNumberBull->addKeyframe(BLOCK, glm::vec2(791.f / 2000.f, 2.f / 480.f));

	spriteNumberBull->setAnimationSpeed(BLOCK2, 1);
	spriteNumberBull->addKeyframe(BLOCK2, glm::vec2(855.f / 2000.f, 2.f / 480.f));

	spriteNumberBull->setAnimationSpeed(BLOCK3, 1);
	spriteNumberBull->addKeyframe(BLOCK3, glm::vec2(926.f / 2000.f, 2.f / 480.f));

	spriteNumberBull->setAnimationSpeed(BLOCK4, 1);
	spriteNumberBull->addKeyframe(BLOCK4, glm::vec2(992.f / 2000.f, 2.f / 480.f));

	spriteNumberBull->setAnimationSpeed(BLOCK5, 1);
	spriteNumberBull->addKeyframe(BLOCK5, glm::vec2(1064.f / 2000.f, 2.f / 480.f));

	spriteNumberBull->setAnimationSpeed(BLOCK6, 1);
	spriteNumberBull->addKeyframe(BLOCK6, glm::vec2(1130.f / 2000.f, 2.f / 480.f));

	spriteNumberBull->changeAnimation(0);
	posNumberBull.x = posPowerUp.x + 25 + 6 * HEALTH_BAR_WIDTH;
	posNumberBull.y = posPowerUp.y;
	spriteNumberBull->setPosition(posNumberBull);
	
}

void PlayerStats::update(int health, int exp, bool* gRescued, int nkeys, bool* powerUp, int bullets)
{
	this->health = health;
	this->exp = exp;
	this->gRescued = gRescued;
	this->nkeys = nkeys;
	switch (this->nkeys)
	{
	case 0: {
		if (spriteNumberKey->animation() != BLOCK)
			spriteNumberKey->changeAnimation(BLOCK);
	} break;
	case 1: {
		if (spriteNumberKey->animation() != BLOCK2)
			spriteNumberKey->changeAnimation(BLOCK2);
	} break;
	case 2: {
		if (spriteNumberKey->animation() != BLOCK3)
			spriteNumberKey->changeAnimation(BLOCK3);
	} break;
	case 3: {
		if (spriteNumberKey->animation() != BLOCK4)
			spriteNumberKey->changeAnimation(BLOCK4);
	} break;
	case 4: {
		if (spriteNumberKey->animation() != BLOCK5)
			spriteNumberKey->changeAnimation(BLOCK5);
	} break;
	case 5: {
		if (spriteNumberKey->animation() != BLOCK6)
			spriteNumberKey->changeAnimation(BLOCK6);
	} break;
	case 6: {
		if (spriteNumberKey->animation() != BLOCK7)
			spriteNumberKey->changeAnimation(BLOCK7);
	} break;
	}
	this->powerUp = powerUp;
	this->bullets = bullets;
	switch (this->bullets)
	{
	case 0: {
		if (spriteNumberBull->animation() != BLOCK)
			spriteNumberBull->changeAnimation(BLOCK);
	} break;
	case 1: {
		if (spriteNumberBull->animation() != BLOCK2)
			spriteNumberBull->changeAnimation(BLOCK2);
	} break;
	case 2: {
		if (spriteNumberBull->animation() != BLOCK3)
			spriteNumberBull->changeAnimation(BLOCK3);
	} break;
	case 3: {
		if (spriteNumberBull->animation() != BLOCK4)
			spriteNumberBull->changeAnimation(BLOCK4);
	} break;
	case 4: {
		if (spriteNumberBull->animation() != BLOCK5)
			spriteNumberBull->changeAnimation(BLOCK5);
	} break;
	case 5: {
		if (spriteNumberBull->animation() != BLOCK6)
			spriteNumberBull->changeAnimation(BLOCK6);
	} break;
	}
}

void PlayerStats::render()
{
	//spriteHealth->render();
	//spriteExp->render();
	
	/*switch (health) {
	case 1: {
		spriteHealth->render();
	}break;
	case 2: {
		spriteHealth->render();
		spriteHealth->setPosition(glm::vec2 (float(posAux.x + HEALTH_BAR_WIDTH), float(posAux.x)));

	}
	}*/
	spriteHeart->render();
	spriteExp->render();
	glm::ivec2 posAux = posHealthBar;
	for (int i = 0; i < health; i++) {
		spriteHealth->setPosition(glm::vec2(float(posAux.x + i * HEALTH_BAR_WIDTH), float(posAux.y)));
		spriteHealth->render();
	}
	spriteHealth->setPosition(posHealthBar);
	posAux = posExpBar;
	for (int i = 0; i < exp; i++) {
		spriteExpBar->setPosition(glm::vec2(float(posAux.x + i * HEALTH_BAR_WIDTH), float(posAux.y)));
		spriteExpBar->render();
	}
	spriteExpBar->setPosition(posExpBar);
	posAux = posGirl;
	for (int i = 0; i < 6; i++) {
		if (gRescued[i])
			spriteGirlsRescued->changeAnimation(BLOCK);
		else
			spriteGirlsRescued->changeAnimation(BLOCK2);
		spriteGirlsRescued->setPosition(glm::vec2(float(posAux.x + i * HEALTH_BAR_WIDTH), float(posAux.y)));
		spriteGirlsRescued->render();

	}
	spriteGirlsRescued->setPosition(posGirl);
	spriteKey->render();
	spriteX->render();
	spriteNumberKey->render();
	posAux = posPowerUp;
	if (powerUp[0]) {
		spritePowerUp->changeAnimation(BLOCK);
		spritePowerUp->setPosition(posAux);
		spritePowerUp->render();
	}
	posAux.x += HEALTH_BAR_WIDTH;
	if (powerUp[1]) {
		spritePowerUp->changeAnimation(BLOCK2);
		spritePowerUp->setPosition(posAux);
		spritePowerUp->render();
	}
	posAux.x += HEALTH_BAR_WIDTH;
	if (powerUp[2]) {
		spritePowerUp->changeAnimation(BLOCK3);
		spritePowerUp->setPosition(posAux);
		spritePowerUp->render();
	}
	posAux.x += HEALTH_BAR_WIDTH;
	if (powerUp[3]) {
		spritePowerUp->changeAnimation(BLOCK4);
		spritePowerUp->setPosition(posAux);
		spritePowerUp->render();
	}
	posAux.x += HEALTH_BAR_WIDTH;
	if (powerUp[4]) {
		spritePowerUp->changeAnimation(BLOCK5);
		spritePowerUp->setPosition(posAux);
		spritePowerUp->render();
	}
	posAux.x += HEALTH_BAR_WIDTH;
	spritePowerUp->changeAnimation(BLOCK6);
	spritePowerUp->setPosition(posAux);
	spritePowerUp->render();
	posAux.x += 15;
	posAux.y += 5;
	spriteX->setPosition(posAux);
	spriteX->render();
	spriteX->setPosition(posX);
	spriteNumberBull->render();
}

void PlayerStats::setPosition(const glm::vec2& pos)
{
	posHeart.x = pos.x;
	posHeart.y = pos.y;
	posExp.x = pos.x;
	posExp.y = pos.y + HEALTH_BAR_HEIGHT + 4;
	posHealthBar.x = pos.x + HEALTH_ICON_WIDTH + 1;
	posHealthBar.y = pos.y;
	posExpBar.x = posHealthBar.x;
	posExpBar.y = posHealthBar.y + HEALTH_BAR_HEIGHT + 4;
	posGirl.x = posHealthBar.x;
	posGirl.y = posExpBar.y + HEALTH_BAR_HEIGHT + 4;
	posKey.x = posGirl.x + 7 * HEALTH_BAR_WIDTH;
	posKey.y = posGirl.y;
	posX.x = posKey.x + 15;
	posX.y = posKey.y + 5;
	posNumberKey.x = posX.x + 10;
	posNumberKey.y = posKey.y;
	posPowerUp.x = posNumberKey.x + 2 * HEALTH_BAR_WIDTH;
	posPowerUp.y = posNumberKey.y;
	posNumberBull.x = posPowerUp.x + 25 + 5 * HEALTH_BAR_WIDTH;
	posNumberBull.y = posPowerUp.y;

	spriteHeart->setPosition(posHeart);
	spriteExp->setPosition(posExp);
	spriteHealth->setPosition(posHealthBar);
	spriteExpBar->setPosition(posExpBar);
	spriteGirlsRescued->setPosition(posGirl);
	spriteKey->setPosition(posKey);
	spriteX->setPosition(posX);
	spriteNumberKey->setPosition(posNumberKey);
	spritePowerUp->setPosition(posPowerUp);
	spriteNumberBull->setPosition(posNumberBull);
}

bool PlayerStats::checkKeys()
{
	if (nkeys > 0)return true;
	return false;
}