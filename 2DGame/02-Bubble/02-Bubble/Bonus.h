#ifndef _BONUS_INCLUDE
#define _BONUS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Extended_GLUT_KEYS.h"



class Bonus
{

public:

    ~Bonus();

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::ivec2& posInicial, int id, string type);
    void update(int deltaTime);
    void render();

    void setTileMap(TileMap* tileMap);
    void setPosition(const glm::vec2& pos);
    bool checkState();
    string checkType();

protected:
    glm::ivec2 tileMapDispl, posIni, posAnt;
    int jumpAngle, startY;
    Texture spritesheet;
    Sprite* sprite;
    TileMap* map;
    bool got;
    int ID;
    string tipus;
};

#endif // _BONUS_INCLUDE