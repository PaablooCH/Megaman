#include "Level1.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 24
#define INIT_PLAYER_Y_TILES 13


Level1::Level1()
{
	enemy1 = NULL;
	enemy2 = NULL;
	enemy3 = NULL;
	fire1 = NULL;
	fire2 = NULL;
	virus1 = NULL;
	virus2 = NULL;
	senemy2 = NULL;
	chip1 = NULL;
	chip2 = NULL;
	bonus1 = NULL;
	bonus2 = NULL;
}

Level1::~Level1()
{
	if (enemy1 != NULL) {
		enemy1->~LinealEnemy();
		delete enemy1;
		enemy1 = nullptr;
	}

	if (enemy3 != NULL) {
		enemy3->~LinealEnemy();
		delete enemy3;
		enemy3 = nullptr;
	}

	if (enemy2 != NULL) {
		enemy2->~LinealEnemy();
		delete enemy2;
		enemy2 = nullptr;
	}
		
	if (fire1 != NULL) {
		fire1->~Fire();
		delete fire1;
		fire1 = nullptr;
	}
		
	if (fire2 != NULL) {
		fire2->~Fire();
		delete fire2;
		fire2 = nullptr;
	}
		
	if (virus1 != NULL) {
		virus1->~Virus();
		delete virus1;
		virus1 = nullptr;
	}

	if (virus2 != NULL) {
		virus2->~Virus();
		delete virus2;
		virus2 = nullptr;
	}
		
	if (senemy2 != NULL) {
		senemy2->~ShootEnemy();
		delete senemy2;
		senemy2 = nullptr;
	}
		
	if (chip1 != NULL) {
		chip1->~Chip();
		delete chip1;
		chip1 = nullptr;
	}

	if (chip2 != NULL) {
		chip2->~Chip();
		delete chip2;
		chip2 = nullptr;
	}
		
	if (bonus1 != NULL) {
		bonus1->~Bonus();
		delete bonus1;
		bonus1 = nullptr;
	}

	if (bonus2 != NULL) {
		bonus2->~Bonus();
		delete bonus2;
		bonus2 = nullptr;
	}
		
}

void Level1::init(Player* player, int selectPortal)
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	playerStats = new PlayerStats();
	playerStats->init(glm::ivec2(posCamera.x, posCamera.y), texProgram);
	this->player = player;
	this->player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	this->player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	this->player->setTileMap(map);
	this->player->setPlayerStats(playerStats);
	enemy1 = new LinealEnemy();
	enemy1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(6 * map->getTileSize(), 28 * map->getTileSize()), 20);
	enemy1->setPosition(glm::vec2(6 * map->getTileSize(), 28 * map->getTileSize()));
	enemy1->setTileMap(map);
	enemy1->setPlayer(this->player);
	enemy2 = new LinealEnemy();
	enemy2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(37 * map->getTileSize(), 40 * map->getTileSize()), 21);
	enemy2->setPosition(glm::vec2(37 * map->getTileSize(), 40 * map->getTileSize()));
	enemy2->setTileMap(map);
	enemy2->setPlayer(this->player);
	enemy3 = new LinealEnemy();
	enemy3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 42 * map->getTileSize()), 22);
	enemy3->setPosition(glm::vec2(58 * map->getTileSize(), 42 * map->getTileSize()));
	enemy3->setTileMap(map);
	enemy3->setPlayer(this->player);
	fire1 = new Fire();
	fire1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 13 * map->getTileSize()), 30);
	fire1->setPosition(glm::vec2(58 * map->getTileSize(), 13 * map->getTileSize()));
	fire1->setTileMap(map);
	fire2 = new Fire();
	fire2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 54 * map->getTileSize()), 31);
	fire2->setPosition(glm::vec2(58 * map->getTileSize(), 54 * map->getTileSize()));
	fire2->setTileMap(map);
	virus1 = new Virus();
	virus1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(9 * map->getTileSize(), 10 * map->getTileSize()), 40);
	virus1->setPosition(glm::vec2( 9* map->getTileSize(), 10 * map->getTileSize()));
	virus1->setTileMap(map);
	virus2 = new Virus();
	virus2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(46 * map->getTileSize(), 49 * map->getTileSize()), 41);
	virus2->setPosition(glm::vec2( 46 * map->getTileSize(), 49 * map->getTileSize()));
	virus2->setTileMap(map);
	teleport1 = new Teleport();
	teleport1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(53 * map->getTileSize(), 13 * map->getTileSize()), 2);
	teleport1->setPosition(glm::vec2(53 * map->getTileSize(), 13 * map->getTileSize()));
	teleport1->setTileMap(map);
	teleport1->setPlayer(player);
	if (!player->isAGirl(0)) {
		girl1 = new RescueGirl();
		girl1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(52 * map->getTileSize(), 54 * map->getTileSize()));
		girl1->setPosition(glm::vec2(52 * map->getTileSize(), 54 * map->getTileSize()));
		girl1->setTileMap(map);
		girl1->setPlayerStats(playerStats);
	}
	if (!player->isAKey(0)) {
		key1 = new Key();
		key1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 18 * map->getTileSize()), 50);
		key1->setPosition(glm::vec2(58 * map->getTileSize(), 18 * map->getTileSize()));
		key1->setTileMap(map);
	}
	senemy2 = new ShootEnemy();
	senemy2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(49 * map->getTileSize(), 19 * map->getTileSize()), 90);
	senemy2->setPosition(glm::vec2(49 * map->getTileSize(), 19 * map->getTileSize()));
	senemy2->setTileMap(map);
	senemy2->setPlayer(this->player);
	chip1 = new Chip();
	chip1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(36 * map->getTileSize(), 14 * map->getTileSize()), 70);
	chip1->setPosition(glm::vec2(36 * map->getTileSize(), 14 * map->getTileSize()));
	chip1->setTileMap(map);
	chip2 = new Chip();
	chip2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(36 * map->getTileSize(), 50 * map->getTileSize()), 71);
	chip2->setPosition(glm::vec2(36 * map->getTileSize(), 50 * map->getTileSize()));
	chip2->setTileMap(map);
	bonus1 = new Bonus();
	bonus1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 18 * map->getTileSize()), 80, "Shoot");
	bonus1->setPosition(glm::vec2(7 * map->getTileSize(), 18 * map->getTileSize()));
	bonus1->setTileMap(map);
	if (!player->isPowerUp(0)) {
		bonus2 = new Bonus();
		bonus2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(33 * map->getTileSize(), 40 * map->getTileSize()), 81, "Bambas");
		bonus2->setPosition(glm::vec2(33 * map->getTileSize(), 40 * map->getTileSize()));
		bonus2->setTileMap(map);
	}
	posCamera = glm::vec2(0, 0);
	projection = glm::ortho(posCamera.x, posCamera.x + SCREEN_WIDTH - 1, posCamera.y + SCREEN_HEIGHT - 1, posCamera.y);
	currentTime = 0.0f;
}

