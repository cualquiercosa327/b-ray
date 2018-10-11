#pragma once

#include "ray.h"
#include "hitable.h"

namespace bray
{

class material
{
public:
	virtual bool scatter(
		const Ray& r_in,
		const hit_record& rec,
		glm::vec3& attenuation,
		Ray& scattered) = 0;
};

class lambertian : public material
{
public:
	lambertian(glm::vec3 albedo) : albedo(albedo) {}
	bool scatter(
		const Ray& r_in,
		const hit_record& rec,
		glm::vec3& attenuation,
		Ray& scattered) override;

	glm::vec3 albedo;
};

class metal : public material
{
public:
	metal(glm::vec3 albedo, float f): albedo(albedo)
	{
		if (f < 1) fuzz = f; else fuzz = 1;
	}
	bool scatter(
		const Ray& r_in,
		const hit_record& rec,
		glm::vec3& attenuation,
		Ray& scattered) override;

	glm::vec3 albedo;
	float fuzz;
};

class dielectric : public material
{
public:
	dielectric(float ri) : ref_idx(ri) {}
	bool scatter(
		const Ray& r_in,
		const hit_record& rec,
		glm::vec3& attenuation,
		Ray& scattered) override;
	float ref_idx;
};

}
