#pragma once
#include "hitable.h"

namespace bray
{

class sphere : public hitable
{
public:
	sphere(glm::vec3 cen, float r, material* mat):center(cen), radius(r), mat_ptr(mat) {}
	bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;
	glm::vec3 center;
	float radius;
	material* mat_ptr = nullptr;
};

}
