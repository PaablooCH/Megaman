#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "Camera.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 92
#define FALL_STEP 4

enum States 
{
	HITTING, JUMPING, CLIMBING, STANDING, MOVING_LEFT, MOVING_RIGHT, FALLING, START, LANDING, DAMAGE
} state;

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, HIT_LEFT, HIT_RIGHT, JUMP_LEFT1, JUMP_LEFT2, JUMP_RIGHT1, JUMP_RIGHT2, JUMP_TOP_LEFT, JUMP_TOP_RIGHT, APPEAR,
	CLIMB11, CLIMB12, CLIMB21, CLIMB22, LAND, DAMAGE_LEFT, DAMAGE_RIGHT
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	isClimbing = false;
	isDamaged = false;
	health = 100;
	state = START;
	cont = 0;
	isAnimation = true;
	isRight = true;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(35, 38), glm::vec2(1.f / 8.f, 1.f / 30.9), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(20);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 15.f / 30.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(7.f / 8.f, 0.f));

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
	sprite->addKeyframe(HIT_LEFT, glm::vec2(5.f / 8.f, 29.1 / 30.f));
	sprite->addKeyframe(HIT_LEFT, glm::vec2(4.f / 8.f, 29.1 / 30.f));
	sprite->addKeyframe(HIT_LEFT, glm::vec2(5.f / 8.f, 29.1 / 30.f));

	sprite->setAnimationSpeed(HIT_RIGHT, 10);
	sprite->addKeyframe(HIT_RIGHT, glm::vec2(2.f / 8.f, 14.1 / 30.f));
	sprite->addKeyframe(HIT_RIGHT, glm::vec2(3.f / 8.f, 14.1 / 30.f));
	sprite->addKeyframe(HIT_RIGHT, glm::vec2(2.f / 8.f, 14.1 / 30.f));

	sprite->setAnimationSpeed(JUMP_LEFT1, 8);
	sprite->addKeyframe(JUMP_LEFT1, glm::vec2(6.f / 8.f, 22.9 / 30.f));

	sprite->setAnimationSpeed(JUMP_LEFT2, 8);
	sprite->addKeyframe(JUMP_LEFT2, glm::vec2(5.f / 8.f, 22.9 / 30.f));

	sprite->setAnimationSpeed(JUMP_RIGHT1, 8);
	sprite->addKeyframe(JUMP_RIGHT1, glm::vec2(1.f / 8.f, 7.9 / 30.f));

	sprite->setAnimationSpeed(JUMP_RIGHT2, 8);
	sprite->addKeyframe(JUMP_RIGHT2, glm::vec2(2.f / 8.f, 7.9 / 30.f));

	sprite->setAnimationSpeed(JUMP_TOP_LEFT, 8);
	sprite->addKeyframe(JUMP_TOP_LEFT, glm::vec2(4.f / 8.f, 22.9 / 30.f));

	sprite->setAnimationSpeed(JUMP_TOP_RIGHT, 8);
	sprite->addKeyframe(JUMP_TOP_RIGHT, glm::vec2(3.f / 8.f, 7.9 / 30.f));

	sprite->setAnimationSpeed(APPEAR, 3);
	sprite->addKeyframe(APPEAR, glm::vec2(0, 0));
	sprite->addKeyframe(APPEAR, glm::vec2(1.f / 8.f, 0));
	sprite->addKeyframe(APPEAR, glm::vec2(2.f / 8.f, 0));
	sprite->addKeyframe(APPEAR, glm::vec2(3.f / 8.f, 0));
	sprite->addKeyframe(APPEAR, glm::vec2(4.f / 8.f, 0));
	sprite->addKeyframe(APPEAR, glm::vec2(5.f / 8.f, 0));

	sprite->setAnimationSpeed(CLIMB11, 8);
	sprite->addKeyframe(CLIMB11, glm::vec2(0, 6.8 / 30.f));

	sprite->setAnimationSpeed(CLIMB12, 8);
	sprite->addKeyframe(CLIMB12, glm::vec2(1.f / 8.f, 6.8 / 30.f));

	sprite->setAnimationSpeed(CLIMB21, 8);
	sprite->addKeyframe(CLIMB21, glm::vec2(2.f / 8.f, 6.8 / 30.f));

	sprite->setAnimationSpeed(CLIMB22, 8);
	sprite->addKeyframe(CLIMB22, glm::vec2(3.f / 8.f, 6.8 / 30.f));

	sprite->setAnimationSpeed(LAND, 5);
	sprite->addKeyframe(LAND, glm::vec2(4.f / 8.f, 6.8 / 30.f));
	sprite->addKeyframe(LAND, glm::vec2(5.f / 8.f, 6.8 / 30.f));

	sprite->setAnimationSpeed(DAMAGE_LEFT, 8);
	sprite->addKeyframe(DAMAGE_LEFT, glm::vec2(2.f / 8.f, 17.9 / 30.f));
	sprite->addKeyframe(DAMAGE_LEFT, glm::vec2(1.f / 8.f, 17.9 / 30.f));

	sprite->setAnimationSpeed(DAMAGE_RIGHT, 8);
	sprite->addKeyframe(DAMAGE_RIGHT, glm::vec2(5.f / 8.f, 2.9 / 30.f));
	sprite->addKeyframe(DAMAGE_RIGHT, glm::vec2(6.f / 8.f, 2.9 / 30.f));

	sprite->changeAnimation(12);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}


