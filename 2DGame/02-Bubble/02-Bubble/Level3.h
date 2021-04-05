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

class Level3 : public Scene
{

public:
	Level3();
	~Level3();

	void init(Player* player);
	void update(int deltaTime);
	void render();
private:
	void deleteVirus();
	void deleteVirus2();
	void deleteEnemy();
	void deleteEnemy4();
	void deleteEnemy2();
	void deleteEnemy3();
	void deleteSEnemy();
	void deleteChip();
	void deleteChip2();
	void deleteChip3();
	void deleteChip4();
	void deleteBonus();
	void deleteBonus2();


private:
	LinealEnemy* enemy1, * enemy2, * enemy3, * enemy4;
	Teleport* teleport2;
	Fire* fire1, * fire2, * fire3, * fire4, * fire5;
	Virus* virus1, * virus2;
	FakeRoof* fakeRoof1, *fakeRoof2;
	ShootEnemy* senemy2;
	Chip* chip1, * chip2, * chip3, * chip4;
	Bonus* bonus1, * bonus2;
};