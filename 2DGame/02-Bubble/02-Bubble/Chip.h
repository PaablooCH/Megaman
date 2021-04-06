#ifndef _CHIP_INCLUDE
#define _CHIP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "PlayerStats.h"
#include "Extended_GLUT_KEYS.h"




class Chip
{

public:

    ~Chip();

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

#endif // _CHIP_INCLUDE
