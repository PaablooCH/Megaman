#pragma once
#include "Scene.h"
class Level2 : public Scene
{
public:
	Level2();
	~Level2();

	void init(Player* player);
	void update(int deltaTime);
	void render();

private:

};

