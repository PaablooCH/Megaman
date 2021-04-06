#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "Extended_GLUT_KEYS.h"




class Enemy
{

public:

    ~Enemy();

    virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id) = 0;
    virtual void update(int deltaTime) = 0;
    void render();

    void setTileMap(TileMap* tileMap);
    void setPlayer(Player* p);
    void setPosition(const glm::vec2& pos);
    bool checkAlive();

protected:
    bool bJumping;
    glm::ivec2 tileMapDispl, posEnemy, posAnt, posIni;
    int jumpAngle, startY;
    Texture spritesheet;
    Sprite* sprite;
    TileMap* map;
    Player* player;
    int cont, ID;
    bool isRight;
    bool isAlive;
};

#endif // _ENEMY_INCLUDE