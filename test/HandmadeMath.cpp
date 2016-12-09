
#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_CPP_MODE
#define HANDMADE_MATH_NO_INLINE
#define GB_MATH_IMPLEMENTATION
#include "../HandmadeMath.h"
#include "../gb_math.h"

int main() {

	hmm_quaternion q1 = { 1,0,0,0 };
	hmm_quaternion q2 = { 0,1,0,0 };

	gbQuat q3 = { 1,0,0,0 };
	gbQuat q4 = { 0,1,0,0 };
	gbQuat result2 = { 0 };

	float time = 0.5f;

	hmm_quaternion Result = HMM_Slerp(q1, q2, time);
	gb_quat_slerp(&result2, q3, q4, time);



return 0;
}