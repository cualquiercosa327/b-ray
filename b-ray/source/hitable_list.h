#pragma once
#include "hitable.h"

namespace bray
{

class hitable_list : public hitable
{
public:
	hitable_list(hitable** l, int n) { list = l; list_size = n; }
	bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;
	hitable** list;
	int list_size;
};

}
