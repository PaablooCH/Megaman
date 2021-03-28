#ifndef _TELEPORT_INCLUDE
#define _TELEPORT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "Extended_GLUT_KEYS.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Teleport
{

public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, const glm::ivec2& posTeleport);
    void update(int deltaTime);
    void render();

    void setTileMap(TileMap* tileMap);
    void Teleport::setPlayer(Player* p);
    void setPosition(const glm::vec2& pos);

protected:
    glm::ivec2 tileMapDispl, posPortal, posTel, posAnt;
    int jumpAngle, startY;
    Texture spritesheet;
    Sprite* sprite;
    TileMap* map;
    Player* player;
};

#endif // _TELEPORT_INCLUDE