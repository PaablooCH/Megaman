#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Cascade.h"

enum Status
{
    MOVING
} states;

enum EnemyAnims
{
    MOVE
};


void Cascade::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
    states = MOVING;
    isAlive = true;
    spritesheet.loadFromFile("images/Cascade.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(MOVE, 1);
    sprite->addKeyframe(MOVE, glm::vec2(1.f / 4.f, 0.f));


    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    posIni = posInicial;
    sprite->setPosition(posIni);
}

void Cascade::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posEnemy;
    cont += deltaTime;
    if (cont >= 300) isAlive = true;
    switch (states) {
        case MOVING: {
            posEnemy.y += 1;
            if (map->cascadeMoveDown(posEnemy, glm::ivec2(20, 20), &posEnemy.y))
            {
                posEnemy = posIni;
                isAlive = false;
                cont = 0;
                map->clearPosition(8);
            }
        } break;
    }

    map->updatePositionCascade(posEnemy, glm::ivec2(32, 32), posAnt, 8);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}