void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch (state)
	{
		case DAMAGE: {
			cont += deltaTime;
			if (sprite->animation() != DAMAGE_RIGHT && sprite->animation() != DAMAGE_LEFT) {
				if (isRight)
					sprite->changeAnimation(DAMAGE_RIGHT);
				else
					sprite->changeAnimation(DAMAGE_LEFT);
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				posPlayer.x -= 2;
				if (isRight)
					sprite->changeAnimation(DAMAGE_LEFT);
				isRight = false;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
					posPlayer.x += 2;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				posPlayer.x += 2;
				if (!isRight)
					sprite->changeAnimation(DAMAGE_RIGHT);
				isRight = true;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
					posPlayer.x -= 2;
			}
			
			if (cont >= 500) {
				state = STANDING;
				isDamaged = false;
			}

		} break;

		case START: {
			cont += deltaTime;
			if (cont >= 1900) {
				state = STANDING;
				isAnimation = false;
			}
		} break;

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
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * (jumpAngle + 4 * JUMP_ANGLE_STEP) / 180.f));
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32))) {
				posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * (jumpAngle - JUMP_ANGLE_STEP) / 180.f));
				state = FALLING;
				jumpAngle = 90;
			}
			else
				posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * (jumpAngle + JUMP_ANGLE_STEP) / 180.f));
			
		} break;

		case FALLING: {
			if (jumpAngle <= 150) {
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
			jumpAngle += JUMP_ANGLE_STEP;

		} break;

		case CLIMBING: {
			cont += deltaTime;
			if (cont >= 250) {
				if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
					if (sprite->animation() == CLIMB11)
						sprite->changeAnimation(CLIMB12);
					else if (sprite->animation() == CLIMB12)
						sprite->changeAnimation(CLIMB21);
					else if (sprite->animation() == CLIMB21)
						sprite->changeAnimation(CLIMB22);
					else
						sprite->changeAnimation(CLIMB11);
					cont = 0;
				}
				else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
					if (sprite->animation() == CLIMB11)
						sprite->changeAnimation(CLIMB12);
					else if (sprite->animation() == CLIMB12)
						sprite->changeAnimation(CLIMB21);
					else if (sprite->animation() == CLIMB21)
						sprite->changeAnimation(CLIMB22);
					else
						sprite->changeAnimation(CLIMB11);
					cont = 0;
				}
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
				posPlayer.x -= 1;
				if (map->collisionMoveStairs(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x += 1;
				}
				else if (!map->isStairs(posPlayer, glm::ivec2(32, 32))) {
					isClimbing = false;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
				posPlayer.x += 1;
				if (map->collisionMoveStairs(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x -= 1;
				}
				else if (!map->isStairs(posPlayer, glm::ivec2(32, 32))) {
					isClimbing = false;
				}
			}
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				posPlayer.y -= 1;
				if (!map->isStairs(glm::ivec2(posPlayer.x, posPlayer.y-20), glm::ivec2(32, 32))) {
					state = LANDING;
					sprite->changeAnimation(LAND);
					cont = 0;
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
				posPlayer.y += 1;
				if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
					isClimbing = false;
					state = STANDING;
				}
			}
		} break;

		case LANDING: {
			cont += deltaTime;
			if (cont >= 500) {
				state = STANDING;
				isClimbing = false;
				posPlayer.y -= 20;
			}
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
			if (map->checkDamage(posPlayer, glm::ivec2(32, 32)))
			{
				isDamaged = true;
				state = DAMAGE;
				cont = 0;
			}
			else
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
			if (map->checkDamage(posPlayer, glm::ivec2(32, 32)))
			{
				isDamaged = true;
				state = DAMAGE;
				cont = 0;
			}
			else 
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
			if (map->checkDamage(posPlayer, glm::ivec2(32, 32)))
			{
				cont = 0;
				isDamaged = true;
				state = DAMAGE;
			}
		} break;

	}

	if (!isAnimation && !bJumping && !isClimbing && !isDamaged)
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
			if (Game::instance().getSpecialKey(GLUT_KEY_UP) && map->isStairs(posPlayer, glm::ivec2(32, 32))) {
				state = CLIMBING;
				isClimbing = true;
				cont = 0;
				sprite->changeAnimation(CLIMB11);
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				state = JUMPING;
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && map->isStairs(glm::ivec2(posPlayer.x, posPlayer.y + 2), glm::ivec2(32, 32)))
			{
				posPlayer.y += 20;
				state = CLIMBING;
				isClimbing = true;
				cont = 0;
				sprite->changeAnimation(CLIMB11);
			}
		}
		else {
			state = FALLING;
			bJumping = true;
			jumpAngle = 90;
		}

	}

	map->updatePositionTile(posPlayer, glm::ivec2(32, 32), posAnt, 2);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

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