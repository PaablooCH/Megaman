#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define FALL_STEP 4

enum States
{
	HITTING, JUMPING, CLIMBING, STANDING, MOVING_LEFT, MOVING_RIGHT, FALLING, START, LANDING, DAMAGE, TELEPORT, DEAD, SHOOTING
} state;

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, HIT_LEFT, HIT_RIGHT, JUMP_LEFT1, JUMP_LEFT2, JUMP_RIGHT1, JUMP_RIGHT2, JUMP_TOP_LEFT, JUMP_TOP_RIGHT, APPEAR,
	CLIMB11, CLIMB12, CLIMB21, CLIMB22, LAND, DAMAGE_LEFT, DAMAGE_RIGHT, DISAPPEAR, SHOOTING_LEFT, SHOOTING_RIGHT
};

enum DeadAnims
{
	DEAD_RIGHT1, DEAD_RIGHT2, DEAD_LEFT1, DEAD_LEFT2
};

Player::Player()
{
	powerUp = new bool[5]{ false, false, false, false, false };
	keys = new bool[6]{ false, false, false, false, false, false };
	girlRescued = new bool[6]{ false, false, false, false, false, false };
	health = 20;
	exp = 10;
	nkeys = 0;
	speed = 2;
	jump_height = 55;
	hasHelmet = false;
	life_damage = 2;
	exp_obtained = 1;
	bullets_cont = 0;
}

