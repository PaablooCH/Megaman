#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerStats.h"

enum HealthState
{
	FULL1, NINE1, EIGHT1, SEVEN1, SIX1, FIVE1, FOUR1, THREE1, TWO1, ONE1
} health_states;

enum ExpState
{
	FULL2, NINE2, EIGHT2, SEVEN2, SIX2, FIVE2, FOUR2, THREE2, TWO2, ONE2
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
	spriteHealth = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	spriteHealth->setNumberAnimations(1);

	spriteHealth->setAnimationSpeed(BLOCK, 1);
	spriteHealth->addKeyframe(BLOCK, glm::vec2(0,0));

	spriteHealth->changeAnimation(0);
	tileMapDispl = tileMapPos;
	spriteHealth->setPosition(glm::vec2(float(tileMapDispl.x + posHealth.x), float(tileMapDispl.y + posHealth.y)));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteExp = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f / 6.f, 1.f / 2.f), &spritesheet, &shaderProgram);
	spriteExp->setNumberAnimations(1);

	spriteExp->setAnimationSpeed(BLOCK, 1);
	spriteExp->addKeyframe(BLOCK, glm::vec2(1.f / 6.f, 1.f / 2.f));

	spriteExp->changeAnimation(0);
	tileMapDispl = tileMapPos;
	spriteExp->setPosition(glm::vec2(float(tileMapDispl.x + posExp.x), float(tileMapDispl.y + posExp.y)));

}

void PlayerStats::update(int health, int exp)
{
	render();
}

void PlayerStats::render()
{
	spriteHealth->render();
}