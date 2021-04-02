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

void PlayerStats::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	//health_states = FULL1;
	//exp_states = FULL2;

	spritesheet.loadFromFile("images/HUD.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteHealth = Sprite::createSprite(glm::ivec2(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT), glm::vec2(55.f / 2000.f, 77.f / 480.f), &spritesheet, &shaderProgram);
	spriteHealth->setNumberAnimations(1);

	spriteHealth->setAnimationSpeed(BLOCK, 1);
	spriteHealth->addKeyframe(BLOCK, glm::vec2(944.f / 2000.f, 160.f / 480.f));

	spriteHealth->changeAnimation(0);
	tileMapDispl = tileMapPos;
	posHealth.x = tileMapDispl.x + HEALTH_ICON_WIDTH;
	posHealth.y = tileMapDispl.y;
	spriteHealth->setPosition(posHealth);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteExp = Sprite::createSprite(glm::ivec2(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT), glm::vec2(55.f / 2000.f, 77.f / 480.f), &spritesheet, &shaderProgram);
	spriteExp->setNumberAnimations(1);

	spriteExp->setAnimationSpeed(BLOCK, 1);
	spriteExp->addKeyframe(BLOCK, glm::vec2(413.f / 2000.f, 161.f / 480.f));

	spriteExp->changeAnimation(0);
	posExp.x = posHealth.x;
	posExp.y = posHealth.y + HEALTH_BAR_HEIGHT + 4;
	spriteExp->setPosition(posExp);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteGirlsRescued = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(80.f / 2000.f, 80.f / 480.f), &spritesheet, &shaderProgram);
	spriteGirlsRescued->setNumberAnimations(2);
	
	spriteGirlsRescued->setAnimationSpeed(BLOCK, 1);
	spriteGirlsRescued->addKeyframe(BLOCK, glm::vec2(0/ 2000.f, 240.f / 480.f));

	spriteGirlsRescued->setAnimationSpeed(BLOCK2, 1);
	spriteGirlsRescued->addKeyframe(BLOCK2, glm::vec2(0 / 2000.f, 320.f / 480.f));

	spriteGirlsRescued->changeAnimation(0);
	tileMapDispl = tileMapPos;
	posGirl.x = posHealth.x;
	posGirl.y = posExp.y + HEALTH_BAR_HEIGHT + 4;
	spriteGirlsRescued->setPosition(posGirl);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteKey = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(62.f / 2000.f, 62.f / 480.f), &spritesheet, &shaderProgram);
	spriteKey->setNumberAnimations(1);

	spriteKey->setAnimationSpeed(BLOCK, 1);
	spriteKey->addKeyframe(BLOCK, glm::vec2(89.f / 2000.f, 249.f / 480.f));

	spriteKey->changeAnimation(0);
	tileMapDispl = tileMapPos;
	posKey.x = posGirl.x + 7* HEALTH_BAR_WIDTH;
	posKey.y = posGirl.y;
	spriteKey->setPosition(posKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteNumberKey = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(63.f / 2000.f, 68.f / 480.f), &spritesheet, &shaderProgram);
	spriteNumberKey->setNumberAnimations(7);

	spriteNumberKey->setAnimationSpeed(BLOCK, 1);
	spriteNumberKey->addKeyframe(BLOCK, glm::vec2(989.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK2, 1);
	spriteNumberKey->addKeyframe(BLOCK2, glm::vec2(1059.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK3, 1);
	spriteNumberKey->addKeyframe(BLOCK3, glm::vec2(1124.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK4, 1);
	spriteNumberKey->addKeyframe(BLOCK4, glm::vec2(1187.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK5, 1);
	spriteNumberKey->addKeyframe(BLOCK5, glm::vec2(1267.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK6, 1);
	spriteNumberKey->addKeyframe(BLOCK6, glm::vec2(1334.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->setAnimationSpeed(BLOCK7, 1);
	spriteNumberKey->addKeyframe(BLOCK7, glm::vec2(1406.f / 2000.f, 2.f / 480.f));

	spriteNumberKey->changeAnimation(0);
	tileMapDispl = tileMapPos;
	posNumberKey.x = posXKey.x + 10;
	posNumberKey.y = posKey.y;
	spriteNumberKey->setPosition(posNumberKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteXKey = Sprite::createSprite(glm::ivec2(10, 10), glm::vec2(54.f / 2000.f, 72.f / 480.f), &spritesheet, &shaderProgram);
	spriteXKey->setNumberAnimations(1);

	spriteXKey->setAnimationSpeed(BLOCK, 1);
	spriteXKey->addKeyframe(BLOCK, glm::vec2(1508.f / 2000.f, 89.f / 480.f));

	spriteXKey->changeAnimation(0);
	tileMapDispl = tileMapPos;
	posXKey.x = posKey.x + 15;
	posXKey.y = posKey.y + 5;
	spriteXKey->setPosition(posXKey);
}

void PlayerStats::update(int health, int exp, bool* gRescued, int nkeys, bool* powerUp)
{
	this->health = health;
	this->exp = exp;
	this->gRescued = gRescued;
	this->nkeys = nkeys;
	switch (this->nkeys)
	{
		case 0:{
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
}

void PlayerStats::render()
{
	//spriteHealth->render();
	//spriteExp->render();
	glm::ivec2 posAux = posHealth;
	/*switch (health) {
	case 1: {
		spriteHealth->render();
	}break;
	case 2: {
		spriteHealth->render();
		spriteHealth->setPosition(glm::vec2 (float(posAux.x + HEALTH_BAR_WIDTH), float(posAux.x)));

	}
	}*/

	for (int i = 0; i < health; i++) {
		spriteHealth->setPosition(glm::vec2(float(posAux.x + i * HEALTH_BAR_WIDTH), float(posAux.y)));
		spriteHealth->render();
	}
	spriteHealth->setPosition(posHealth);
	posAux = posExp;
	for (int i = 0; i < exp; i++) {
		spriteExp->setPosition(glm::vec2(float(posAux.x + i * HEALTH_BAR_WIDTH), float(posAux.y)));
		spriteExp->render();
	}
	spriteExp->setPosition(posExp);
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
	spriteXKey->render();
	spriteNumberKey->render();
}

void PlayerStats::setPosition(const glm::vec2& pos)
{
	posHealth.x = pos.x + HEALTH_ICON_WIDTH;
	posHealth.y = pos.y;
	posExp.x = posHealth.x;
	posExp.y = posHealth.y + HEALTH_BAR_HEIGHT + 4;
	posGirl.x = posHealth.x;
	posGirl.y = posExp.y + HEALTH_BAR_HEIGHT + 4;
	posKey.x = posGirl.x + 7 * HEALTH_BAR_WIDTH;
	posKey.y = posGirl.y;
	posXKey.x = posKey.x + 15;
	posXKey.y = posKey.y + 5;
	posNumberKey.x = posXKey.x + 10;
	posNumberKey.y = posKey.y;
	spriteHealth->setPosition(posHealth);
	spriteExp->setPosition(posExp);
	spriteGirlsRescued->setPosition(posGirl);
	spriteKey->setPosition(posKey);
	spriteXKey->setPosition(posXKey);
	spriteNumberKey->setPosition(posNumberKey);
}

bool PlayerStats::checkKeys()
{
	if (nkeys > 0)return true;
	return false;
}