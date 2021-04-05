#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void Game::init()
{
	bPlay = true;
	lvl = 0;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	player = new Player();
	selectPortal = 1;
	cont = 0;
}

bool Game::update(int deltaTime)
{
	cont += deltaTime;
	switch (lvl)
	{
	case 0: {
		if (menu == NULL) {
			menu = new Menu();
			menu->init(0);
		}
		menu->update(deltaTime);
		changeLvl();
	} break;
	case 1: {
		if (level1 == NULL) {
			level1 = new Level1();
			level1->init(player, selectPortal);
		}
		level1->update(deltaTime);
		if (cont >= 250) {
			cheatPowerUp();
			cheatBullet();
			cheatGirl();
			cheatLvl();
			cheatGOD();
		}
		changeLvl();
		restart();
		isAWin();
	} break;
	case 2: {
		if (level2 == NULL) {
			level2 = new Level2();
			level2->init(player, selectPortal);
		}
		level2->update(deltaTime);
		if (cont >= 250) {
			cheatPowerUp();
			cheatBullet();
			cheatGirl();
			cheatLvl();
			cheatGOD();
		}
		changeLvl();
		restart();
		isAWin();
	} break;
	case 3: {
		if (level3 == NULL) {
			level3 = new Level3();
			level3->init(player, selectPortal);
		}
		level3->update(deltaTime);
		if (cont >= 250) {
			cheatPowerUp();
			cheatBullet();
			cheatGirl();
			cheatLvl();
			cheatGOD();
		}
		changeLvl();
		restart();
		isAWin();
	} break;
	case 4: {
		if (level4 == NULL) {
			level4 = new Level4();
			level4->init(player, selectPortal);
		}
		level4->update(deltaTime);
		if (cont >= 250) {
			cheatPowerUp();
			cheatBullet();
			cheatGirl();
			cheatLvl();
			cheatGOD();
		}
		changeLvl();
		restart();
		isAWin();
	} break;
	case 5: {
		if (level5 == NULL) {
			level5 = new Level5();
			level5->init(player, selectPortal);
		}
		level5->update(deltaTime);
		if (cont >= 250) {
			cheatPowerUp();
			cheatBullet();
			cheatGirl();
			cheatLvl();
			cheatGOD();
		}
		changeLvl();
		restart();
		isAWin();
	} break;
	}

	//level2->update(deltaTime);
	return bPlay;
}

void Game::isAWin()
{
	if (player->isAWin()) {
		player->~Player();
		delete player;
		player = nullptr;
		destroyLvl();
		lvl = 0;
		if (menu == NULL) {
			menu = new Menu();
			menu->init(7);
		}
	}
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
			selectPortal = 1;
		}
	}
	else if (!player->isAnAnimation()) {
		newLvl = player->getLvl();
		if (newLvl != lvl) {
			getPortal(newLvl);
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
		if (level3 != NULL) {
			level3->~Level3();
			delete level3;
			level3 = nullptr;
		}
	} break;
	case 4: {
		if (level4 != NULL) {
			level4->~Level4();
			delete level4;
			level4 = nullptr;
		}
	} break;
	case 5: {
		if (level5 != NULL) {
			level5->~Level5();
			delete level5;
			level5 = nullptr;
		}
	} break;
	}
}

void Game::getPortal(int newLvl)
{
	switch (newLvl)
	{
	case 1: {
		selectPortal = 2;
	} break;
	case 2: {
		if (lvl == 1)
			selectPortal = 1;
		else selectPortal = 2;
	} break;
	case 3: {
		if (lvl == 2)
			selectPortal = 1;
		else
			selectPortal = 2;
	} break;
	case 4: {
		if (lvl == 3)
			selectPortal = 1;
		else
			selectPortal = 2;
	} break;
	case 5: {
		if (lvl == 4)
			selectPortal = 1;
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
		if (level3 != NULL)
			level3->render();
	} break;
	case 4: {
		if (level4 != NULL)
			level4->render();
	} break;
	case 5: {
		if (level5 != NULL)
			level5->render();
	} break;
	}
	//level1->render();
	//level2->render();
}

void Game::cheatPowerUp()
{
	if (getKey(GLUT_B) || getKey(GLUT_b)) {
		player->winBonus();
		cont = 0;
	}
}

void Game::cheatBullet()
{
	if (getKey(GLUT_V) || getKey(GLUT_v)) {
		cont = 0;
		player->winBullets();
	}
}

void Game::cheatGirl()
{
	if (getKey(GLUT_C) || getKey(GLUT_c)) {
		cont = 0;
		player->winGirl();
	}
}

void Game::cheatLvl()
{
	if (getKey(GLUT_1) && lvl != 1) {
		cont = 0;
		player->changeLvl(1);
	}
	else if (getKey(GLUT_2) && lvl != 2) {
		cont = 0;
		player->changeLvl(2);
	}
	else if (getKey(GLUT_3) && lvl != 3) {
		cont = 0;
		player->changeLvl(3);
	}
	else if (getKey(GLUT_4) && lvl != 4) {
		cont = 0;
		player->changeLvl(4);
	}
	else if (getKey(GLUT_5) && lvl != 5) {
		cont = 0;
		player->changeLvl(5);
	}
}

void Game::cheatGOD()
{
	if (getKey(GLUT_g) || getKey(GLUT_G)) {
		cont = 0;
		player->becomeGod();
	}
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