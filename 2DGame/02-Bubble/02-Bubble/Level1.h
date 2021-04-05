#pragma once
#include "Scene.h"
#include "Virus.h"
#include "Fire.h"
#include "LinealEnemy.h"
#include "Chip.h"
#include "ShootEnemy.h"
#include "Bonus.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 640

class Level1 : public Scene
{

public:
	Level1();
	~Level1();

	void init(Player* player);
	void update(int deltaTime);
	void render();
private:
	void deleteVirus();
	void deleteVirus2();
	void deleteEnemy();
	void deleteEnemy2();
	void deleteEnemy3();
	void deleteSEnemy();
	void deleteChip();
	void deleteChip2();
	void deleteBonus();
	void deleteBonus2();
	

private:
	LinealEnemy* enemy1, *enemy2, *enemy3;
	Fire* fire1;
	Fire* fire2;
	Virus* virus1, *virus2;
	ShootEnemy* senemy2;
	Chip* chip1, *chip2;
	Bonus* bonus1, *bonus2;
};

