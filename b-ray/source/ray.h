#pragma once

#include <glm/vec3.hpp>

namespace bray
{

class Ray
{
public:
	Ray() {}
	Ray(const glm::vec3& a, const glm::vec3& b) { A = a; B = b; }
	const glm::vec3& Origin() const { return A; }
	const glm::vec3& Direction() const { return B; }
	glm::vec3 PointAtParameter(float t)	const { return A + t * B; }
private:
	glm::vec3 A;
	glm::vec3 B;
};

}
