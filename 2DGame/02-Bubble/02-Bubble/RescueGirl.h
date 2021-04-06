#ifndef _RESCUEGIRL_INCLUDE
#define _RESCUEGIRL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "PlayerStats.h"
#include "Extended_GLUT_KEYS.h"




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
    bool rescued, finish; 
};

#endif // _RESCUEGIRL_INCLUDE
