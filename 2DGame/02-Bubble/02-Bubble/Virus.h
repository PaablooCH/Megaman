#pragma once
#include "Enemy.h"
class Virus : public Enemy
{
public:

    ~Virus();

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id);
    void update(int deltaTime);
};