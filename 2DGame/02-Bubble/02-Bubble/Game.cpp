#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void Game::init()
{
	bPlay = true;
	lvl = 0;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	player = new Player();
	//level1 = new Level1();
	//level1->init(player);
	//level2 = new Level2();
	//level2->init(player);
}

bool Game::update(int deltaTime)
{
	switch (lvl)
	{
	case 0: {
		if (menu == NULL) {
			menu = new Menu();
			menu->init();
		}
		menu->update(deltaTime);
	} break;
	case 1: {
		if (level1 == NULL) {
			level1 = new Level1();
			level1->init(player);
		}
		level1->update(deltaTime);
	} break;
	case 2: {
		if (level2 == NULL) {
			level2 = new Level2();
			level2->init(player);
		}
		level2->update(deltaTime);
	} break;
	case 3: {

	} break;
	case 4: {

	} break;
	case 5: {

	} break;
	}

	//level2->update(deltaTime);
	changeLvl();
	restart();
	return bPlay;
}

void Game::restart()
{
	if (player->getDead()) {
		if (!player->isAnAnimation()) {
			player->~Player();
			delete player;
			player = nullptr;
			destroyLvl();
			init();
		}
	}
}

void Game::changeLvl()
{
	int newLvl;
	if (lvl == 0) {
		if (menu->getPlay()) {
			destroyLvl();
			lvl = 1;
		}
	}
	else if (!player->isAnAnimation()) {
		newLvl = player->getLvl();
		if (newLvl != lvl) {
			destroyLvl();
			lvl = newLvl;
		}
	}

}

void Game::destroyLvl()
{
	switch (lvl)
	{
	case 0: {
		if (menu != NULL) {
			menu->~Menu();
			delete menu;
			menu = nullptr;
		}
	} break;
	case 1: {
		if (level1 != NULL) {
			level1->~Level1();
			delete level1;
			level1 = nullptr;
		}
	} break;
	case 2: {
		if (level2 != NULL) {
			level2->~Level2();
			delete level2;
			level2 = nullptr;
		}
	} break;
	case 3: {

	} break;
	case 4: {

	} break;
	case 5: {

	} break;
	}
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (lvl)
	{
	case 0: {
		if (menu != NULL)
			menu->render();
	} break;
	case 1: {
		if (level1 != NULL)
			level1->render();
	} break;
	case 2: {
		if (level2 != NULL)
			level2->render();
	} break;
	case 3: {

	} break;
	case 4: {
		;
	} break;
	case 5: {

	} break;
	}
	//level1->render();
	//level2->render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}