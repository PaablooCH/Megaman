#pragma once
#include "Enemy.h"
class FakeRoof : public Enemy
{
public:

    ~FakeRoof();

    FakeRoof(int id);
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id);
    void update(int deltaTime);
private:
    int level;
    string state;
};