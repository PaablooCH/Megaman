#include "Level3.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 9
#define INIT_PLAYER_Y_TILES 54


Level3::Level3()
{
	enemy1 = NULL;
	enemy2 = NULL;
	enemy3 = NULL;
	enemy4 = NULL;
	fire1 = NULL;
	fire2 = NULL;
	fire3 = NULL;
	fire4 = NULL;
	fire5 = NULL;
	virus1 = NULL;
	virus2 = NULL;
	fakeRoof1 = NULL;
	fakeRoof2 = NULL;
	senemy2 = NULL;
	chip1 = NULL;
	chip2 = NULL;	
	chip3 = NULL;
	chip4 = NULL;
	bonus1 = NULL;
	bonus2 = NULL;
}

Level3::~Level3()
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

	if (enemy4 != NULL) {
		enemy4->~LinealEnemy();
		delete enemy4;
		enemy4 = nullptr;
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

	if (fire3 != NULL) {
		fire3->~Fire();
		delete fire3;
		fire3 = nullptr;
	}

	if (fire4 != NULL) {
		fire4->~Fire();
		delete fire4;
		fire4 = nullptr;
	}

	if (fire5 != NULL) {
		fire5->~Fire();
		delete fire5;
		fire5 = nullptr;
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

	if (fakeRoof1 != NULL) {
		fakeRoof1->~FakeRoof();
		delete fakeRoof1;
		fakeRoof1 = nullptr;
	}

	if (fakeRoof2 != NULL) {
		fakeRoof2->~FakeRoof();
		delete fakeRoof2;
		fakeRoof2 = nullptr;
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

	if (chip3 != NULL) {
		chip3->~Chip();
		delete chip3;
		chip3 = nullptr;
	}

	if (chip4 != NULL) {
		chip4->~Chip();
		delete chip4;
		chip4 = nullptr;
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

void Level3::init(Player* player, int selectPortal)
{
	initShaders();
	map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	playerStats = new PlayerStats();
	playerStats->init(glm::ivec2(posCamera.x, posCamera.y), texProgram);
	this->player = player;
	this->player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3);
	this->player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	this->player->setTileMap(map);
	this->player->setPlayerStats(playerStats);
	enemy1 = new LinealEnemy();
	enemy1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(19 * map->getTileSize(), 48 * map->getTileSize()), 20);
	enemy1->setPosition(glm::vec2(19 * map->getTileSize(), 48 * map->getTileSize()));
	enemy1->setTileMap(map);
	enemy1->setPlayer(this->player);
	enemy2 = new LinealEnemy();
	enemy2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(13 * map->getTileSize(), 42 * map->getTileSize()), 21);
	enemy2->setPosition(glm::vec2(13 * map->getTileSize(), 42 * map->getTileSize()));
	enemy2->setTileMap(map);
	enemy2->setPlayer(this->player);
	enemy3 = new LinealEnemy();
	enemy3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(11 * map->getTileSize(), 20 * map->getTileSize()), 22);
	enemy3->setPosition(glm::vec2(11 * map->getTileSize(), 20 * map->getTileSize()));
	enemy3->setTileMap(map);
	enemy3->setPlayer(this->player);
	enemy4 = new LinealEnemy();
	enemy4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(44 * map->getTileSize(), 27 * map->getTileSize()), 23);
	enemy4->setPosition(glm::vec2(44 * map->getTileSize(), 27 * map->getTileSize()));
	enemy4->setTileMap(map);
	enemy4->setPlayer(this->player);
	senemy2 = new ShootEnemy();
	senemy2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(45 * map->getTileSize(), 16 * map->getTileSize()), 90);
	senemy2->setPosition(glm::vec2(45 * map->getTileSize(), 16 * map->getTileSize()));
	senemy2->setTileMap(map);
	senemy2->setPlayer(this->player);
	fire1 = new Fire();
	fire1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(28 * map->getTileSize(), 42 * map->getTileSize()), 30);
	fire1->setPosition(glm::vec2(28 * map->getTileSize(), 42 * map->getTileSize()));
	fire1->setTileMap(map);
	fire2 = new Fire();
	fire2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(28 * map->getTileSize(), 9 * map->getTileSize()), 31);
	fire2->setPosition(glm::vec2(28 * map->getTileSize(), 9 * map->getTileSize()));
	fire2->setTileMap(map);
	fire3 = new Fire();
	fire3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(59 * map->getTileSize(), 16 * map->getTileSize()), 32);
	fire3->setPosition(glm::vec2(59 * map->getTileSize(), 16 * map->getTileSize()));
	fire3->setTileMap(map);
	fire4 = new Fire();
	fire4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(59 * map->getTileSize(), 10 * map->getTileSize()), 33);
	fire4->setPosition(glm::vec2(59 * map->getTileSize(), 10 * map->getTileSize()));
	fire4->setTileMap(map);
	fire5 = new Fire();
	fire5->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(28 * map->getTileSize(), 27 * map->getTileSize()), 34);
	fire5->setPosition(glm::vec2(28 * map->getTileSize(), 27 * map->getTileSize()));
	fire5->setTileMap(map);
	virus1 = new Virus();
	virus1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(19 * map->getTileSize(), 51 * map->getTileSize()), 40);
	virus1->setPosition(glm::vec2(19 * map->getTileSize(), 51 * map->getTileSize()));
	virus1->setTileMap(map);
	virus2 = new Virus();
	virus2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(5 * map->getTileSize(), 12 * map->getTileSize()), 41);
	virus2->setPosition(glm::vec2(5 * map->getTileSize(), 12 * map->getTileSize()));
	virus2->setTileMap(map);
	teleport1 = new Teleport();
	teleport1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 54 * map->getTileSize()), 2);
	teleport1->setPosition(glm::vec2(7 * map->getTileSize(), 54 * map->getTileSize()));
	teleport1->setTileMap(map);
	teleport1->setPlayer(player);
	teleport2 = new Teleport();
	teleport2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 27 * map->getTileSize()), 4);
	teleport2->setPosition(glm::vec2(58 * map->getTileSize(), 27 * map->getTileSize()));
	teleport2->setTileMap(map);
	teleport2->setPlayer(player);
	if (!player->isAGirl(2)) {
		girl1 = new RescueGirl();
		girl1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 9 * map->getTileSize()));
		girl1->setPosition(glm::vec2(7 * map->getTileSize(), 9 * map->getTileSize()));
		girl1->setTileMap(map);
		girl1->setPlayerStats(playerStats);
	}
	if (!player->isAKey(2)) {
		key1 = new Key();
		key1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(58 * map->getTileSize(), 23 * map->getTileSize()), 50);
		key1->setPosition(glm::vec2(58 * map->getTileSize(), 23 * map->getTileSize()));
		key1->setTileMap(map);
	}
	fakeRoof1 = new FakeRoof(3);
	fakeRoof1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(42 * map->getTileSize(), 4 * map->getTileSize()), 60);
	fakeRoof1->setPosition(glm::vec2(42 * map->getTileSize(), 4 * map->getTileSize()));
	fakeRoof1->setTileMap(map);
	fakeRoof2 = new FakeRoof(3);
	fakeRoof2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(50 * map->getTileSize(), 4 * map->getTileSize()), 61);
	fakeRoof2->setPosition(glm::vec2(50 * map->getTileSize(), 4 * map->getTileSize()));
	fakeRoof2->setTileMap(map);
	chip1 = new Chip();
	chip1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(22 * map->getTileSize(), 55 * map->getTileSize()), 70);
	chip1->setPosition(glm::vec2(22 * map->getTileSize(), 55 * map->getTileSize()));
	chip1->setTileMap(map);
	chip2 = new Chip();
	chip2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(47 * map->getTileSize(), 23 * map->getTileSize()), 71);
	chip2->setPosition(glm::vec2(47 * map->getTileSize(), 23 * map->getTileSize()));
	chip2->setTileMap(map);
	chip3 = new Chip();
	chip3->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(53 * map->getTileSize(), 23 * map->getTileSize()), 72);
	chip3->setPosition(glm::vec2(55 * map->getTileSize(), 23 * map->getTileSize()));
	chip3->setTileMap(map);
	chip4 = new Chip();
	chip4->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(46 * map->getTileSize(), 11 * map->getTileSize()), 73);
	chip4->setPosition(glm::vec2(46 * map->getTileSize(), 11 * map->getTileSize()));
	chip4->setTileMap(map);
	if (!player->isPowerUp(1)) {
		bonus1 = new Bonus();
		bonus1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(7 * map->getTileSize(), 16 * map->getTileSize()), 80, "Bateria");
		bonus1->setPosition(glm::vec2(7 * map->getTileSize(), 16 * map->getTileSize()));
		bonus1->setTileMap(map);
	}
	bonus2 = new Bonus();
	bonus2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(18 * map->getTileSize(), 28 * map->getTileSize()), 81, "Shoot");
	bonus2->setPosition(glm::vec2(18 * map->getTileSize(), 28 * map->getTileSize()));
	bonus2->setTileMap(map);
	posCamera = glm::vec2(0, 0);
	projection = glm::ortho(posCamera.x, posCamera.x + SCREEN_WIDTH - 1, posCamera.y + SCREEN_HEIGHT - 1, posCamera.y);
	currentTime = 0.0f;
}

