#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LinealEnemy.h"

enum State
{
	MOVING_LEFT, MOVING_RIGHT, HITTED_RIGHT, HITTED_LEFT
} states;

enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT, HIT_RIGHT, HIT_LEFT
};


void LinealEnemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
	bJumping = false;

	isRight = true;
	isAlive = true;
	states = MOVING_LEFT;
	spritesheet.loadFromFile("images/Enemy1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(23.f / 158.f, 22.f / 54.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(109.f / 158.f, 2.f / 54.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(134.f / 158.f, 2.f / 54.f));


	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(31.f / 158.f, 28.f / 54.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.f / 158.f, 28.f / 54.f));

	sprite->setAnimationSpeed(HIT_RIGHT, 6);
	sprite->addKeyframe(HIT_RIGHT, glm::vec2(1.f / 6.f, 0));
	sprite->addKeyframe(HIT_RIGHT, glm::vec2(0.f / 6.f, 0));

	sprite->setAnimationSpeed(HIT_LEFT, 6);
	sprite->addKeyframe(HIT_LEFT, glm::vec2(4.f / 6.f, 1.f / 2.f));
	sprite->addKeyframe(HIT_LEFT, glm::vec2(5.f / 6.f, 1.f / 2.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	posIni = posInicial;
	sprite->setPosition(posIni);
}

void LinealEnemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch (states) {
	case HITTED_LEFT: {
		cont += deltaTime;
		if (sprite->animation() != HIT_LEFT)
			sprite->changeAnimation(HIT_LEFT);
		posEnemy.x += 2;
		if (map->collisionMoveRight(posEnemy, glm::ivec2(32, 32))) {
			posEnemy.x -= 2;
			states = MOVING_LEFT;
		}
		else if (map->collisionFall(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.x -= 1;
			states = MOVING_LEFT;
		}
		if (cont >= 350)states = MOVING_LEFT;
		posAnt = posEnemy;
	} break;

	case HITTED_RIGHT: {
		cont += deltaTime;
		if (sprite->animation() != HIT_RIGHT)
			sprite->changeAnimation(HIT_RIGHT);
		posEnemy.x -= 2;
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32))) {
			posEnemy.x += 2;
			states = MOVING_RIGHT;
		}
		else if (map->collisionFall(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.x += 1;
			states = MOVING_RIGHT;
		}
		if (cont >= 350)states = MOVING_RIGHT;
		posAnt = posEnemy;
	} break;

	case MOVING_LEFT: {
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posEnemy.x -= 1;
		if (map->collisionFall(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.x += 1;
			sprite->changeAnimation(MOVE_RIGHT);
			states = MOVING_RIGHT;
		}
		else if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x += 1;
			sprite->changeAnimation(MOVE_RIGHT);
			states = MOVING_RIGHT;
		}
		if (map->enemyMoveLeft(posEnemy, glm::ivec2(20, 32)))
		{
			if (player->checkRight()) {
				if (player->checkHit())isAlive = false;
			}
		}
		if (map->enemyMoveRight(posEnemy, glm::ivec2(23, 32)))
		{
			if (!player->checkRight()) {
				if (player->checkHit())isAlive = false;
			}
		}
		posAnt = posEnemy;
	} break;

	case MOVING_RIGHT: {
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posEnemy.x += 1;
		if (map->collisionFall(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.x -= 1;
			sprite->changeAnimation(MOVE_LEFT);
			states = MOVING_LEFT;
		}
		else if (map->collisionMoveRight(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x -= 1;
			sprite->changeAnimation(MOVE_LEFT);
			states = MOVING_LEFT;
		}
		if (map->enemyMoveRight(posEnemy, glm::ivec2(23, 32)))
		{
			if (!player->checkRight()) {
				if (player->checkHit())isAlive = false;
			}
		}
		if (map->enemyMoveLeft(posEnemy, glm::ivec2(23, 32)))
		{
			if (player->checkRight()) {
				if (player->checkHit())isAlive = false;
			}
		}
		posAnt = posEnemy;
	} break;
	}

	map->updatePositionTile(posEnemy, glm::ivec2(32, 32), posAnt, 10);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}