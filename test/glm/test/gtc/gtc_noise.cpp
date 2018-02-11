#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/noise.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtx/raw_data.hpp>

int test_simplex()
{
	int Error = 0;

	glm::u8vec4 const PixelSimplex2D(glm::byte(glm::abs(glm::simplex(glm::vec2(0.f, 0.f))) * 255.f));
	glm::u8vec4 const PixelSimplex3D(glm::byte(glm::abs(glm::simplex(glm::vec3(0.f, 0.f, 0.f))) * 255.f));
	glm::u8vec4 const PixelSimplex4D(glm::byte(glm::abs(glm::simplex(glm::vec4(0.f, 0.f, 0.f, 0.f))) * 255.f));

	return Error;
}

int test_perlin()
{
	int Error = 0;

	glm::u8vec4 const PixelPerlin2D(glm::byte(glm::abs(glm::perlin(glm::vec2(0.f, 0.f))) * 255.f));
	glm::u8vec4 const PixelPerlin3D(glm::byte(glm::abs(glm::perlin(glm::vec3(0.f, 0.f, 0.f))) * 255.f));
	glm::u8vec4 const PixelPerlin4D(glm::byte(glm::abs(glm::perlin(glm::vec4(0.f, 0.f, 0.f, 0.f))) * 255.f));

	return Error;
}

int test_perlin_pedioric()
{
	int Error = 0;

	glm::u8vec4 const PixelPeriodic2D(glm::byte(glm::abs(glm::perlin(glm::vec2(0.f, 0.f), glm::vec2(2.0f))) * 255.f));
	glm::u8vec4 const PixelPeriodic3D(glm::byte(glm::abs(glm::perlin(glm::vec3(0.f, 0.f, 0.f), glm::vec3(2.0f))) * 255.f));
	glm::u8vec4 const PixelPeriodic4D(glm::byte(glm::abs(glm::perlin(glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(2.0f))) * 255.f));

	return Error;
}

int main()
{
	int Error = 0;

	Error += test_simplex();
	Error += test_perlin();
	Error += test_perlin_pedioric();

	return Error;
}
