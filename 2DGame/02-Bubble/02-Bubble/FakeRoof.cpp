#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "FakeRoof.h"

enum Status
{
    MOVING_DOWN, MOVING_UP, STANDING
} states;

enum EnemyAnims
{
    MOVE
};

FakeRoof::FakeRoof(int id)
{
    this->id = id;
}

void FakeRoof::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
    states = STANDING;
    isAlive = true;
    spritesheet.loadFromFile("images/Stone" + to_string(id) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(MOVE, 1);
    sprite->addKeyframe(MOVE, glm::vec2(1.f / 4.f, 0.f));


    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    posIni = posInicial;
    sprite->setPosition(posIni);
}

void FakeRoof::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posEnemy;
    switch (states) {
        case STANDING: {
            if (map->checkPlayerDown(posEnemy, glm::ivec2(32, 32))) states = MOVING_DOWN;
        } break;
        case MOVING_DOWN: {
            for (int i = 0; i < 10; i++) {
                posEnemy.y += 1;
                if (map->collisionMoveDown(posEnemy, glm::ivec2(20, 20), &posEnemy.y))
                {
                    states = MOVING_UP;
                    cont = 0;
                    break;
                }
            }
        } break;
        case MOVING_UP: {
            cont += deltaTime;
            if (cont >= 500) {
                posEnemy.y -= 1;
                if (posEnemy.y == posIni.y)
                    states = STANDING;
            }
        } break;
    }

    map->updatePositionFakeRoof(posEnemy, glm::ivec2(40, 40), posAnt, 8);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}