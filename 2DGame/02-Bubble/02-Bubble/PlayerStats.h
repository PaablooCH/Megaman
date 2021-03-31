#ifndef _PLAYERSTATS_INCLUDE
#define _PLAYERSTATS_INCLUDE

#include "Sprite.h"

class PlayerStats
{
public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int health, int exp, bool* gRescued);
	void render();

	void setPosition(const glm::vec2& pos);
	void addKey();
	void removeKey();
	bool checkKeys();
	void addExp();

private:
	Texture spritesheet;
	Sprite* spriteHealth;
	Sprite* spriteExp;
	Sprite* spritePowerUp;
	Sprite* spriteGirlsRescued;
	glm::ivec2 tileMapDispl, posHealth, posExp, posGirl;
	int keys;
	int health, exp;
	bool* gRescued;
};

#endif // _PLAYERSTATS_INCLUDE