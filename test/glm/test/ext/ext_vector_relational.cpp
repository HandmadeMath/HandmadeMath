#include <glm/ext/vector_relational.hpp>
#include <glm/vec2.hpp>

int test_equal()
{
	int Error = 0;

	Error += glm::equal(1.01f, 1.02f, 0.1f) ? 0 : 1;
	Error += glm::all(glm::equal(glm::vec2(1.01f), glm::vec2(1.02f), 0.1f)) ? 0 : 1;
	Error += glm::all(glm::equal(glm::vec2(1.01f), glm::vec2(1.02f), glm::vec2(0.1f))) ? 0 : 1;

	Error += !glm::equal(1.01f, 1.02f, 0.001f) ? 0 : 1;
	Error += !glm::any(glm::equal(glm::vec2(1.01f), glm::vec2(1.02f), 0.001f)) ? 0 : 1;
	Error += !glm::any(glm::equal(glm::vec2(1.01f), glm::vec2(1.02f), glm::vec2(0.001f))) ? 0 : 1;

	return Error;
}

int test_notEqual()
{
	int Error = 0;

	Error += glm::notEqual(1.01f, 1.02f, 0.001f) ? 0 : 1;
	Error += glm::all(glm::notEqual(glm::vec2(1.01f), glm::vec2(1.02f), 0.001f)) ? 0 : 1;
	Error += glm::all(glm::notEqual(glm::vec2(1.01f), glm::vec2(1.02f), glm::vec2(0.001f))) ? 0 : 1;

	Error += !glm::notEqual(1.01f, 1.02f, 0.1f) ? 0 : 1;
	Error += !glm::any(glm::notEqual(glm::vec2(1.01f), glm::vec2(1.02f), 0.1f)) ? 0 : 1;
	Error += !glm::any(glm::notEqual(glm::vec2(1.01f), glm::vec2(1.02f), glm::vec2(0.1f))) ? 0 : 1;

	return Error;
}

int test_openBounded()
{
	int Error = 0;

	Error += glm::all(glm::openBounded(glm::ivec2(2), glm::ivec2(1), glm::ivec2(3))) ? 0 : 1;
	Error += !glm::all(glm::openBounded(glm::ivec2(1), glm::ivec2(1), glm::ivec2(3))) ? 0 : 1;
	Error += !glm::all(glm::openBounded(glm::ivec2(3), glm::ivec2(1), glm::ivec2(3))) ? 0 : 1;

	return Error;
}

int test_closeBounded()
{
	int Error = 0;

	Error += glm::all(glm::closeBounded(glm::ivec2(2), glm::ivec2(1), glm::ivec2(3))) ? 0 : 1;
	Error += glm::all(glm::closeBounded(glm::ivec2(1), glm::ivec2(1), glm::ivec2(3))) ? 0 : 1;
	Error += glm::all(glm::closeBounded(glm::ivec2(3), glm::ivec2(1), glm::ivec2(3))) ? 0 : 1;

	return Error;
}

int main()
{
	int Error = 0;

	Error += test_equal();
	Error += test_notEqual();
	Error += test_openBounded();
	Error += test_closeBounded();

	return Error;
}
