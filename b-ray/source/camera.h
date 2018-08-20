#pragma once
#include "Ray.h"

namespace bray
{

	class camera
	{
	public:
		camera();

		Ray get_ray(float u, float v) const
		{ return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

		glm::vec3 origin;
		glm::vec3 lower_left_corner;
		glm::vec3 horizontal;
		glm::vec3 vertical;
	};

}
