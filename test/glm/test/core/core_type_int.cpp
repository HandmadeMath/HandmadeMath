#include <glm/glm.hpp>

static int test_int_size()
{
	return
		sizeof(glm::int_t) != sizeof(glm::lowp_int) &&
		sizeof(glm::int_t) != sizeof(glm::mediump_int) && 
		sizeof(glm::int_t) != sizeof(glm::highp_int);
}

static int test_uint_size()
{
	return
		sizeof(glm::uint_t) != sizeof(glm::lowp_uint) &&
		sizeof(glm::uint_t) != sizeof(glm::mediump_uint) && 
		sizeof(glm::uint_t) != sizeof(glm::highp_uint);
}

static int test_int_precision()
{
	return (
		sizeof(glm::lowp_int) <= sizeof(glm::mediump_int) && 
		sizeof(glm::mediump_int) <= sizeof(glm::highp_int)) ? 0 : 1;
}

static int test_uint_precision()
{
	return (
		sizeof(glm::lowp_uint) <= sizeof(glm::mediump_uint) && 
		sizeof(glm::mediump_uint) <= sizeof(glm::highp_uint)) ? 0 : 1;
}

static int test_bit_operator()
{
	int Error = 0;

	glm::ivec4 const a(1);
	glm::ivec4 const b = ~a;
	Error += glm::all(glm::equal(b, glm::ivec4(-2))) ? 0 : 1;

	glm::int32 const c(1);
	glm::int32 const d = ~c;
	Error += d == -2 ? 0 : 1;

	return Error;
}

int main()
{
	int Error = 0;

	Error += test_int_size();
	Error += test_int_precision();
	Error += test_uint_size();
	Error += test_uint_precision();
	Error += test_bit_operator();

	return Error;
}
