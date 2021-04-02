#include "Level2.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 26
#define INIT_PLAYER_Y_TILES 13

Level2::Level2()
{
}

Level2::~Level2()
{
}

void Level2::init(Player* player)
{
	initShaders();
	map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	playerStats = new PlayerStats();
	playerStats->init(glm::ivec2(posCamera.x, posCamera.y), texProgram);
	this->player = player;
	this->player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2);
	this->player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	this->player->setTileMap(map);
	this->player->setPlayerStats(playerStats);
	teleport1 = new Teleport();
	teleport1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(53 * map->getTileSize(), 13 * map->getTileSize()), 1);
	teleport1->setPosition(glm::vec2(53 * map->getTileSize(), 13 * map->getTileSize()));
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
	posCamera = glm::vec2(0, 0);
	projection = glm::ortho(posCamera.x, posCamera.x + SCREEN_WIDTH - 1, posCamera.y + SCREEN_HEIGHT - 1, posCamera.y);
	currentTime = 0.0f;
}

void Level2::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	teleport1->update(deltaTime);
	if (girl1 != nullptr && girl1->checkState()) {
		player->loseKey();
		deleteGirl1();
	}
	if (girl1 != nullptr) girl1->update(deltaTime);
	if (key1 != nullptr) deleteKey1();
	if (key1 != nullptr) key1->update(deltaTime);
	updateCamera();
	if (posCamera.y > 0)
		playerStats->setPosition(glm::vec2(float(posCamera.x), float(posCamera.y + 28 * 16)));
	else
		playerStats->setPosition(posCamera);
}

void Level2::render()
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
	if (key1 != NULL)key1->render();
	playerStats->render();
}
