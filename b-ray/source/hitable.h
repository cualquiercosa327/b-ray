#pragma once
#include <glm/detail/type_vec3.hpp>

namespace bray
{
class Ray;

struct hit_record
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
};

class hitable
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) = 0;
};

}
