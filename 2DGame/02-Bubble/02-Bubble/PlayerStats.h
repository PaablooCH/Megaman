#ifndef _PLAYERSTATS_INCLUDE
#define _PLAYERSTATS_INCLUDE

#include "Sprite.h"

class PlayerStats
{
public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int health, int exp, bool* gRescued, int nkeys, bool* powerUp, int bullets);
	void render();

	void setPosition(const glm::vec2& pos);
	bool checkKeys();

private:
	Texture spritesheet;
	Sprite* spriteHealth;
	Sprite* spriteExp;
	Sprite* spriteKey;
	Sprite* spriteNumberKey;
	Sprite* spriteX;
	Sprite* spritePowerUp;
	Sprite* spriteGirlsRescued;
	glm::ivec2 tileMapDispl, posHealth, posExp, posGirl, posKey, posNumberKey, posX, posPowerUp;
	int nkeys, bullets;
	int health, exp;
	bool* gRescued;
	bool* powerUp;
};

#endif // _PLAYERSTATS_INCLUDE