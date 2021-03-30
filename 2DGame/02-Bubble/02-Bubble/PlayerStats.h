#ifndef _PLAYERSTATS_INCLUDE
#define _PLAYERSTATS_INCLUDE

#include "Sprite.h"

class PlayerStats
{
public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int health, int exp);
	void render(int health, int exp);

	void setPosition(const glm::vec2& pos);
	void addKey();
	void removeKey();
	bool checkKeys();

private:
	Texture spritesheet;
	Sprite* spriteHealth;
	Sprite* spriteExp;
	glm::ivec2 tileMapDispl, posHealth, posExp;
	int keys;
};

#endif // _PLAYERSTATS_INCLUDE