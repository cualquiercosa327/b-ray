#pragma once
#include "hitable.h"

namespace bray
{

class sphere : public hitable
{
public:
	sphere(glm::vec3 cen, float r):center(cen), radius(r) {}
	bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) override;
	glm::vec3 center;
	float radius;
};

}
