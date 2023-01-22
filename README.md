# Handmade Math

A single-file, cross-platform, public domain game math library for both C and C++. Supports vectors, matrices, quaternions, and all the utilities you'd expect.

To get started, go download [the latest release](https://github.com/HandmadeMath/HandmadeMath/releases).

> If you are upgrading to version 2 of Handmade Math, save yourself some time and use our [automatic update tool](./update).

Here's what sets Handmade Math apart:

- **A simple single-header library.** Just `#include "HandmadeMath.h"`.
- **Supports both C and C++.** While libraries like GLM only support C++, Handmade Math supports both C and C++, with convenient overloads wherever possible. For example, C++ codebases get operator overloading, and C11 codebases get `_Generic` versions of common operations.
- **Swizzling, sort of.** Handmade Math's vector types use unions to provide several ways of accessing the same underlying data. For example, the components of an `HMM_Vec3` can be accessed as `XYZ`, `RGB`, or `UVW` - or subsets can be accessed like `.XY` and `.YZ`.
- **Your choice of angle unit.** While Handmade Math uses radians by default, you can configure it to use degrees or [turns](https://www.computerenhance.com/p/turns-are-better-than-radians) instead.


## Usage

Simply `#include "HandmadeMath.h"`. All functions are `static inline`, so no need for an "implementation" file as with some other single-header libraries.

A few config options are available. See the header comment in [the source](./HandmadeMath.h) for details.


## FAQ

**What's the license?**

This library is in the public domain. You can do whatever you want with it.

**Where can I contact you to ask questions?**

Feel free to make Github issues for any questions, concerns, or problems you encounter.

**What if I don't want the `HMM_` prefix?**

Do a find and replace in the library source.
