#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include <random>
#include "camera.h"
#include <thread>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <stb_image_write.h>

using uchar = unsigned char;
using namespace bray;
using namespace glm;
using namespace std;

vec3 random_in_unit_sphere()
{
	static default_random_engine gen;
	static uniform_real_distribution<float> random(0.0f, 1.0f);

	vec3 p;
	do
	{
		p = 2.0f * vec3(random(gen), random(gen), random(gen)) - vec3(1,1,1);
	} while (length(p) >= 1.0f);
	return p;
}

vec3 Color(const Ray& r, hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0.0f, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		//return 0.5f * (rec.normal + vec3(1, 1, 1));
		return 0.5f * Color(Ray(rec.p, target - rec.p), world);
	}
	// Return sky
	vec3 unit_direction = glm::normalize(r.Direction());
	float t = 0.5f * (unit_direction.y + 1.0f);
	return mix(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.7f, 1.0f), t);
}

int main(int argc, char* argv[])
{
	int nx = 400;
	int ny = 200;
	int ns = 100;

	uchar* data = new unsigned char[nx * ny * 3];
	uchar* p = data;

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5f, -1), 100);
	hitable* world = new hitable_list(list, 2);

	default_random_engine gen;
	uniform_real_distribution<float> random(0.0f, 1.0f);
	camera cam;

	auto fun = [&]()
	{
		printf("Tracing from thread.");

		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 color(0, 0, 0);
				for (int s = 0; s < ns; s++)
				{
					float u = float(i + random(gen)) / float(nx);
					float v = float(j + random(gen)) / float(ny);
					Ray r = cam.get_ray(u, v);
					color += Color(r, world);
				}
				color /= float(ns);
				//color = vec3(sqrt(color.x), sqrt(color.y), sqrt(color.z));

				*p++ = uchar(255.99f * color.r);
				*p++ = uchar(255.99f * color.g);
				*p++ = uchar(255.99f * color.b);
			}
		}
	};

	thread thr(fun);

	printf("Main goes on");

	thr.join();
	
	stbi_write_png("image2.png", nx, ny, 3, data, 3*nx);

	delete[] data;
}
