#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "FakeRoof.h"
#include "Game.h"


enum EnemyAnims
{
    MOVE
};

FakeRoof::~FakeRoof()
{
}

FakeRoof::FakeRoof(int id)
{
    this->level = id;
}

void FakeRoof::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id)
{
    state = "STANDING";
    isAlive = true;
    spritesheet.loadFromFile("images/Stone" + to_string(level) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(MOVE, 1);
    sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.f));


    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    posIni = posInicial;
    ID = id;
    sprite->setPosition(posIni);
}

void FakeRoof::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posEnemy;
    if(state == "STANDING") {
        if (map->checkPlayerDown(posEnemy, glm::ivec2(32, 32))) {
            state = "MOVING_DOWN";
            Game::instance().playSound("music/StoneEffect.wav");
        }
    }
    if(state == "MOVING_DOWN") {
        for (int i = 0; i < 10; i++) {
            posEnemy.y += 1;
            if (map->collisionMoveDown(posEnemy, glm::ivec2(20, 20), &posEnemy.y))
            {
                state = "MOVING_UP";
                cont = 0;
                break;
            }
        }
    }
    if(state == "MOVING_UP") {
        cont += deltaTime;
        if (cont >= 500) {
            posEnemy.y -= 1;
            if (posEnemy.y == posIni.y)
                state = "STANDING";
        }
    }

    map->updatePositionFakeRoof(posEnemy, glm::ivec2(40, 40), posAnt, ID);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}