#include "camera.h"

using namespace bray;
using namespace glm;

bray::camera::camera()
	: origin(0.0f, 0.0f, 0.0f)
	, lower_left_corner(-2.0f, -1.0f, -1.0f)
	, horizontal(4.0f, 0.0f, 0.0f)
	, vertical(0.0f, 2.0f, 0.0f)
{}
