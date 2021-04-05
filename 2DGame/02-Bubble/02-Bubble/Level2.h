#pragma once
#include "Scene.h"
#include "Virus.h"
#include "Fire.h"
#include "LinealEnemy.h"
#include "FakeRoof.h"
#include "Chip.h"
#include "ShootEnemy.h"
#include "Bonus.h"
#include "FakeRoof.h"

class Level2 : public Scene
{
public:
	Level2();
	~Level2();

	void init(Player* player, int selectPortal);
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

private:
	LinealEnemy *enemy1, *enemy2, *enemy3;
	Fire *fire1, *fire2, *fire3, *fire4, *fire5, *fire6;
	Teleport* teleport2;
	FakeRoof* fakeRoof1;
	Virus* virus1, * virus2;
	ShootEnemy* senemy2;
	Chip* chip1, * chip2;
	Bonus* bonus1;
};

