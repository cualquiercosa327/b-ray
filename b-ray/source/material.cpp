#include "material.h"
#include <glm/glm.hpp>
#include <random>

using namespace bray;
using namespace glm;

#define M_PI 3.14159265359f

inline float drand48()
{
	return(rand() / (RAND_MAX + 1.0));
}

vec3 random_in_unit_sphere()
{
	/*
	static std::default_random_engine gen;
	static std::uniform_real_distribution<float> random(0.0f, 1.0f);

	vec3 p;
	do
	{
		p = 2.0f * vec3(random(gen), random(gen), random(gen)) - vec3(1.0f, 1.0f, 1.0f);
	} while (length(p) > 1.0f);
	return p;
	*/

	vec3 p;
	do {
		p = 2.0f * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n)*n;
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refrected)
{
	vec3 uv = normalize(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt*(1 - dt * dt);
	if(discriminant > 0)
	{
		refrected = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

bool lambertian::scatter(
	const Ray& r_in,
	const hit_record& rec,
	glm::vec3& attenuation,
	Ray& scattered)
{
	vec3 target = rec.p + rec.normal + random_in_unit_sphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}

bool metal::scatter(
	const Ray& r_in,
	const hit_record& rec,
	glm::vec3& attenuation,
	Ray& scattered)
{
	vec3 reflected = reflect(normalize(r_in.Direction()), rec.normal);
	//scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
	scattered = Ray(rec.p, reflected);
	attenuation = albedo;	
	return dot(scattered.Direction(), rec.normal) > 0.0f;
}

bool dielectric::scatter(
	const Ray& r_in,
	const hit_record& rec,
	glm::vec3& attenuation,
	Ray& scattered)
{
	vec3 outward_normal;
	vec3 reflected = reflect(r_in.Direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1, 1, 1);
	vec3 refracted;

	// Tracing ray getting in or getting out
	if(dot(r_in.Direction(), rec.normal) > 0)
	{
		outward_normal = -rec.normal;
		ni_over_nt = ref_idx;
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.0f / ref_idx;
	}

	if(refract(r_in.Direction(), outward_normal, ni_over_nt, refracted))
	{
		scattered = Ray(rec.p, refracted);
	}
	else 
	{
		scattered = Ray(rec.p, reflected);
		return false;
	}
	return true;
}
