#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LinealEnemy.h"


enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT
};


LinealEnemy::~LinealEnemy()
{
}

void LinealEnemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id)
{
	bJumping = false;

	isRight = true;
	isAlive = true;
	bool moveRight = false;
	spritesheet.loadFromFile("images/Enemy1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(23.f / 158.f, 22.f / 54.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(109.f / 158.f, 2.f / 54.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(134.f / 158.f, 2.f / 54.f));


	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(31.f / 158.f, 28.f / 54.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.f / 158.f, 28.f / 54.f));


	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	posIni = posInicial;
	ID = id;
	sprite->setPosition(posIni);
}

void LinealEnemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch (moveRight) {
	case false: {
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posEnemy.x -= 1;
		if (map->collisionFall(posEnemy, glm::ivec2(16, 16), &posEnemy.y)) {
			posEnemy.x += 1;
			sprite->changeAnimation(MOVE_RIGHT);
			moveRight = true;
		}
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(16, 16)))
		{
			posEnemy.x += 1;
			sprite->changeAnimation(MOVE_RIGHT);
			moveRight = true;
		}
		if (map->checkPlayerLeft(posEnemy, glm::ivec2(16, 16)))
		{
			if (player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkPlayerRight(posEnemy, glm::ivec2(16, 16)))
		{
			if (!player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkEnemyBulletDamage(posEnemy, glm::ivec2(16, 16)))
		{
			isAlive = false;
			map->clearPosition(ID);
		}
		posAnt = posEnemy;
	} break;

	case true : {
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posEnemy.x += 1;
		if (map->collisionFall(posEnemy, glm::ivec2(16, 16), &posEnemy.y)) {
			posEnemy.x -= 1;
			sprite->changeAnimation(MOVE_LEFT);
			moveRight = false;
		}
		if (map->collisionMoveRight(posEnemy, glm::ivec2(16, 16)))
		{
			posEnemy.x -= 1;
			sprite->changeAnimation(MOVE_LEFT);
			moveRight = false;
		}
		if (map->checkPlayerRight(posEnemy, glm::ivec2(16, 16)))
		{
			if (!player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkPlayerLeft(posEnemy, glm::ivec2(16, 16)))
		{
			if (player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkEnemyBulletDamage(posEnemy, glm::ivec2(16, 16)))
		{
			isAlive = false;
			map->clearPosition(ID);
		}
		posAnt = posEnemy;
	} break;
	}

	if(isAlive)map->updatePositionTile(posEnemy, glm::ivec2(32, 32), posAnt, ID);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}