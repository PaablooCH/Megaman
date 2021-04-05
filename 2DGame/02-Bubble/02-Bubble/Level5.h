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

	void init(Player* player, int selectPortal);
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
	void deleteSEnemy3();
	void deleteChip();
	void deleteChip5();
	void deleteChip2();
	void deleteChip3();
	void deleteChip4();
	void deleteBonus();
	void deleteBonus2();


private:
	LinealEnemy* enemy1, * enemy2, * enemy3, * enemy4;
	Fire* fire1, * fire2, * fire3, * fire4, * fire5;
	RescueGirl* girl2;
	Key* key2;
	Teleport* teleport2;
	Virus* virus1, * virus2;
	FakeRoof* fakeRoof1, * fakeRoof2;
	ShootEnemy* senemy2, * senemy3;
	Chip* chip1, * chip2, * chip3, * chip4, * chip5;
	Bonus* bonus1, * bonus2;
};

