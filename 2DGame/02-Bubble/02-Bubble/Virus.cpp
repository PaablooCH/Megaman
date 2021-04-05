#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Virus.h"


enum EnemyAnims
{
    MOVE
};

Virus::~Virus()
{
}

void Virus::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id)
{
    stand = true;
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
    switch (stand) {
        case false: {
            posEnemy.y += 2;
            if (map->collisionMoveDown(posEnemy, glm::ivec2(16, 16), &posEnemy.y))
            {
                isAlive = false;
                map->clearPosition(ID);
            }
        } break;

        case true : {
            cont += deltaTime;
            if (map->checkPlayerDown(posEnemy, glm::ivec2(20, 20))) stand = false;
        } break;
    }

    map->updatePositionTile(posEnemy, glm::ivec2(40, 40), posAnt, ID);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}