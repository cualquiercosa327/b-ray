#include "sphere.h"
#include <glm/glm.hpp>
#include "ray.h"

using namespace glm;
using namespace bray;

bool sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec)
{
	vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = 2.0f * dot(oc, r.Direction());
	float c = dot(oc, oc) -(radius * radius);
	float discriminant = b * b - 4 * a*c;

	if (discriminant > 0.0f)
	{
		float t = (-b - sqrt(discriminant)) / (2.0f * a);
		if (t < t_max && t > t_min)
		{
			rec.t = t;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		
		t = (-b + sqrt(discriminant)) / (2.0f * a);
		if (t < t_max && t > t_min)
		{
			rec.t = t;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}

	return false;
}
