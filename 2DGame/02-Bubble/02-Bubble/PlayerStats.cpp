#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerStats.h"

#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_HEIGHT 10

#define HEALTH_ICON_WIDTH 10
#define HEALTH_ICON_HEIGHT 10

enum HealthState
{
	FULL1, NINET1, EIGHTE1, SEVENT1, SIXT1, FIF1, FOURT1, THIR1, TWE1, ELE1, TEN1, NINE1, EIGHT1, SEVEN1, SIX1, FIVE1, FOUR1, THREE1, TWO1, ONE1
} health_states;

enum ExpState
{
	FULL2, NINET2, EIGHTE2, SEVENT2, SIXT2, FIF2, FOURT2, THIR2, TWE2, ELE2, TEN2, NINE2, EIGHT2, SEVEN2, SIX2, FIVE2, FOUR2, THREE2, TWO2, ONE2
} exp_states;

enum Anims
{
	BLOCK
};

void PlayerStats::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	health_states = FULL1;
	exp_states = FULL2;
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

}

void PlayerStats::update(int health, int exp)
{

}

void PlayerStats::render(int health, int exp)
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
}

void PlayerStats::setPosition(const glm::vec2& pos)
{
	posHealth.x = pos.x + HEALTH_ICON_WIDTH;
	posHealth.y = pos.y;
	posExp.x = posHealth.x;
	posExp.y = posHealth.y + HEALTH_BAR_HEIGHT + 4;
	spriteHealth->setPosition(posHealth);
	spriteExp->setPosition(posExp);
}
