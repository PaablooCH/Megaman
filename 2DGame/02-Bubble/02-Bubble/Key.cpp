#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Key.h"

enum keyState
{
    NORMAL
} states;

enum EnemyAnims
{
    STAND
};


void Key::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
    states = NORMAL;
    spritesheet.loadFromFile("images/Key.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(STAND, 1);
    sprite->addKeyframe(STAND, glm::vec2(1.f, 0.f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    sprite->setPosition(posInicial);
}

void Key::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posIni;
    switch (states) {
    case NORMAL: {
            if (map->checkIfPlayer(posIni, glm::ivec2(32, 32)))
            {
                //playerStats->teleport();
            }
        } break;
    }
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
}

void Key::render()
{
    sprite->render();
}

void Key::setTileMap(TileMap* tileMap)
{
    map = tileMap;
}

void Key::setPlayerStats(PlayerStats* ps) 
{
    playerstat = ps;
}

void Key::setPosition(const glm::vec2& pos)
{
    posIni = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
}