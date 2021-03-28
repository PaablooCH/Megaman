#ifndef _PLAYERSTATS_INCLUDE
#define _PLAYERSTATS_INCLUDE

#include "Sprite.h"

class PlayerStats
{
public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int health, int exp);
	void render();

private:
	Texture spritesheet;
	Sprite* spriteHealth;
	Sprite* spriteExp;
	glm::ivec2 tileMapDispl, posHealth, posExp;
};

#endif // _PLAYERSTATS_INCLUDE