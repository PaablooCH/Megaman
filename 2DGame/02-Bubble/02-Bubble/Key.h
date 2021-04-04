#ifndef _KEY_INCLUDE
#define _KEY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Extended_GLUT_KEYS.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Key
{

public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id);
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
    int ID;
};

#endif // _KEY_INCLUDE