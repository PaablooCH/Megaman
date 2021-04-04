#pragma once
#include "Enemy.h"
class Fire : public Enemy
{
public:

    ~Fire();

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id);
    void update(int deltaTime);
};