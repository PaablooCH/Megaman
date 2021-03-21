#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "Camera.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum States 
{
	HITTING, JUMPING, CLIMBING, STANDING, MOVING_LEFT, MOVING_RIGHT, FALLING
} state;

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, HIT_LEFT, HIT_RIGHT, JUMP_LEFT1, JUMP_LEFT2, JUMP_RIGHT1, JUMP_RIGHT2, JUMP_TOP_LEFT, JUMP_TOP_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	state = STANDING;
	isRight = true;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(35, 38), glm::vec2(1.f / 8.f, 1.f / 30.9), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 15.f/30.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(7.f/8.f, 0.f));
		
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
		
		sprite->setAnimationSpeed(HIT_LEFT, 10);
		//sprite->addKeyframe(HIT_LEFT, glm::vec2(7.f / 8.f, 29.1 / 30.f));
		//sprite->addKeyframe(HIT_LEFT, glm::vec2(6.f / 8.f, 29.1 / 30.f));
		sprite->addKeyframe(HIT_LEFT, glm::vec2(5.f / 8.f, 29.1 / 30.f));
		sprite->addKeyframe(HIT_LEFT, glm::vec2(4.f / 8.f, 29.1 / 30.f));
		sprite->addKeyframe(HIT_LEFT, glm::vec2(5.f / 8.f, 29.1 / 30.f));
		//sprite->addKeyframe(HIT_LEFT, glm::vec2(6.f / 8.f, 29.1 / 30.f));
		//sprite->addKeyframe(HIT_LEFT, glm::vec2(7.f / 8.f, 29.1 / 30.f));

		sprite->setAnimationSpeed(HIT_RIGHT, 10);
		//sprite->addKeyframe(HIT_RIGHT, glm::vec2(0.f / 8.f, 14.1 / 30.f));
		//sprite->addKeyframe(HIT_RIGHT, glm::vec2(1.f / 8.f, 14.1 / 30.f));
		sprite->addKeyframe(HIT_RIGHT, glm::vec2(2.f / 8.f, 14.1 / 30.f));
		sprite->addKeyframe(HIT_RIGHT, glm::vec2(3.f / 8.f, 14.1 / 30.f));
		sprite->addKeyframe(HIT_RIGHT, glm::vec2(2.f / 8.f, 14.1 / 30.f));
		//sprite->addKeyframe(HIT_RIGHT, glm::vec2(1.f / 8.f, 14.1 / 30.f));
		//sprite->addKeyframe(HIT_RIGHT, glm::vec2(0.f / 8.f, 14.1 / 30.f));

		sprite->setAnimationSpeed(JUMP_LEFT1, 8);
		sprite->addKeyframe(JUMP_LEFT1, glm::vec2(6.f / 8.f, 23.f / 30.f));

		sprite->setAnimationSpeed(JUMP_LEFT2, 8);
		sprite->addKeyframe(JUMP_LEFT2, glm::vec2(5.f / 8.f, 23.f / 30.f));

		sprite->setAnimationSpeed(JUMP_RIGHT1, 8);
		sprite->addKeyframe(JUMP_RIGHT1, glm::vec2(1.f / 8.f, 8.f / 30.f));

		sprite->setAnimationSpeed(JUMP_RIGHT2, 8);
		sprite->addKeyframe(JUMP_RIGHT2, glm::vec2(2.f / 8.f, 8.f / 30.f));

		sprite->setAnimationSpeed(JUMP_TOP_LEFT, 8);
		sprite->addKeyframe(JUMP_TOP_LEFT, glm::vec2(4.f / 8.f, 23.f / 30.f));

		sprite->setAnimationSpeed(JUMP_TOP_RIGHT, 8);
		sprite->addKeyframe(JUMP_TOP_RIGHT, glm::vec2(3.f / 8.f, 8.f / 30.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch (state)
	{
		case HITTING: {
			cont += deltaTime;
			if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(HIT_LEFT);
			else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(HIT_RIGHT);
			if (cont >= 250) state = STANDING;
			
		} break;

		case JUMPING: {
			
			jumpAngle += JUMP_ANGLE_STEP;

			if (jumpAngle >= 90)
			{
				state = FALLING;
			}
				
			if (jumpAngle <= 30) {
				if (!isRight)
					sprite->changeAnimation(JUMP_LEFT1);
				else 
					sprite->changeAnimation(JUMP_RIGHT1);
			}
			else if (jumpAngle <=80) {
				if (!isRight)
					sprite->changeAnimation(JUMP_LEFT2);
				else
					sprite->changeAnimation(JUMP_RIGHT2);
			}
			else if (jumpAngle <= 90) {
				if (!isRight)
					sprite->changeAnimation(JUMP_TOP_LEFT);
				else
					sprite->changeAnimation(JUMP_TOP_RIGHT);
			}

			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
				posPlayer.x -= 2;
				isRight = false;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
					posPlayer.x += 2;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
				posPlayer.x += 2;
				isRight = true;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
					posPlayer.x -= 2;
			}
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			
		} break;

		case FALLING: {
			if (jumpAngle <= 100) {
				if (!isRight)
					sprite->changeAnimation(JUMP_TOP_LEFT);
				else
					sprite->changeAnimation(JUMP_TOP_RIGHT);
			}
			else {
				if (!isRight)
					sprite->changeAnimation(JUMP_LEFT2);
				else
					sprite->changeAnimation(JUMP_RIGHT2);
			}

			posPlayer.y += FALL_STEP;
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
				posPlayer.x -= 2;
				isRight = false;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
					posPlayer.x += 2;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
				posPlayer.x += 2;
				isRight = true;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
					posPlayer.x -= 2;
			}
			bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
			if (!bJumping)
				state = STANDING;

		} break;

		case CLIMBING: {

		} break;

		case MOVING_LEFT: {
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			isRight = false;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
			state = STANDING;
		} break;

		case MOVING_RIGHT: {
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			isRight = true;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
			state = STANDING;
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

	if(!bJumping)
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			state = MOVING_LEFT;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			state = MOVING_RIGHT;
		}
		else if (Game::instance().getKey(GLUT_SPACE)) {
			state = HITTING;
			cont = 0;
		}
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				state = JUMPING;
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
		else {
			state = FALLING;
			bJumping = true;
			jumpAngle = 90;
		}
			
	}
		

	/*if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}*/

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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



void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




