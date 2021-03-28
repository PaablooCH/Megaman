#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 8


Scene::Scene()
{
	map = NULL;
	player = NULL;
	enemy1 = NULL;
	fire1 = NULL;
	virus1 = NULL;
	teleport1 = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (enemy1 != NULL)
		delete enemy1;
	if (fire1 != NULL)
		delete fire1;
	if (virus1 != NULL)
		delete virus1;
	if (teleport1 != NULL)
		delete teleport1;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	enemy1 = new LinealEnemy();
	enemy1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(15 * map->getTileSize(), 12 * map->getTileSize()));
	enemy1->setPosition(glm::vec2(15 * map->getTileSize(), 12 * map->getTileSize()));
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
	teleport1->setPosition(glm::vec2(33 * map->getTileSize(), 9 * map->getTileSize()));
	teleport1->setTileMap(map);
	teleport1->setPlayer(player);
	posCamera = glm::vec2(0, 0);
	//projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
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

	updateCamera();
}

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

void Scene::render()
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
	
}

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