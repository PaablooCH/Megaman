#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Teleport.h"

enum teleState
{
    TELEPORT
} states;

enum EnemyAnims
{
    STAND
};


void Teleport::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int lvl)
{
    states = TELEPORT;
    spritesheet.loadFromFile("images/Teleport.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(STAND, 1);
    sprite->addKeyframe(STAND, glm::vec2(1.f, 0.f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    this->lvl = lvl;
    sprite->setPosition(posInicial);
}

void Teleport::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posPortal;
    switch (states) {
    case TELEPORT: {
        if (map->checkIfPlayer(posPortal, glm::ivec2(32, 32)))
            player->teleport(lvl);
    } break;
    }

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPortal.x), float(tileMapDispl.y + posPortal.y)));
}

void Teleport::render()
{
    sprite->render();
}

void Teleport::setTileMap(TileMap* tileMap)
{
    map = tileMap;
}

void Teleport::setPlayer(Player* p)
{
    player = p;
}

void Teleport::setPosition(const glm::vec2& pos)
{
    posPortal = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPortal.x), float(tileMapDispl.y + posPortal.y)));
}