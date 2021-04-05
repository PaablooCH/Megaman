#pragma once
#include "Enemy.h"

class LinealEnemy : public Enemy
{
public:
    ~LinealEnemy();

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id);
    void update(int deltaTime);
private:
    bool moveRight;
};