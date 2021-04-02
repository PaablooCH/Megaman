#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	lvl = 1;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
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
	return bPlay;
}

void Game::changeLvl()
{
	int newLvl;
	if (!player->isAnAnimation()) {
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
		case 1: {
			level1->~Level1();
			level1 = nullptr;
			delete level1;
		} break;
		case 2: {
			level2->~Level2();
			level2 = nullptr;
			delete level2;
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
	case 1: {
		if(level1 != NULL)
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
	if(key == 27) // Escape code
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





