#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bonus.h"

enum bonusType
{
    BOTES, HELMET, BATTERY, BOOK, ARMOR, SHOOT
} states;

enum EnemyAnims
{
    STAND
};


Bonus::~Bonus()
{
    if (sprite != NULL) {
        delete sprite;
        sprite = nullptr;
    }
}

void Bonus::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id, string type)
{
    if (type == "Bambas")states = BOTES;
    else if (type == "Casco")states = HELMET;
    else if (type == "Bateria")states = BATTERY;
    else if (type == "Libro")states = BOOK;
    else if (type == "Escudo")states = ARMOR;
    else states = SHOOT;
    got = false;
    spritesheet.loadFromFile("images/Bonus" + type + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(STAND, 1);
    sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    ID = id;
    tipus = type;
    sprite->setPosition(posInicial);
}

void Bonus::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posIni;
    if (map->checkIfPlayer(posIni, glm::ivec2(1, 16))) {
        map->clearPosition(ID);
        got = true;
    }
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
    if (!got) map->updatePositionTile(posIni, glm::ivec2(32, 32), posAnt, ID);
}

void Bonus::render()
{
    sprite->render();
}

void Bonus::setTileMap(TileMap* tileMap)
{
    map = tileMap;
}

void Bonus::setPosition(const glm::vec2& pos)
{
    posIni = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posIni.x), float(tileMapDispl.y + posIni.y)));
}

bool Bonus::checkState()
{
    return got;
}

string Bonus::checkType()
{
    return tipus;
}