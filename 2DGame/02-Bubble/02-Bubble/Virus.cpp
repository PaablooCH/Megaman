#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Virus.h"

enum Situation1
{
    MOVING, STANDING
} states;

enum EnemyAnims
{
    MOVE
};

Virus::~Virus()
{
}

void Virus::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id)
{
    states = STANDING;
    isAlive = true;
    spritesheet.loadFromFile("images/Virus.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(MOVE, 1);
    sprite->addKeyframe(MOVE, glm::vec2(1.f, 0.f));


    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    posIni = posInicial;
    ID = id;
    sprite->setPosition(posIni);
}

void Virus::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posEnemy;
    switch (states) {
    case MOVING: {
        posEnemy.y += 2;
        if (map->collisionMoveDown(posEnemy, glm::ivec2(20, 20), &posEnemy.y))
        {
            isAlive = false;
            map->clearPosition(ID);
        }
    } break;

    case STANDING: {
        cont += deltaTime;
        if (map->checkPlayerDown(posEnemy, glm::ivec2(20, 20))) states = MOVING;
    } break;
    }

    map->updatePositionTile(posEnemy, glm::ivec2(40, 40), posAnt, ID);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}