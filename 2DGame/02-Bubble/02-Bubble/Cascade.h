#pragma once
#include "Enemy.h"
class Cascade : public Enemy
{
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial);
    void update(int deltaTime);
};