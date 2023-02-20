# Handmade Math

A single-file, cross-platform, public domain graphics math library for both C and C++. Supports vectors, matrices, quaternions, and all the utilities you'd expect.

To get started, go download [the latest release](https://github.com/HandmadeMath/HandmadeMath/releases).

> If you are upgrading to Handmade Math 2.0, save yourself some time and use our [automatic update tool](./update).

Here's what sets Handmade Math apart:

- **A simple single-header library.** Just `#include "HandmadeMath.h"`.
- **Supports both C and C++.** While libraries like GLM only support C++, Handmade Math supports both C and C++, with convenient overloads wherever possible. For example, C++ codebases get operator overloading, and C11 codebases get `_Generic` versions of common operations.
- **Supports all graphics APIs.** Handmade Math has left- and right-handed versions of each operation, as well as support for zero-to-one and negative-one-to-one NDC conventions.
- **Swizzling, sort of.** Handmade Math's vector types use unions to provide several ways of accessing the same underlying data. For example, the components of an `HMM_Vec3` can be accessed as `XYZ`, `RGB`, or `UVW` - or subsets can be accessed like `.XY` and `.YZ`.
- **Your choice of angle unit.** While Handmade Math uses radians by default, you can configure it to use degrees or [turns](https://www.computerenhance.com/p/turns-are-better-than-radians) instead.


## Usage

Simply `#include "HandmadeMath.h"`. All functions are `static inline`, so there is no need for an "implementation" file as with some other single-header libraries.

A few config options are available. See the header comment in [the source](./HandmadeMath.h) for details.


## FAQ

**What conventions does HMM use, e.g. row vs. column major, handedness, etc.?**

Handmade Math's matrices are column-major, i.e. data is stored by columns, then rows. It also assumes column vectors, i.e. vectors are written vertically and matrix-vector multiplication is `M * V` instead of `V * M`. For more information, see [this issue](https://github.com/HandmadeMath/HandmadeMath/issues/124#issuecomment-775737253).

For other properties, we provide variants for each common convention. Functions that care about handedness have left-handed (`LH`) and right-handed (`RH`) variants. Projection functions have zero-to-one (`ZO`) and negative-one-to-one (`NO`) variants for different NDC conventions.

**What if I don't want the `HMM_` prefix?**

Do a find and replace in the library source.

**What's the license?**

This library is in the public domain. You can do whatever you want with it.

**Where can I contact you to ask questions?**

Feel free to make GitHub issues for any questions, concerns, or problems you encounter.
