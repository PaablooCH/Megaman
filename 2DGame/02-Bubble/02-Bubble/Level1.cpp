#include "Level1.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 26
#define INIT_PLAYER_Y_TILES 13


Level1::Level1()
{
	enemy1 = NULL;
	fire1 = NULL;
	virus1 = NULL;
	cascade1 = NULL;
	chip1 = NULL;
}

Level1::~Level1()
{
	if (enemy1 != NULL)
		delete enemy1;
	if (fire1 != NULL)
		delete fire1;
	if (virus1 != NULL)
		delete virus1;
	if (cascade1 != NULL)
		delete cascade1;
	if (chip1 != NULL)
		delete chip1;
}

void Level1::init(Player* player)
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	playerStats = new PlayerStats();
	playerStats->init(glm::ivec2(posCamera.x, posCamera.y), texProgram);
	this->player = player;
	this->player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	this->player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	this->player->setTileMap(map);
	this->player->setPlayerStats(playerStats);
	enemy1 = new LinealEnemy();
	enemy1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()));
	enemy1->setPosition(glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()));
	enemy1->setTileMap(map);
	enemy1->setPlayer(this->player);
	fire1 = new Fire();
	fire1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(35 * map->getTileSize(), 13 * map->getTileSize()));
	fire1->setPosition(glm::vec2(35 * map->getTileSize(), 15 * map->getTileSize()));
	fire1->setTileMap(map);
	virus1 = new Virus();
	virus1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 11 * map->getTileSize()));
	virus1->setPosition(glm::vec2(7 * map->getTileSize(), 11 * map->getTileSize()));
	virus1->setTileMap(map);
	teleport1 = new Teleport();
	teleport1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(33 * map->getTileSize(), 9 * map->getTileSize()), glm::vec2(6 * map->getTileSize(), 8 * map->getTileSize()));
	teleport1->setPosition(glm::vec2(33 * map->getTileSize(), 12 * map->getTileSize()));
	teleport1->setTileMap(map);
	teleport1->setPlayer(player);
	girl1 = new RescueGirl();
	girl1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(52 * map->getTileSize(), 54 * map->getTileSize()));
	girl1->setPosition(glm::vec2(52 * map->getTileSize(), 54 * map->getTileSize()));
	girl1->setTileMap(map);
	girl1->setPlayerStats(playerStats);
	key1 = new Key();
	key1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(49 * map->getTileSize(), 20 * map->getTileSize()));
	key1->setPosition(glm::vec2(49 * map->getTileSize(), 20 * map->getTileSize()));
	key1->setTileMap(map);
	key1->setPlayerStats(playerStats);
	cascade1 = new Cascade();
	cascade1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(39 * map->getTileSize(), 31 * map->getTileSize()));
	cascade1->setPosition(glm::vec2(39 * map->getTileSize(), 31 * map->getTileSize()));
	cascade1->setTileMap(map);
	chip1 = new Chip();
	chip1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * map->getTileSize(), 23 * map->getTileSize()));
	chip1->setPosition(glm::vec2(16 * map->getTileSize(), 23 * map->getTileSize()));
	chip1->setTileMap(map);
	chip1->setPlayerStats(playerStats);
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
	fire1->update(deltaTime);
	if (virus1 != nullptr) deleteVirus();
	if (virus1 != nullptr) virus1->update(deltaTime);
	teleport1->update(deltaTime);
	girl1->update(deltaTime);
	key1->update(deltaTime);
	cascade1->update(deltaTime);
	chip1->update(deltaTime);
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
	player->render();
	if (enemy1 != NULL)enemy1->render();
	fire1->render();
	if (virus1 != NULL)virus1->render();
	if (girl1->checkState())girl1->render();
	if (!key1->checkState())key1->render();
	if (cascade1->checkAlive())cascade1->render();
	if (!chip1->checkState())chip1->render();
	playerStats->render();
}

void Level1::deleteVirus()
{
	if (!virus1->checkAlive()) {
		virus1 = nullptr;
		delete virus1;
	}
}

void Level1::deleteEnemy()
{
	if (!enemy1->checkAlive()) {
		enemy1 = nullptr;
		delete enemy1;
	}
}