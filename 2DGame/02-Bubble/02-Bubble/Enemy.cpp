#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"
#include "Camera.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 92
#define FALL_STEP 4

/*
enum State
{
	MOVING_LEFT, MOVING_RIGHT, HITTED_RIGHT, HITTED_LEFT
} states;

enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT, HIT_RIGHT, HIT_LEFT
};


void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;

	isRight = true;
	states = MOVING_LEFT;
	spritesheet.loadFromFile("images/Enemy1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f / 6.f, 1.f / 2.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(1.f / 6.f, 1.f / 2.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f / 6.f, 1.f / 2.f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.f / 6.f, 0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5.f / 6.f, 0));

	sprite->setAnimationSpeed(HIT_RIGHT, 6);
	sprite->addKeyframe(HIT_RIGHT, glm::vec2(1.f / 6.f, 0));
	sprite->addKeyframe(HIT_RIGHT, glm::vec2(0.f / 6.f, 0));

	sprite->setAnimationSpeed(HIT_LEFT, 6);
	sprite->addKeyframe(HIT_LEFT, glm::vec2(4.f / 6.f, 1.f / 2.f));
	sprite->addKeyframe(HIT_LEFT, glm::vec2(5.f / 6.f, 1.f / 2.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}


void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	posAnt = posEnemy;
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
			if(cont >= 350)states = MOVING_LEFT;
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
			if (map->enemyMoveLeft(posEnemy, glm::ivec2(32, 32))) comentar esto
			{
				posEnemy.x += 2;
				sprite->changeAnimation(HIT_LEFT);
				cont = 0;
				states = HITTED_LEFT;
			}
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
			if (map->enemyMoveRight(posEnemy, glm::ivec2(10, 32))) comentar esto
			{
				posEnemy.x -= 2;
				sprite->changeAnimation(HIT_RIGHT);
				cont = 0;
				states = HITTED_RIGHT;
			}
		} break;
	}

	map->updatePositionTile(posEnemy, glm::ivec2(32, 32), posAnt, 3);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}*/

void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}