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


enum State
{
	MOVING_LEFT, MOVING_RIGHT
} states;

enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT
};


void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;

	isRight = true;
	states = MOVING_LEFT;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(35, 38), glm::vec2(1.f / 8.f, 1.f / 30.9), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_LEFT, 12);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(7.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(5.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(4.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(1.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f / 8.f, 18.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(7.f / 8.f, 19.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6.f / 8.f, 19.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(5.f / 8.f, 19.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6.f / 8.f, 19.9 / 30.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(7.f / 8.f, 19.9 / 30.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 12);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7.f / 8.f, 3.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f / 8.f, 4.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.f / 8.f, 4.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.f / 8.f, 4.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.f / 8.f, 4.9 / 30.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f / 8.f, 4.9 / 30.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch (states) {
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
	} break;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

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