Player::~Player()
{
}

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int lvl)
{
	this->lvl = lvl;
	bJumping = false;
	isClimbing = false;
	isHitting = false;
	isDamaged = false;
	isDead = false;
	state = START;
	cont = 0;
	isAnimation = true;
	isRight = true;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(35, 38), glm::vec2(1.f / 8.f, 1.f / 30.9), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(23);

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

	sprite->setAnimationSpeed(DISAPPEAR, 3);
	sprite->addKeyframe(DISAPPEAR, glm::vec2(5.f / 8.f, 0));
	sprite->addKeyframe(DISAPPEAR, glm::vec2(4.f / 8.f, 0));
	sprite->addKeyframe(DISAPPEAR, glm::vec2(3.f / 8.f, 0));
	sprite->addKeyframe(DISAPPEAR, glm::vec2(2.f / 8.f, 0));
	sprite->addKeyframe(DISAPPEAR, glm::vec2(1.f / 8.f, 0));
	sprite->addKeyframe(DISAPPEAR, glm::vec2(0, 0));

	sprite->setAnimationSpeed(SHOOTING_LEFT, 7);
	//sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(7.f / 8.f, 17.9 / 30.f));
	//sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(6.f / 8.f, 17.9 / 30.f));
	sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(7.f / 8.f, 16.9 / 30.f));
	sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(6.f / 8.f, 16.9 / 30.f));
	sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(5.f / 8.f, 16.9 / 30.f));
	sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(6.f / 8.f, 17.9 / 30.f));
	sprite->addKeyframe(SHOOTING_LEFT, glm::vec2(7.f / 8.f, 17.9 / 30.f));


	sprite->setAnimationSpeed(SHOOTING_RIGHT, 7);
	//sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(0.f, 2.9 / 30.f));
	//sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(1.f / 8.f, 2.9 / 30.f));
	sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(0.f, 1.9 / 30.f));
	sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(1.f / 8.f, 1.9 / 30.f));
	sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(2.f / 8.f, 1.9 / 30.f));
	sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(1.f / 8.f, 2.9 / 30.f));
	sprite->addKeyframe(SHOOTING_RIGHT, glm::vec2(0.f, 2.9 / 30.f));


	sprite->changeAnimation(12);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	spriteDead = Sprite::createSprite(glm::ivec2(35, 38), glm::vec2(42.f / 396.f, 56.f / 1534.f), &spritesheet, &shaderProgram);
	spriteDead->setNumberAnimations(4);

	spriteDead->setAnimationSpeed(DEAD_RIGHT1, 10);
	spriteDead->addKeyframe(DEAD_RIGHT1, glm::vec2(354.f / 396.f, 716.f / 1534.f));

	spriteDead->setAnimationSpeed(DEAD_RIGHT2, 8);
	spriteDead->addKeyframe(DEAD_RIGHT2, glm::vec2(254.f / 396.f, 716.f / 1534.f));

	spriteDead->setAnimationSpeed(DEAD_LEFT1, 10);
	spriteDead->addKeyframe(DEAD_LEFT1, glm::vec2(0.f / 396.f, 1478.f / 1534.f));

	spriteDead->setAnimationSpeed(DEAD_LEFT2, 8);
	spriteDead->addKeyframe(DEAD_LEFT2, glm::vec2(100.f / 396.f, 1478.f / 1534.f));

	spriteDead->changeAnimation(3);
	spriteDead->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	bulletLeft = new Bullet();
	bulletLeft->init(glm::ivec2(tileMapDispl.x, tileMapDispl.y), shaderProgram, 2, 2);

	bulletRight = new Bullet();
	bulletRight->init(glm::ivec2(tileMapDispl.x, tileMapDispl.y), shaderProgram, 2, 2);

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	bulletLeft->update(deltaTime);
	bulletRight->update(deltaTime);
	switch (state)
	{

	case DEAD: {
		if (cont == 0) {
			if (isRight)
				spriteDead->changeAnimation(DEAD_RIGHT1);
			else
				spriteDead->changeAnimation(DEAD_LEFT1);
		}
		cont += deltaTime;
		if (cont >= 1000) {
			if (spriteDead->animation() == DEAD_RIGHT1)
				spriteDead->changeAnimation(DEAD_RIGHT2);
			else if (spriteDead->animation() == DEAD_LEFT1)
				spriteDead->changeAnimation(DEAD_LEFT2);
			isAnimation = false;
		}
	} break;

	case DAMAGE: {
		if (cont == 0)
			health -= life_damage;
		if (health <= 0) {
			isAnimation = true;
			state = DEAD;
			isDead = true;
			cont = 0;
		}
		else {
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

			if (cont >= 650) {
				state = STANDING;
				isDamaged = false;
			}
		}

	} break;

	case START: {
		if (sprite->animation() != APPEAR)
			sprite->changeAnimation(APPEAR);
		cont += deltaTime;
		isAnimation = true;
		if (cont >= 1900) {
			state = STANDING;
			isAnimation = false;
		}
	} break;

	case TELEPORT: {
		if (sprite->animation() != DISAPPEAR)
			sprite->changeAnimation(DISAPPEAR);
		cont += deltaTime;
		if (cont >= 1900) {
			isAnimation = false;
			state = STANDING;
		}
	} break;

	case HITTING: {
		cont += deltaTime;
		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT) {
			sprite->changeAnimation(HIT_LEFT);
			isHitting = true;
		}
		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT) {
			sprite->changeAnimation(HIT_RIGHT);
			isHitting = true;;
		}
		if (cont >= 250) {
			state = STANDING;
			isHitting = false;
		}
	} break;

	case SHOOTING: {
		cont += deltaTime;
		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT) {
			sprite->changeAnimation(SHOOTING_LEFT);
			if(bullets_cont >= 1)bulletLeft->addBullet(glm::ivec2(posPlayer.x, posPlayer.y + 10), false);
			if (bullets_cont > 0) --bullets_cont;

		}
		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT) {
			sprite->changeAnimation(SHOOTING_RIGHT);
			if (bullets_cont >= 1)bulletRight->addBullet(glm::ivec2(posPlayer.x + 16, posPlayer.y + 10), true);
			if (bullets_cont > 0) --bullets_cont;
		}
		if (cont >= 500) {
			state = STANDING;
		}
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
		else if (jumpAngle <= 80) {
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
			posPlayer.x -= speed;
			isRight = false;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
				posPlayer.x += speed;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			posPlayer.x += speed;
			isRight = true;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
				posPlayer.x -= speed;
		}
		posPlayer.y = int(startY - jump_height * sin(3.14159f * (jumpAngle + JUMP_ANGLE_STEP) / 180.f));
		if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32))) {
			posPlayer.y = int(startY - jump_height * sin(3.14159f * (jumpAngle - JUMP_ANGLE_STEP) / 180.f));
			state = FALLING;
			jumpAngle = 90;
		}
		else
			posPlayer.y = int(startY - jump_height * sin(3.14159f * (jumpAngle + JUMP_ANGLE_STEP) / 180.f));
		if (map->checkDamage(posPlayer, glm::ivec2(8, 32), hasHelmet)) //Hablar esto
		{
			cont = 0;
			isDamaged = true;
			state = DAMAGE;
			bJumping = false; //hacer que se quede statico cuando sea golpeado aire
		}

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
			posPlayer.x -= speed;
			isRight = false;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
				posPlayer.x += speed;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			posPlayer.x += speed;
			isRight = true;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
				posPlayer.x -= speed;
		}
		bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		if (!bJumping)
			state = STANDING;
		if (map->checkDamage(posPlayer, glm::ivec2(8, 32), hasHelmet)) //Hablar esto
		{
			cont = 0;
			isDamaged = true;
			state = DAMAGE;
			bJumping = false; // hacer que se quede statico
		}
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
			if (map->collisionMoveStairsLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 1;
			}
			else if (!map->isStairs(posPlayer, glm::ivec2(32, 32))) {
				isClimbing = false;
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			posPlayer.x += 1;
			if (map->collisionMoveStairsRight(posPlayer, glm::ivec2(32, 32)))
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

			if (!map->isStairs(glm::ivec2(posPlayer.x, posPlayer.y - 20), glm::ivec2(32, 32))) {
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
		posPlayer.x -= speed;
		isRight = false;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += speed;
			sprite->changeAnimation(STAND_LEFT);
		}
		if (map->checkDamage(posPlayer, glm::ivec2(7, 32), hasHelmet))
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
		posPlayer.x += speed;
		isRight = true;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= speed;
			sprite->changeAnimation(STAND_RIGHT);
		}
		if (map->checkDamage(posPlayer, glm::ivec2(16, 32), hasHelmet))
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
			if (map->checkDamage(posPlayer, glm::ivec2(8, 32), hasHelmet))
			{
				cont = 0;
				isDamaged = true;
				state = DAMAGE;
			}
		}
		else {
			sprite->changeAnimation(STAND_RIGHT);
			isRight = true;
			if (map->checkDamage(posPlayer, glm::ivec2(16, 32), hasHelmet))
			{
				cont = 0;
				isDamaged = true;
				state = DAMAGE;
			}
		}
	} break;

	}

	if (!isAnimation && !bJumping && !isClimbing && !isDamaged && !isDead)
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
			else if (Game::instance().getSpecialKey(GLUT_KEY_INSERT))
			{
				state = SHOOTING;
				cont = 0;
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
	if (!isAnimation && !isDead)
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y))); //vigilar
	else if (isDead)
		spriteDead->setPosition((glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y))));
	playerStats->update(health, exp, girlRescued, nkeys, powerUp, bullets_cont);
}

