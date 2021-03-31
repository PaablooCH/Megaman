#pragma once
#include "Enemy.h"
class FakeRoof : public Enemy
{
public:
    FakeRoof(int id);
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial);
    void update(int deltaTime);
private:
    int id;
};