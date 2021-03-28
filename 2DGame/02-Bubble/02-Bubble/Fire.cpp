#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Fire.h"

enum Situation
{
    MOVING
} states;

enum EnemyAnims
{
    MOVE
};


void Fire::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
    states = MOVING;
    spritesheet.loadFromFile("images/FireTrap.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(1.f / 4.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(MOVE, 6);
    sprite->addKeyframe(MOVE, glm::vec2(1.f / 4.f, 0.f));
    sprite->addKeyframe(MOVE, glm::vec2(2.f / 4.f, 0.f));
    sprite->addKeyframe(MOVE, glm::vec2(3.f / 4.f, 0.f));
    sprite->addKeyframe(MOVE, glm::vec2(4.f / 4.f, 0.f));


    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    posIni = posInicial;
    sprite->setPosition(posIni);
}

void Fire::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posEnemy;
    switch (states) {
    case MOVING: {
        posEnemy.x -= 1;
        if (map->collisionMoveLeft(posEnemy, glm::ivec2(20, 20)))
        {
            posEnemy = posIni;
        }
    } break;
    }

    map->updatePositionTile(posEnemy, glm::ivec2(32, 32), posAnt, 6);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}