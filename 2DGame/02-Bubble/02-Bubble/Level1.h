#pragma once
#include "Scene.h"
#include "Virus.h"
#include "Fire.h"
#include "LinealEnemy.h"
#include "Cascade.h"
#include "Chip.h"

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
	void deleteEnemy();

private:
	LinealEnemy* enemy1;
	Fire* fire1;
	Virus* virus1;
	Cascade* cascade1;
	Chip* chip1;
};