void Level3::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	if (enemy1 != nullptr) deleteEnemy();
	if (enemy1 != nullptr) enemy1->update(deltaTime);
	if (enemy4 != nullptr) deleteEnemy4();
	if (enemy4 != nullptr) enemy4->update(deltaTime);
	if (enemy2 != nullptr) deleteEnemy2();
	if (enemy2 != nullptr) enemy2->update(deltaTime);
	if (enemy3 != nullptr) deleteEnemy3();
	if (enemy3 != nullptr) enemy3->update(deltaTime);
	fire1->update(deltaTime);
	fire2->update(deltaTime);
	fire3->update(deltaTime);
	fire4->update(deltaTime);
	fire5->update(deltaTime);
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
	fakeRoof1->update(deltaTime);
	fakeRoof2->update(deltaTime);
	if (senemy2 != nullptr) deleteSEnemy();
	if (senemy2 != nullptr) senemy2->update(deltaTime);
	if (chip1 != nullptr) deleteChip();
	if (chip1 != nullptr) chip1->update(deltaTime);
	if (chip2 != nullptr) deleteChip2();
	if (chip2 != nullptr) chip2->update(deltaTime);
	if (chip3 != nullptr) deleteChip3();
	if (chip3 != nullptr) chip3->update(deltaTime);
	if (chip4 != nullptr) deleteChip4();
	if (chip4 != nullptr) chip4->update(deltaTime);
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

