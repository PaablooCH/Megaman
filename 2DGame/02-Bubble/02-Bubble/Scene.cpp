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
	if (map != NULL) {
		map->~TileMap();
		delete map;
		map = nullptr;
	}
		
	if (teleport1 != NULL) {
		teleport1->~Teleport();
		delete teleport1;
		teleport1 = nullptr;
	}
		
	if (girl1 != NULL) {
		girl1->~RescueGirl();
		delete girl1;
		girl1 = nullptr;
	}
		
	if (key1 != NULL) {
		key1->~Key();
		delete key1;
		key1 = nullptr;
	}
		
	if (playerStats != NULL) {
		playerStats->~PlayerStats();
		delete playerStats;
		playerStats = nullptr;
	}
		
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
