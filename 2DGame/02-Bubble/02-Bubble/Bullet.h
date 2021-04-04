#ifndef _BULLET_INCLUDE
#define _BULLET_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Extended_GLUT_KEYS.h"
#include "ShaderProgram.h"



class Bullet
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int id, int code);
	void initSprite();
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void addBullet(const glm::vec2& pos, bool Right);
	void deleteAll();


private:
	glm::ivec2 tileMapDispl, posBullet, posAnt;
	vector<glm::ivec2> bullets;
	Texture spritesheet;
	Sprite* sprite;
	vector<Sprite*> sprites;
	TileMap* map;
	ShaderProgram texProgram;

	bool exit;
	bool isRight;
	int ID;
};

#endif