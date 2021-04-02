#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 26
#define INIT_PLAYER_Y_TILES 13


Scene::Scene()
{
	map = NULL;
	player = NULL;
	teleport1 = NULL;
	girl1 = NULL;
	key1 = NULL;
	playerStats = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (teleport1 != NULL)
		delete teleport1;
	if (girl1 != NULL)
		delete girl1;
	if (key1 != NULL)
		delete key1;
	if (playerStats != NULL)
		delete playerStats;
}
/*
void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	playerStats = new PlayerStats();
	playerStats->init(glm::ivec2(posCamera.x, posCamera.y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	player->setPlayerStats(playerStats);
	enemy1 = new LinealEnemy();
	enemy1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()));
	enemy1->setPosition(glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()));
	enemy1->setTileMap(map);
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
	key1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(49 * map->getTileSize(), 19 * map->getTileSize()));
	key1->setPosition(glm::vec2(49 * map->getTileSize(), 19 * map->getTileSize()));
	key1->setTileMap(map);
	key1->setPlayerStats(playerStats);
	posCamera = glm::vec2(0, 0);
	projection = glm::ortho(posCamera.x, posCamera.x + SCREEN_WIDTH - 1, posCamera.y + SCREEN_HEIGHT - 1, posCamera.y);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	enemy1->update(deltaTime);
	fire1->update(deltaTime);
	virus1->update(deltaTime);
	teleport1->update(deltaTime);
	girl1->update(deltaTime);
	key1->update(deltaTime);
	updateCamera();
	if(posCamera.y>0)
		playerStats->setPosition(glm::vec2(float(posCamera.x), float(posCamera.y + 28*16)));
	else
		playerStats->setPosition(posCamera);
}*/

void Scene::updateCamera()
{
	glm::vec2 playerpos = player->getPosPlayer();
	if (playerpos.x > posCamera.x + SCREEN_WIDTH)
		posCamera.x += SCREEN_WIDTH;
	else if (playerpos.x < posCamera.x)
		posCamera.x -= SCREEN_WIDTH;

	if (playerpos.y > posCamera.y + SCREEN_HEIGHT)
		posCamera.y += SCREEN_HEIGHT;
	else if (playerpos.y < posCamera.y)
		posCamera.y -= SCREEN_HEIGHT;
	projection = glm::ortho(posCamera.x, posCamera.x + SCREEN_WIDTH - 1, posCamera.y + SCREEN_HEIGHT - 1, posCamera.y);
}

/*void Scene::render()
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
	enemy1->render();
	fire1->render();
	if (!virus1->checkAlive())virus1->render();
	if (girl1->checkState())girl1->render();
	if (!key1->checkState())key1->render();
	playerStats->render();
	
}
*/
void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::deleteGirl1()
{
	if (girl1->checkState()) {
		girl1 = nullptr;
		delete girl1;
	}
}

void Scene::deleteKey1()
{
	if (key1->checkState()) {
		key1 = nullptr;
		delete key1;
		player->winKey();
	}
}
