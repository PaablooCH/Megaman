#pragma once
#include "Enemy.h"
class LinealEnemy: public Enemy
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
};