void Level1::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	if (enemy1 != nullptr) deleteEnemy();
	if (enemy1 != nullptr) enemy1->update(deltaTime);
	if (enemy2 != nullptr) deleteEnemy2();
	if (enemy2 != nullptr) enemy2->update(deltaTime);
	if(enemy3 != nullptr) deleteEnemy3();
	if (enemy3 != nullptr) enemy3->update(deltaTime);
	fire1->update(deltaTime);
	fire2->update(deltaTime);
	if (virus1 != nullptr) deleteVirus();
	if (virus1 != nullptr) virus1->update(deltaTime);
	if (virus2 != nullptr) deleteVirus2();
	if (virus2 != nullptr) virus2->update(deltaTime);
	teleport1->update(deltaTime);
	if (girl1 != nullptr && girl1->checkState()) {
		player->loseKey();
		deleteGirl1();
	}
	if (girl1 != nullptr) girl1->update(deltaTime);
	if (key1 != nullptr) deleteKey1();
	if (key1 != nullptr) key1->update(deltaTime);
	if (senemy2 != nullptr) deleteSEnemy();
	if (senemy2 != nullptr) senemy2->update(deltaTime);
	if (chip1 != nullptr) deleteChip();
	if (chip1 != nullptr) chip1->update(deltaTime);
	if (chip2 != nullptr) deleteChip2();
	if (chip2 != nullptr) chip2->update(deltaTime);
	if (bonus1 != nullptr) deleteBonus();
	if (bonus1 != nullptr) bonus1->update(deltaTime);
	if (bonus2 != nullptr) deleteBonus2();
	if (bonus2 != nullptr) bonus2->update(deltaTime);
	updateCamera();
	if (posCamera.y > 0)
		playerStats->setPosition(glm::vec2(float(posCamera.x), float(posCamera.y + 28 * 16)));
	else
		playerStats->setPosition(posCamera);
}

void Level1::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	teleport1->render();
	if (girl1 != NULL)girl1->render();
	player->render();
	if (enemy1 != NULL)enemy1->render();
	if (enemy2 != NULL)enemy2->render();
	if (enemy3 != NULL)enemy3->render();
	fire1->render();
	fire2->render();
	if (virus1 != NULL)virus1->render();
	if (virus2 != NULL)virus2->render();
	if (key1 != NULL)key1->render();
	if (senemy2 != NULL)senemy2->render();
	if (chip1 != NULL)chip1->render();
	if (chip2 != NULL)chip2->render();
	if (bonus1 != NULL)bonus1->render();
	if (bonus2 != NULL)bonus2->render();
	playerStats->render();
}

void Level1::deleteVirus()
{
	if (!virus1->checkAlive()) {
		virus1->~Virus();
		delete virus1;
		virus1 = nullptr;
	}
}

void Level1::deleteVirus2()
{
	if (!virus2->checkAlive()) {
		virus2->~Virus();
		delete virus2;
		virus2 = nullptr;
	}
}

void Level1::deleteEnemy()
{
	if (!enemy1->checkAlive()) {
		enemy1->~LinealEnemy();
		delete enemy1;
		enemy1 = nullptr;
		player->winExp();
	}
}

void Level1::deleteEnemy2()
{
	if (!enemy2->checkAlive()) {
		enemy2->~LinealEnemy();
		delete enemy2;
		enemy2 = nullptr;
		player->winExp();
	}
}

void Level1::deleteEnemy3()
{
	if (!enemy3->checkAlive()) {
		enemy3->~LinealEnemy();
		delete enemy3;
		enemy3 = nullptr;
		player->winExp();
	}
}

void Level1::deleteChip()
{
	if (chip1->checkState()) {
		chip1->~Chip();
		delete chip1;
		chip1 = nullptr;
		player->winExp();
	}
}

void Level1::deleteChip2()
{
	if (chip2->checkState()) {
		chip2->~Chip();
		delete chip2;
		chip2 = nullptr;
		player->winExp();
	}
}

void Level1::deleteSEnemy()
{
	if (!senemy2->checkAlive()) {
		senemy2->~ShootEnemy();
		delete senemy2;
		senemy2 = nullptr;
		player->winExp();
	}
}

void Level1::deleteBonus()
{
	if (bonus1->checkState()) {
		player->bonusShoot();
		bonus1->~Bonus();
		delete bonus1;
		bonus1 = nullptr;
	}
}

void Level1::deleteBonus2()
{
	if (bonus2->checkState()) {
		player->bonusBoots();
		bonus2->~Bonus();
		delete bonus2;
		bonus2 = nullptr;
	}
}