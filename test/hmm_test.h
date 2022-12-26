#include <float.h>

#define HANDMADE_TEST_IMPLEMENTATION
#include "HandmadeTest.h"

#undef COVERAGE // Make sure we don't double-define initializers from the header part
#include "../HandmadeMath.h"

#include "categories/ScalarMath.h"
#include "categories/Initialization.h"
#include "categories/VectorOps.h"
#include "categories/QuaternionOps.h"
#include "categories/Addition.h"
#include "categories/Subtraction.h"
#include "categories/Multiplication.h"
#include "categories/Division.h"
#include "categories/Equality.h"
#include "categories/Projection.h"
#include "categories/Transformation.h"
#include "categories/SSE.h"
#include "categories/InvMatrix.h"