void Player::render()
{
	if (!isDead)
		sprite->render();
	else
		spriteDead->render();
	bulletLeft->render();
	bulletRight->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
	bulletLeft->setTileMap(tileMap);
	bulletRight->setTileMap(tileMap);
}

void Player::setPlayerStats(PlayerStats* pStats)
{
	playerStats = pStats;
	playerStats->update(health, exp, girlRescued, nkeys, powerUp, bullets_cont);
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	if (!isDead)
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	else
		spriteDead->setPosition((glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y))));
}

void Player::teleport(int lvl)
{
	isAnimation = true;
	cont = 0;
	state = TELEPORT;
	this->lvl = lvl;
	posPlayer = glm::vec2(float(0), float(0));
}

bool Player::checkHit()
{
	return isHitting;
}

bool Player::checkRight()
{
	return isRight;
}

void Player::winExp()
{
	exp += exp_obtained;
	if (exp == 21) {
		if (health < 20)
			health += 2;
		else if (health == 19)
			health++;
		exp = 1;
	}
}

void Player::winKey()
{
	keys[lvl - 1] = true;
	nkeys++;
}

void Player::loseKey()
{
	nkeys--;
	girlRescued[lvl - 1] = true;
}

bool Player::isAnAnimation() {
	return isAnimation;
}

int Player::getLvl() {
	return lvl;
}

bool Player::isAGirl(int lvl) {
	return girlRescued[lvl - 1];
}

bool Player::isAKey(int lvl) {
	return keys[lvl - 1];
}

void Player::bonusBoots() {
	powerUp[0] = true;
	speed = 3;
}

void Player::bonusBattery() {
	powerUp[1] = true;
	jump_height = 92;
}

void Player::bonusHelmet() {
	powerUp[2] = true;
	hasHelmet = true;
}

void Player::bonusArmor() {
	powerUp[3] = true;
	life_damage = 1;
}

void Player::bonusBook() {
	powerUp[4] = true;
	exp_obtained = 2;
}

void Player::bonusShoot() {
	bullets_cont = 5;
}