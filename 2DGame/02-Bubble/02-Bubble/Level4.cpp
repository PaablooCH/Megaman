#include "Level4.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 24
#define INIT_PLAYER_Y_TILES 13


Level4::Level4()
{
	enemy1 = NULL;
	fire1 = NULL;
	fire2 = NULL;
	virus1 = NULL;
	fakeRoof1 = NULL;
	senemy2 = NULL;
	chip1 = NULL;
	bonus1 = NULL;
}

Level4::~Level4()
{
	if (enemy1 != NULL) {
		enemy1->~LinealEnemy();
		delete enemy1;
		enemy1 = nullptr;
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

	if (fakeRoof1 != NULL) {
		fakeRoof1->~FakeRoof();
		delete fakeRoof1;
		fakeRoof1 = nullptr;
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

	if (bonus1 != NULL) {
		bonus1->~Bonus();
		delete bonus1;
		bonus1 = nullptr;
	}

}

void Level4::init(Player* player)
{
	initShaders();
	map = TileMap::createTileMap("levels/level04.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	playerStats = new PlayerStats();
	playerStats->init(glm::ivec2(posCamera.x, posCamera.y), texProgram);
	this->player = player;
	this->player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	this->player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	this->player->setTileMap(map);
	this->player->setPlayerStats(playerStats);
	enemy1 = new LinealEnemy();
	enemy1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()), 20);
	enemy1->setPosition(glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()));
	enemy1->setTileMap(map);
	enemy1->setPlayer(this->player);
	fire1 = new Fire();
	fire1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 13 * map->getTileSize()), 30);
	fire1->setPosition(glm::vec2(58 * map->getTileSize(), 13 * map->getTileSize()));
	fire1->setTileMap(map);
	fire2 = new Fire();
	fire2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 54 * map->getTileSize()), 31);
	fire2->setPosition(glm::vec2(58 * map->getTileSize(), 54 * map->getTileSize()));
	fire2->setTileMap(map);
	virus1 = new Virus();
	virus1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 10 * map->getTileSize()), 40);
	virus1->setPosition(glm::vec2(7 * map->getTileSize(), 10 * map->getTileSize()));
	virus1->setTileMap(map);
	teleport1 = new Teleport();
	teleport1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(53 * map->getTileSize(), 13 * map->getTileSize()), 2);
	teleport1->setPosition(glm::vec2(53 * map->getTileSize(), 13 * map->getTileSize()));
	teleport1->setTileMap(map);
	teleport1->setPlayer(player);
	if (!player->isAGirl(1)) {
		girl1 = new RescueGirl();
		girl1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(52 * map->getTileSize(), 54 * map->getTileSize()));
		girl1->setPosition(glm::vec2(52 * map->getTileSize(), 54 * map->getTileSize()));
		girl1->setTileMap(map);
		girl1->setPlayerStats(playerStats);
	}
	if (!player->isAKey(1)) {
		key1 = new Key();
		key1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(49 * map->getTileSize(), 20 * map->getTileSize()), 50);
		key1->setPosition(glm::vec2(49 * map->getTileSize(), 20 * map->getTileSize()));
		key1->setTileMap(map);
	}
	fakeRoof1 = new FakeRoof(1);
	fakeRoof1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(12 * map->getTileSize(), 8 * map->getTileSize()), 60);
	fakeRoof1->setPosition(glm::vec2(12 * map->getTileSize(), 8 * map->getTileSize()));
	fakeRoof1->setTileMap(map);
	senemy2 = new ShootEnemy();
	senemy2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(21 * map->getTileSize(), 27 * map->getTileSize()), 80);
	senemy2->setPosition(glm::vec2(21 * map->getTileSize(), 27 * map->getTileSize()));
	senemy2->setTileMap(map);
	senemy2->setPlayer(this->player);
	chip1 = new Chip();
	chip1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * map->getTileSize(), 23 * map->getTileSize()), 70);
	chip1->setPosition(glm::vec2(16 * map->getTileSize(), 23 * map->getTileSize()));
	chip1->setTileMap(map);
	bonus1 = new Bonus();
	bonus1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(4 * map->getTileSize(), 28 * map->getTileSize()), 90, "Shoot");
	bonus1->setPosition(glm::vec2(4 * map->getTileSize(), 28 * map->getTileSize()));
	bonus1->setTileMap(map);
	posCamera = glm::vec2(0, 0);
	projection = glm::ortho(posCamera.x, posCamera.x + SCREEN_WIDTH - 1, posCamera.y + SCREEN_HEIGHT - 1, posCamera.y);
	currentTime = 0.0f;
}

void Level4::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	if (enemy1 != nullptr) deleteEnemy();
	if (enemy1 != nullptr) enemy1->update(deltaTime);
	fire1->update(deltaTime);
	fire2->update(deltaTime);
	if (virus1 != nullptr) deleteVirus();
	if (virus1 != nullptr) virus1->update(deltaTime);
	teleport1->update(deltaTime);
	if (girl1 != nullptr && girl1->checkState()) {
		player->loseKey();
		deleteGirl1();
	}
	if (girl1 != nullptr) girl1->update(deltaTime);
	if (key1 != nullptr) deleteKey1();
	if (key1 != nullptr) key1->update(deltaTime);
	fakeRoof1->update(deltaTime);
	if (senemy2 != nullptr) deleteSEnemy();
	if (senemy2 != nullptr) senemy2->update(deltaTime);
	if (chip1 != nullptr) deleteChip();
	if (chip1 != nullptr) chip1->update(deltaTime);
	if (bonus1 != nullptr) deleteBonus();
	if (bonus1 != nullptr) bonus1->update(deltaTime);
	updateCamera();
	if (posCamera.y > 0)
		playerStats->setPosition(glm::vec2(float(posCamera.x), float(posCamera.y + 28 * 16)));
	else
		playerStats->setPosition(posCamera);
}

void Level4::render()
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
	fire1->render();
	fire2->render();
	if (virus1 != NULL)virus1->render();
	if (key1 != NULL)key1->render();
	fakeRoof1->render();
	if (senemy2 != NULL)senemy2->render();
	if (chip1 != NULL)chip1->render();
	if (bonus1 != NULL)bonus1->render();
	playerStats->render();
}

void Level4::deleteVirus()
{
	if (!virus1->checkAlive()) {
		virus1->~Virus();
		delete virus1;
		virus1 = nullptr;
	}
}

void Level4::deleteEnemy()
{
	if (!enemy1->checkAlive()) {
		enemy1->~LinealEnemy();
		delete enemy1;
		enemy1 = nullptr;
		player->winExp();
	}
}

void Level4::deleteChip()
{
	if (chip1->checkState()) {
		chip1->~Chip();
		delete chip1;
		chip1 = nullptr;
		player->winExp();
	}
}

void Level4::deleteSEnemy()
{
	if (!senemy2->checkAlive()) {
		senemy2->~ShootEnemy();
		senemy2->deleteBullets();
		delete senemy2;
		senemy2 = nullptr;
		player->winExp();
	}
}

void Level4::deleteBonus()
{
	if (bonus1->checkState()) {
		if (bonus1->checkType() == "Bambas")player->bonusBoots();
		if (bonus1->checkType() == "Casco")player->bonusHelmet();
		if (bonus1->checkType() == "Bateria")player->bonusBattery();
		if (bonus1->checkType() == "Libro")player->bonusBook();
		if (bonus1->checkType() == "Escudo")player->bonusArmor();
		if (bonus1->checkType() == "Shoot")player->bonusShoot();
		bonus1->~Bonus();
		delete bonus1;
		bonus1 = nullptr;
	}
}