#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "RescueGirl.h"

enum GirlState
{
    RESCUED
} states;

enum EnemyAnims
{
    STAND
};


void RescueGirl::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
    states = RESCUED;
    rescued = false;
    spritesheet.loadFromFile("images/Girl.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(20, 32), glm::vec2(1.f / 7.f, 1.f / 2.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(STAND, 7);
    sprite->addKeyframe(STAND, glm::vec2(7.f / 7.f, 0.f / 2.f));
    sprite->addKeyframe(STAND, glm::vec2(6.f / 7.f, 0.f / 2.f));
    sprite->addKeyframe(STAND, glm::vec2(5.f / 7.f, 0.f / 2.f));
    sprite->addKeyframe(STAND, glm::vec2(4.f / 7.f, 0.f / 2.f));
    sprite->addKeyframe(STAND, glm::vec2(3.f / 7.f, 1.f / 2.f));
    sprite->addKeyframe(STAND, glm::vec2(2.f / 7.f, 1.f / 2.f));
    sprite->addKeyframe(STAND, glm::vec2(1.f / 7.f, 1.f / 2.f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    sprite->setPosition(posInicial);
}

void RescueGirl::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posGirl;
    switch (states) {
    case RESCUED: {
        if (map->checkIfPlayer(posGirl, glm::ivec2(20, 32))) {
            if (playerstat->checkKeys()) {
                rescued = true;
                map->openDoor(posGirl);
            }
        }
    } break;
    }

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGirl.x), float(tileMapDispl.y + posGirl.y)));
}

void RescueGirl::render()
{
    sprite->render();
}

void RescueGirl::setTileMap(TileMap* tileMap)
{
    map = tileMap;
}

void RescueGirl::setPlayerStats(PlayerStats* ps)
{
    playerstat = ps;
}

void RescueGirl::setPosition(const glm::vec2& pos)
{
    posGirl = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGirl.x), float(tileMapDispl.y + posGirl.y)));
}

bool RescueGirl::checkState()
{
    return rescued;
}