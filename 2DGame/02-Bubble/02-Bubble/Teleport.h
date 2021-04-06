#ifndef _TELEPORT_INCLUDE
#define _TELEPORT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "Extended_GLUT_KEYS.h"


class Teleport
{

public:

    ~Teleport();

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int lvl);
    void update(int deltaTime);
    void render();

    void setTileMap(TileMap* tileMap);
    void setPlayer(Player* p);
    void setPosition(const glm::vec2& pos);

protected:
    glm::ivec2 tileMapDispl, posPortal, posAnt;
    int jumpAngle, startY;
    Texture spritesheet;
    Sprite* sprite;
    TileMap* map;
    Player* player;
    int lvl;
};

#endif // _TELEPORT_INCLUDE