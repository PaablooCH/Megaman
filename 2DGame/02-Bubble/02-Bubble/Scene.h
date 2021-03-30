#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "LinealEnemy.h"
#include "Camera.h"
#include "Virus.h"
#include "Teleport.h"
#include "Fire.h"
#include "PlayerStats.h"
#include "Key.h"
#include "RescueGirl.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 640

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void updateCamera();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	LinealEnemy *enemy1;
	Fire* fire1;
	Virus* virus1;
	Teleport* teleport1;
	PlayerStats *playerStats;
	RescueGirl *girl1;
	Key *key1;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	glm::vec2 posCamera;
};


#endif // _SCENE_INCLUDE

