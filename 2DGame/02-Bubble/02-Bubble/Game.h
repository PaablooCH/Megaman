#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Level1.h"
#include "Player.h"
#include "Level2.h"
#include "Menu.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"


#define SCREEN_WIDTH 496
#define SCREEN_HEIGHT 496


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}

	static Game& instance()
	{
		static Game G;

		return G;
	}

	void init();
	bool update(int deltaTime);
	void isAWin();
	void restart();
	void changeLvl();
	void destroyLvl();
	void getPortal(int newLvl);
	void render();

	void cheatPowerUp();
	void cheatBullet();
	void cheatGirl();
	void cheatLvl();
	void cheatGOD();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	Player* player;
	int lvl, selectPortal, cont;
	bool bPlay;                       // Continue to play game?
	Menu* menu;                      // Scene to render
	Level1* level1;
	Level2* level2;
	Level3* level3;
	Level4* level4;
	Level5* level5;
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time

};


#endif // _GAME_INCLUDE