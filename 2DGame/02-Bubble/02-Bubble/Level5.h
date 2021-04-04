#pragma once
#include "Scene.h"
#include "Virus.h"
#include "Fire.h"
#include "LinealEnemy.h"
#include "FakeRoof.h"
#include "Chip.h"
#include "ShootEnemy.h"
#include "Bonus.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 640

class Level5 : public Scene
{

public:
	Level5();
	~Level5();

	void init(Player* player);
	void update(int deltaTime);
	void render();
private:
	void deleteVirus();
	void deleteEnemy();
	void deleteSEnemy();
	void deleteChip();
	void deleteBonus();


private:
	LinealEnemy* enemy1;
	Fire* fire1;
	Fire* fire2;
	Virus* virus1;
	FakeRoof* fakeRoof1;
	ShootEnemy* senemy2;
	Chip* chip1;
	Bonus* bonus1;
};

