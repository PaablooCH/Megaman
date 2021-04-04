#ifndef _RESCUEGIRL_INCLUDE
#define _RESCUEGIRL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "PlayerStats.h"
#include "Extended_GLUT_KEYS.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class RescueGirl
{

public:

    ~RescueGirl();

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial);
    void update(int deltaTime);
    void render();

    void setTileMap(TileMap* tileMap);
    void setPlayerStats(PlayerStats* ps);
    void setPosition(const glm::vec2& pos);
    bool checkState();

protected:
    glm::ivec2 tileMapDispl, posGirl, posAnt;
    int jumpAngle, startY, cont;
    Texture spritesheet;
    Sprite* sprite;
    Sprite* spriteDoor;
    TileMap* map;
    PlayerStats* playerstat;
    bool rescued, finish; //cambiar nombre a show
};

#endif // _RESCUEGIRL_INCLUDE
