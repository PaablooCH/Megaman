#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "ShootEnemy.h"

ShootEnemy::ShootEnemy() {
	cont = 0;
	protect = false;
	isAlive = true;
}

ShootEnemy::~ShootEnemy() {
	if (sprite != NULL) {
		delete sprite;
		sprite = nullptr;
	}
	if (bulletLeft != NULL) {
		bulletLeft->deleteAll();
		delete bulletLeft;
		bulletLeft = nullptr;
	}
	if (bulletRight != NULL) {
		bulletRight->deleteAll();
		delete bulletRight;
		bulletRight = nullptr;
	}
}

enum ShootState
{
	SHOOTING_LEFT, SHOOTING_RIGHT, PROTECTING_LEFT, PROTECTING_RIGHT, STANDING_RIGHT, STANDING_LEFT
} states;

enum EnemyAnims
{
	SHOT_LEFT, SHOT_RIGHT, PROTECT_LEFT, PROTECT_RIGHT, STAND_RIGHT, STAND_LEFT
};


void ShootEnemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id)
{
	states = PROTECTING_RIGHT;
	spritesheet.loadFromFile("images/ShotEnemy.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(47.f / 306.f, 45.f / 194.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(SHOT_RIGHT, 5);
	sprite->addKeyframe(SHOT_RIGHT, glm::vec2(112.f / 306.f, 52.f / 194.f));
	sprite->addKeyframe(SHOT_RIGHT, glm::vec2(159.f / 306.f, 52.f / 194.f));
	sprite->addKeyframe(SHOT_RIGHT, glm::vec2(208.f / 306.f, 52.f / 194.f));
	sprite->addKeyframe(SHOT_RIGHT, glm::vec2(258.f / 306.f, 51.f / 194.f));
	sprite->addKeyframe(SHOT_RIGHT, glm::vec2(112.f / 306.f, 52.f / 194.f));


	sprite->setAnimationSpeed(SHOT_LEFT, 5);
	sprite->addKeyframe(SHOT_LEFT, glm::vec2(147.f / 306.f, 149.f / 194.f));
	sprite->addKeyframe(SHOT_LEFT, glm::vec2(100.f / 306.f, 149.f / 194.f));
	sprite->addKeyframe(SHOT_LEFT, glm::vec2(51.f / 306.f, 149.f / 194.f));
	sprite->addKeyframe(SHOT_LEFT, glm::vec2(1.f / 306.f, 148.f / 194.f));
	sprite->addKeyframe(SHOT_LEFT, glm::vec2(147.f / 306.f, 149.f / 194.f));

	sprite->setAnimationSpeed(PROTECT_RIGHT, 3);
	sprite->addKeyframe(PROTECT_RIGHT, glm::vec2(2.f / 306.f, 0.f / 194.f));
	sprite->addKeyframe(PROTECT_RIGHT, glm::vec2(52.f / 306.f, 0.f / 194.f));
	sprite->addKeyframe(PROTECT_RIGHT, glm::vec2(103.f / 306.f, 0.f / 194.f));

	sprite->setAnimationSpeed(PROTECT_LEFT, 3);
	sprite->addKeyframe(PROTECT_LEFT, glm::vec2(257.f / 306.f, 97.f / 194.f));
	sprite->addKeyframe(PROTECT_LEFT, glm::vec2(207.f / 306.f, 97.f / 194.f));
	sprite->addKeyframe(PROTECT_LEFT, glm::vec2(156.f / 306.f, 97.f / 194.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 1);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(112.f / 306.f, 52.f / 194.f));

	sprite->setAnimationSpeed(STAND_LEFT, 1);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(147.f / 306.f, 149.f / 194.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	ID = id;
	sprite->setPosition(posInicial);

	bulletLeft = new Bullet();
	bulletLeft->init(glm::ivec2(tileMapDispl.x, tileMapDispl.y), shaderProgram, ID, 1);

	bulletRight = new Bullet();
	bulletRight->init(glm::ivec2(tileMapDispl.x, tileMapDispl.y), shaderProgram, ID, 1);

}

void ShootEnemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	bulletLeft->update(deltaTime);
	bulletRight->update(deltaTime);
	posAnt = posEnemy;
	cont += deltaTime;
	switch (states) {
	case STANDING_LEFT: {
		if (sprite->animation() != STAND_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		if (map->checkPlayerRight(posEnemy, glm::ivec2(23, 32)))
		{
			if (!player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkPlayerLeft(posEnemy, glm::ivec2(23, 32)))
		{
			if (player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkEnemyBulletDamage(posEnemy, glm::ivec2(16, 32)))
		{
			isAlive = false;
			map->clearPosition(ID);
		}
		if (cont >= 1000) {
			states = PROTECTING_LEFT;
			cont = 0;
		}
	} break;

	case STANDING_RIGHT: {
		if (sprite->animation() != STAND_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		if (map->checkPlayerRight(posEnemy, glm::ivec2(23, 32)))
		{
			if (!player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkPlayerLeft(posEnemy, glm::ivec2(23, 32)))
		{
			if (player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkEnemyBulletDamage(posEnemy, glm::ivec2(16, 32)))
		{
			isAlive = false;
			map->clearPosition(ID);
		}
		if (cont >= 1000) {
			states = PROTECTING_RIGHT;
			cont = 0;
		}
	} break;

	case SHOOTING_RIGHT: {
		if (sprite->animation() != SHOT_RIGHT)
			sprite->changeAnimation(SHOT_RIGHT);
		bulletRight->addBullet(glm::ivec2((posEnemy.x + 16), (posEnemy.y + 8)), true);
		if (map->checkPlayerRight(posEnemy, glm::ivec2(23, 32)))
		{
			if (!player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkPlayerLeft(posEnemy, glm::ivec2(23, 32)))
		{
			if (player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkEnemyBulletDamage(posEnemy, glm::ivec2(16, 32)))
		{
			isAlive = false;
			map->clearPosition(ID);
		}
		if (cont >= 100) {
			states = STANDING_RIGHT;
			cont = 0;
		}
	} break;

	case SHOOTING_LEFT: {
		if (sprite->animation() != SHOT_LEFT)
			sprite->changeAnimation(SHOT_LEFT);
		protect = false;
		bulletLeft->addBullet(glm::ivec2((posEnemy.x), (posEnemy.y + 8)), false);
		if (map->checkPlayerRight(posEnemy, glm::ivec2(23, 32)))
		{
			if (!player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkPlayerLeft(posEnemy, glm::ivec2(23, 32)))
		{
			if (player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (map->checkEnemyBulletDamage(posEnemy, glm::ivec2(16, 32)))
		{
			isAlive = false;
			map->clearPosition(ID);
		}
		if (cont >= 100) {
			states = STANDING_LEFT;
			cont = 0;
		}
	} break;

	case PROTECTING_RIGHT: {
		if (sprite->animation() != PROTECT_RIGHT)
			sprite->changeAnimation(PROTECT_RIGHT);
		int r = rand() % 300;
		if (map->checkPlayerLeft(posEnemy, glm::ivec2(23, 32)))
		{
			if (player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (cont >= 2500 ) {
			states = SHOOTING_RIGHT;
			cont = 0;
		}
		if (r == 50) {
			states = SHOOTING_LEFT;
			cont = 0;
		}
	} break;

	case PROTECTING_LEFT: {
		if (sprite->animation() != PROTECT_LEFT)
			sprite->changeAnimation(PROTECT_LEFT);
		int r = rand() % 300;
		if (map->checkPlayerRight(posEnemy, glm::ivec2(23, 32)))
		{
			if (!player->checkRight()) {
				if (player->checkHit()) {
					isAlive = false;
					map->clearPosition(ID);
				}
			}
		}
		if (cont >= 2500) {
			states = SHOOTING_LEFT;
			cont = 0;
		}
		if (r == 50) {
			states = SHOOTING_RIGHT;
			cont = 0;
		}
	} break;
	}

	map->updatePositionTile(posEnemy, glm::ivec2(32, 32), posAnt, ID);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void ShootEnemy::render()
{
	sprite->render();
	bulletLeft->render();
	bulletRight->render();
}

void ShootEnemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
	bulletLeft->setTileMap(tileMap);
	bulletRight->setTileMap(tileMap);
}

void ShootEnemy::setPlayer(Player* p)
{
	player = p;
}

void ShootEnemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

bool ShootEnemy::checkAlive() { return isAlive; }

void ShootEnemy::deleteBullets() {
	bulletLeft->deleteAll();
	bulletRight->deleteAll();
}
