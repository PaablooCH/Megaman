#include "Camera.h"

void Camera::update(glm::vec2 position)
{
	switch (type)
	{
		case ECamType::SIMPLE:
			if (!outOfBounds(position))
				centerPosition = position;
			break;
		case ECamType::INTERPOLATED:
			if (!outOfBounds(position))
				centerPosition = linearInterpolate(centerPosition, position, 0.05f);
			break;
		default:
			centerPosition = position;
	}
}

//Camera bounds checking (deactivated)...
bool Camera::outOfBounds(glm::vec2 centerPoint) const
{
	return false;
}

glm::vec2 Camera::linearInterpolate(glm::vec2& p1, glm::vec2& p2, float alpha) const
{
	return p1*(1-alpha) + p2*alpha;
}
