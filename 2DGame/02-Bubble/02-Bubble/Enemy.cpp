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
	STANDING, FALLING
} states;

enum EnemyAnims
{
	STAND_LEFT, STAND_RIGHT
};


void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;

	isRight = true;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(35, 38), glm::vec2(1.f / 8.f, 1.f / 30.9), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 15.f / 30.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(7.f / 8.f, 0.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch(states){
		case FALLING: {
			posEnemy.y += FALL_STEP;
			bJumping = !map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y);
			if (!bJumping)
				states = STANDING;
			jumpAngle += JUMP_ANGLE_STEP;

		} break;

		case STANDING: {
			if (!isRight) {
				sprite->changeAnimation(STAND_LEFT);
				isRight = false;
			}
			else {
				sprite->changeAnimation(STAND_RIGHT);
				isRight = true;
			}
		} break;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
} 

/*void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getKey(GLUT_SPACE)) {
		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(HIT_LEFT);
		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(HIT_RIGHT);

	}
	else
	{
		if(sprite->animation() == MOVE_LEFT || sprite->animation() == HIT_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT || sprite->animation() == HIT_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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
	posEnemy= pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}
