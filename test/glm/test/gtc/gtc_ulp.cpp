#include <glm/gtc/ulp.hpp>
#include <glm/gtc/epsilon.hpp>
#include <limits>

int test_ulp_float_dist()
{
	int Error = 0;

	float A = 1.0f;

	float B = glm::next_float(A);
	Error += !glm::epsilonEqual(A, B, glm::epsilon<float>()) ? 0 : 1;
	float C = glm::prev_float(B);
	Error += glm::epsilonEqual(A, C, glm::epsilon<float>()) ? 0 : 1;

	int D = glm::float_distance(A, B);
	Error += D == 1 ? 0 : 1;
	int E = glm::float_distance(A, C);
	Error += E == 0 ? 0 : 1;

	return Error;
}

int test_ulp_float_step()
{
	int Error = 0;

	float A = 1.0f;

	for(int i = 10; i < 1000; i *= 10)
	{
		float B = glm::next_float(A, i);
		Error += !glm::epsilonEqual(A, B, glm::epsilon<float>()) ? 0 : 1;
		float C = glm::prev_float(B, i);
		Error += glm::epsilonEqual(A, C, glm::epsilon<float>()) ? 0 : 1;

		int D = glm::float_distance(A, B);
		Error += D == i ? 0 : 1;
		int E = glm::float_distance(A, C);
		Error += E == 0 ? 0 : 1;
	}

	return Error;
}

int test_ulp_double_dist()
{
	int Error = 0;

	double A = 1.0;

	double B = glm::next_float(A);
	Error += !glm::epsilonEqual(A, B, glm::epsilon<double>()) ? 0 : 1;
	double C = glm::prev_float(B);
	Error += glm::epsilonEqual(A, C, glm::epsilon<double>()) ? 0 : 1;

	int D = glm::float_distance(A, B);
	Error += D == 1 ? 0 : 1;
	int E = glm::float_distance(A, C);
	Error += E == 0 ? 0 : 1;

	return Error;
}

int test_ulp_double_step()
{
	int Error = 0;

	double A = 1.0;

	for(int i = 10; i < 1000; i *= 10)
	{
		double B = glm::next_float(A, i);
		Error += !glm::epsilonEqual(A, B, glm::epsilon<double>()) ? 0 : 1;
		double C = glm::prev_float(B, i);
		Error += glm::epsilonEqual(A, C, glm::epsilon<double>()) ? 0 : 1;

		int D = glm::float_distance(A, B);
		Error += D == i ? 0 : 1;
		int E = glm::float_distance(A, C);
		Error += E == 0 ? 0 : 1;
	}

	return Error;
}

int main()
{
	int Error = 0;
	Error += test_ulp_float_dist();
	Error += test_ulp_float_step();
	Error += test_ulp_double_dist();
	Error += test_ulp_double_step();
	return Error;
}


