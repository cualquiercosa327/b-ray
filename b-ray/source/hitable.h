#pragma once
#include <glm/detail/type_vec3.hpp>

namespace bray
{
class Ray;
class material;

struct hit_record
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
	material* mat_ptr = nullptr;
};

class hitable
{
public:
	virtual ~hitable() = default;
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

}
