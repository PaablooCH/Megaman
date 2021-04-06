#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Level1.h"
#include "Player.h"
#include "Level2.h"
#include "Menu.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"

#include <irrKlang.h>
#include <ik_ISoundEngine.h>

#define SCREEN_WIDTH 496
#define SCREEN_HEIGHT 496




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

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	void loopMusic(char* fileName);
	void stopMusic();
	void playSound(char* fileName);

private:
	Player* player;
	int lvl, selectPortal, cont;
	bool bPlay;                       
	Menu* menu;                      
	Level1* level1;
	Level2* level2;
	Level3* level3;
	Level4* level4;
	Level5* level5;
	bool keys[256], specialKeys[256];  
									  
	irrklang::ISoundEngine* engine;  
	irrklang::ISound* music;
};


#endif // _GAME_INCLUDE