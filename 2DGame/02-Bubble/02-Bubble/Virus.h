#pragma once
#include "Enemy.h"
class Virus : public Enemy
{
public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial);
    void update(int deltaTime);
    bool checkAlive();
private:
    bool isDead;
};