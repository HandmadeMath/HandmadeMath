
#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_CPP_MODE
#define HANDMADE_MATH_NO_INLINE
#include "../HandmadeMath.h"

#ifndef gb_abs
#define gb_abs(x) ((x) > 0 ? (x) : -(x))
#endif

#define GB_MATH_TAU_OVER_2   3.14159265358979323846264338327950288f
#define GB_MATH_TAU_OVER_4   1.570796326794896619231321691639751442f
#define GB_MATH_TAU_OVER_8   0.785398163397448309615660845819875721f

static float gb_arctan(float a);
static float gb_arctan2(float y, float x);

float gb_arccos(float a) { return gb_arctan2(HMM_SquareRootF((1.0f + a) * (1.0 - a)), a); }

float
gb_arctan(float a)
{
	float u = a*a;
	float u2 = u*u;
	float u3 = u2*u;
	float u4 = u3*u;
	float f = 1.0f + 0.33288950512027f*u - 0.08467922817644f*u2 + 0.03252232640125f*u3 - 0.00749305860992f*u4;
	return a / f;
}

float
gb_arctan2(float y, float x)
{
	if (gb_abs(x) > gb_abs(y)) {
		float a = gb_arctan(y / x);
		if (x > 0.0f)
			return a;
		else
			return y > 0.0f ? a + GB_MATH_TAU_OVER_2 : a - GB_MATH_TAU_OVER_2;
	}
	else {
		float a = gb_arctan(x / y);
		if (x > 0.0f)
			return y > 0.0f ? GB_MATH_TAU_OVER_4 - a : -GB_MATH_TAU_OVER_4 - a;
		else
			return y > 0.0f ? GB_MATH_TAU_OVER_4 + a : -GB_MATH_TAU_OVER_4 + a;
	}
}

int main() {

	hmm_quaternion q1 = { 0,1,0 };
	hmm_quaternion q2 = { 0,0,0 };
	hmm_quaternion Result = { 0 };
	float time = 0.5f;

	hmm_quaternion x, y, z;
	float cos_theta, angle;
	float s1, s2, is;

	z = q2;
	cos_theta = HMM_DotQuat(q1, q2);

	angle = gb_arccos(cos_theta);

	s1 = HMM_SinF(1.0f - time*angle);
	s2 = HMM_SinF(time*angle);
	is = 1.0f / HMM_SinF(angle);

	x.X = z.X * s1;
	x.Y = z.Y * s1;
	x.Z = z.Z * s1;
	x.W = z.W * s1;

	y.X = z.X * s2;
	y.Y = z.Y * s2;
	y.Z = z.Z * s2;
	y.W = z.W * s2;

	Result.X = x.X + y.X;
	Result.Y = x.Y + y.Y;
	Result.Z = x.Z + y.Z;
	Result.W = x.W + y.W;

	Result.X = Result.X * is;
	Result.Y = Result.Y * is;
	Result.Z = Result.Z * is;
	Result.W = Result.W * is;

return 0;
}