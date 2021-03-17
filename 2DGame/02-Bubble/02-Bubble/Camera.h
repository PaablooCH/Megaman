#pragma once

#include <glm/glm.hpp>


enum class ECamType
{ SIMPLE, INTERPOLATED, DEAD_ZONE};

class Camera
{
public:
	Camera(int W, int H, ECamType type = ECamType::SIMPLE) : type(type), W(W), H(H)
	{
		centerPosition = glm::vec2(W/2, H/2);
	}

	void update(glm::vec2 position);
	inline glm::vec2 getTransform() const { return -centerPosition + glm::vec2(W / 2, H/2); }


private:

	bool outOfBounds(glm::vec2 centerPoint) const;
	glm::vec2 linearInterpolate(glm::vec2 &p1, glm::vec2 &p2, float alpha) const;

	int W, H, xmin, xmax, ymin, ymax;
	ECamType type;
	glm::vec2 centerPosition;
};

