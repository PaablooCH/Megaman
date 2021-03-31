#ifndef _CHIP_INCLUDE
#define _CHIP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "PlayerStats.h"
#include "Extended_GLUT_KEYS.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Chip
{

public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial);
    void update(int deltaTime);
    void render();

    void setTileMap(TileMap* tileMap);
    void setPosition(const glm::vec2& pos);
    bool checkState();

protected:
    glm::ivec2 tileMapDispl, posIni, posAnt;
    int jumpAngle, startY;
    Texture spritesheet;
    Sprite* sprite;
    TileMap* map;
    bool got;
};

#endif // _CHIP_INCLUDE