void Level3::render()
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
	if (enemy4 != NULL)enemy4->render();
	fire1->render();
	fire2->render();
	fire3->render();
	fire4->render();
	fire5->render();
	if (virus1 != NULL)virus1->render();
	if (virus2 != NULL)virus2->render();
	if (key1 != NULL)key1->render();
	fakeRoof1->render();
	fakeRoof2->render();
	if (senemy2 != NULL)senemy2->render();
	if (chip1 != NULL)chip1->render();
	if (chip2 != NULL)chip2->render();
	if (chip3 != NULL)chip3->render();
	if (chip4 != NULL)chip4->render();
	if (bonus1 != NULL)bonus1->render();
	if (bonus2 != NULL)bonus2->render();
	playerStats->render();
}

void Level3::deleteVirus()
{
	if (!virus1->checkAlive()) {
		virus1->~Virus();
		delete virus1;
		virus1 = nullptr;
	}
}

void Level3::deleteVirus2()
{
	if (!virus2->checkAlive()) {
		virus2->~Virus();
		delete virus2;
		virus2 = nullptr;
	}
}

void Level3::deleteEnemy()
{
	if (!enemy1->checkAlive()) {
		enemy1->~LinealEnemy();
		delete enemy1;
		enemy1 = nullptr;
		player->winExp();
	}
}

void Level3::deleteEnemy4()
{
	if (!enemy4->checkAlive()) {
		enemy4->~LinealEnemy();
		delete enemy4;
		enemy4 = nullptr;
		player->winExp();
	}
}

void Level3::deleteEnemy2()
{
	if (!enemy2->checkAlive()) {
		enemy2->~LinealEnemy();
		delete enemy2;
		enemy2 = nullptr;
		player->winExp();
	}
}

void Level3::deleteEnemy3()
{
	if (!enemy3->checkAlive()) {
		enemy3->~LinealEnemy();
		delete enemy3;
		enemy3 = nullptr;
		player->winExp();
	}
}

void Level3::deleteChip()
{
	if (chip1->checkState()) {
		chip1->~Chip();
		delete chip1;
		chip1 = nullptr;
		player->winExp();
	}
}

void Level3::deleteChip2()
{
	if (chip2->checkState()) {
		chip2->~Chip();
		delete chip2;
		chip2 = nullptr;
		player->winExp();
	}
}

void Level3::deleteChip3()
{
	if (chip3->checkState()) {
		chip3->~Chip();
		delete chip3;
		chip3 = nullptr;
		player->winExp();
	}
}

void Level3::deleteChip4()
{
	if (chip4->checkState()) {
		chip4->~Chip();
		delete chip4;
		chip4 = nullptr;
		player->winExp();
	}
}

void Level3::deleteSEnemy()
{
	if (!senemy2->checkAlive()) {
		senemy2->~ShootEnemy();
		delete senemy2;
		senemy2 = nullptr;
		player->winExp();
	}
}

void Level3::deleteBonus()
{
	if (bonus1->checkState()) {
		player->bonusBattery();
		bonus1->~Bonus();
		delete bonus1;
		bonus1 = nullptr;
	}
}

void Level3::deleteBonus2()
{
	if (bonus2->checkState()) {
		player->bonusShoot();
		bonus2->~Bonus();
		delete bonus2;
		bonus2 = nullptr;
	}
}