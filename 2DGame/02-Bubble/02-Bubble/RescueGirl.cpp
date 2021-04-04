#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "RescueGirl.h"

enum GirlState
{
    WAITING, RESCUED
} states;

enum EnemyAnims
{
    STAND
};


RescueGirl::~RescueGirl()
{
    if (sprite != NULL) {
        delete sprite;
        sprite = nullptr;
    }
    if (spriteDoor != NULL) {
        delete spriteDoor;
        spriteDoor = nullptr;
    }
}

void RescueGirl::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
    states = WAITING;
    rescued = false;
    finish = false;
    spritesheet.loadFromFile("images/Girl.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(20, 32), glm::vec2(27.f / 202.f, 46.f / 96.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(STAND, 7);
    sprite->addKeyframe(STAND, glm::vec2(174.f / 202.f, 0.f / 96.f));
    sprite->addKeyframe(STAND, glm::vec2(146.f / 202.f, 0.f / 96.f));
    sprite->addKeyframe(STAND, glm::vec2(117.f / 202.f, 1.f / 96.f));
    sprite->addKeyframe(STAND, glm::vec2(87.f / 202.f, 0.f / 96.f));
    sprite->addKeyframe(STAND, glm::vec2(57.f / 202.f, 49.f / 96.f));
    sprite->addKeyframe(STAND, glm::vec2(29.f / 202.f, 48.f / 96.f));
    sprite->addKeyframe(STAND, glm::vec2(0.f / 202.f, 48.f / 96.f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    sprite->setPosition(posInicial);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    spriteDoor = Sprite::createSprite(glm::ivec2(20, 32), glm::vec2(16.f / 202.f, 32.f / 96.f), &spritesheet, &shaderProgram);
    spriteDoor->setNumberAnimations(1);

    spriteDoor->setAnimationSpeed(STAND, 7);
    spriteDoor->addKeyframe(STAND, glm::vec2(151.f / 202.f, 50.f / 96.f));

    spriteDoor->changeAnimation(0);
    tileMapDispl = tileMapPos;
    spriteDoor->setPosition(posInicial);
}

void RescueGirl::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posGirl;
    switch (states) {
    case WAITING: {
        if (map->checkIfPlayer(posGirl, glm::ivec2(20, 32))) {
            if (playerstat->checkKeys()) {
                rescued = true;
                states = RESCUED;
                cont = 0;
                map->openDoor(posGirl);
            }
        }
    } break;
    case RESCUED: {
        cont += deltaTime;
        if (cont >= 5000)
            finish = true;
    } break;
    }

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGirl.x), float(tileMapDispl.y + posGirl.y)));
}

void RescueGirl::render()
{
    if (rescued)
        sprite->render();
    else
        spriteDoor->render();
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
    return finish;
}