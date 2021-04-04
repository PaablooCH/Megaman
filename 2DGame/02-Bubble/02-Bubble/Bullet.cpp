#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"
#include "TileMap.h"

Bullet::~Bullet()
{
    delete sprite;
    sprite = nullptr; //acabar
    deleteAll();
}

void Bullet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int id, int code)
{
    spritesheet.loadFromFile("images/Bullet" + to_string(code) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    tileMapDispl = tileMapPos;
    texProgram = shaderProgram;
    ID = id;
}

void Bullet::update(int deltaTime)
{
    sprite->update(deltaTime);
    posAnt = posBullet;
    int i = 0;
    int maxIt = bullets.size() - 1;
    while (i <= maxIt) {
        int j = 0;
        exit = false;
        while ((j < 1) && (!exit)) {
            if (isRight)bullets[i].x += 2;
            if (!isRight) bullets[i].x -= 2;
            if (map->collisionMoveLeft(bullets[i], glm::ivec2(16, 16)) || map->collisionMoveRight(bullets[i], glm::ivec2(16, 16))){
                bullets.erase(bullets.begin() + i);
                sprites[i]->free();
                if (sprites[i] != NULL) {
                    sprites[i]->free();
                    delete sprites[i];
                }
                sprites.erase(sprites.begin() + i);
                if (isRight)map->clearPosition(ID + i + 1);
                if (!isRight)map->clearPosition(ID + i + 6);
                i--;
                maxIt--;
                exit = true;
            }
            else {
                int id = ID;
                if(isRight)id += (i + 1);
                if (!isRight)id += (6 + i );
                map->updatePositionTile(bullets[i], glm::ivec2(16, 16), posAnt, id);
                sprites[i]->setPosition(
                    glm::vec2(float(tileMapDispl.x + bullets[i].x),
                        float(tileMapDispl.y + bullets[i].y)));
            }
            j++;
        }
        i++;
    }
}

void Bullet::render()
{
    for (unsigned int i = 0; i < sprites.size(); i++) {
        sprites[i]->render();
    }
}

void Bullet::deleteAll() {
    for (int i = bullets.size() - 1; i >= 0; i--) {
        bullets.erase(bullets.begin() + i);
        sprites[i]->free();
        if (sprites[i] != NULL) {
            delete sprites[i];
        }
        sprites.erase(sprites.begin() + i);
        if (isRight)map->clearPosition(ID + i);
        if (!isRight)map->clearPosition((ID + 5 + i));
    }
}

void Bullet::setTileMap(TileMap* tileMap)
{
    map = tileMap;
}


void Bullet::setPosition(const glm::vec2& pos)
{
    posBullet = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x), float(tileMapDispl.y + posBullet.y)));
}

void Bullet::addBullet(const glm::vec2& pos, bool Right)
{
    isRight = Right;
    bullets.push_back(glm::vec2(pos.x + 1, pos.y));
    initSprite();
    sprites[sprites.size() - 1]->setPosition(
        glm::vec2(float(tileMapDispl.x + bullets[bullets.size() - 1].x),
            float(tileMapDispl.y + bullets[bullets.size() - 1].y)));
}

void Bullet::initSprite() {
    sprites.push_back(Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f),
        &spritesheet, &texProgram));
    sprites[sprites.size() - 1]->setNumberAnimations(1);

    sprites[sprites.size() - 1]->setAnimationSpeed(0, 8);
    sprites[sprites.size() - 1]->addKeyframe(0, glm::vec2(0.f, 0.f));

    sprites[sprites.size() - 1]->changeAnimation(0);
}