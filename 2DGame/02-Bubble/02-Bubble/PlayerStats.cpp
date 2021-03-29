#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerStats.h"

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
	spriteHealth = Sprite::createSprite(glm::ivec2(20, 16), glm::vec2(55.f / 2000.f, 77.f / 480.f), &spritesheet, &shaderProgram);
	spriteHealth->setNumberAnimations(1);

	spriteHealth->setAnimationSpeed(BLOCK, 1);
	spriteHealth->addKeyframe(BLOCK, glm::vec2(944.f / 2000.f, 160.f / 480.f));

	spriteHealth->changeAnimation(0);
	tileMapDispl = tileMapPos;
	posHealth.x = tileMapDispl.x + 10;
	posHealth.y = tileMapDispl.y;
	spriteHealth->setPosition(glm::vec2(float(tileMapDispl.x + posHealth.x), float(tileMapDispl.y + posHealth.y)));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteExp = Sprite::createSprite(glm::ivec2(20, 16), glm::vec2(55.f / 2000.f, 77.f / 480.f), &spritesheet, &shaderProgram);
	spriteExp->setNumberAnimations(1);

	spriteExp->setAnimationSpeed(BLOCK, 1);
	spriteExp->addKeyframe(BLOCK, glm::vec2(413.f / 2000.f, 160.f / 480.f));

	posExp.x = posHealth.x;
	posExp.y = posHealth.y + 17;
	spriteExp->changeAnimation(0);
	spriteExp->setPosition(glm::vec2(float(tileMapDispl.x + posExp.x), float(tileMapDispl.y + posExp.y)));

}

void PlayerStats::update(int health, int exp)
{
	switch (health) {
	case 1: {


	}break;
	}
	
}

void PlayerStats::render(int health, int exp)
{
	spriteHealth->render();
	spriteExp->render();
}

void PlayerStats::setPosition(const glm::vec2& pos)
{
	posHealth = pos;
	posExp.x = pos.x;
	posExp.y = pos.y + 64;
	spriteHealth->setPosition(glm::vec2(float(tileMapDispl.x + posHealth.x), float(tileMapDispl.y + posHealth.y)));
	spriteExp->setPosition(glm::vec2(float(tileMapDispl.x + posExp.x), float(tileMapDispl.y + posExp.y)));
}
