#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Chip.h"

enum chipState
{
    NORMAL
} states;

enum EnemyAnims
{
    STAND
};


void Chip::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial)
{
    states = NORMAL;
    got = false;
    spritesheet.loadFromFile("images/ExperienceChip.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(STAND, 1);
    sprite->addKeyframe(STAND, glm::vec2(1.f, 0.f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    sprite->setPosition(posInicial);
}

void Chip::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posIni;
    switch (states) {
        case NORMAL: {
            if (map->checkIfPlayer(posIni, glm::ivec2(32, 32))) {
                got = true;
                map->clearPosition(11);
            }
                
        } break;
    }
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
    if(!got) map->updatePositionTile(posIni, glm::ivec2(32, 32), posAnt, 11);
}

void Chip::render()
{
    sprite->render();
}

void Chip::setTileMap(TileMap* tileMap)
{
    map = tileMap;
}

void Chip::setPosition(const glm::vec2& pos)
{
    posIni = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
}

bool Chip::checkState()
{
    return got;
}