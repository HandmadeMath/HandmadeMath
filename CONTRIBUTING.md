# Understanding the structure of Handmade Math

Most of the functions in Handmade Math are very short, and all are the kind of functions you want to be easily inlined for performance. Because of this, all functions in Handmade Math are defined with `HMM_INLINE`, which is defined as `static inline`.

# Quick style guide

* Put braces on a new line
* Float literals should have digits both before and after the decimal.
  ```cpp
  // Good
  0.0f;
  0.5f;
  1.0f;
  3.14159f;

  // Bad
  1.f
  .0f
  ```
* Put parentheses around the returned value:
  ```cpp
  HINLINE float
  HMM_MyFunction()
  {
      return (1.0f);
  }
  ```


## Other style notes

* If a new function is defined with different names for different datatypes, also add C++ overloaded versions of the functions. For example, if you have `HMM_LengthVec2(hmm_vec2)` and `HMM_LengthVec3(hmm_vec3)`, also provide `HMM_Length(hmm_vec2)` and `HMM_Length(hmm_vec3)`.

  It is fine for the overloaded versions to call the C versions.
* Only use operator overloading for analogous operators in C. That means `+` for vector addition is fine, but no using `^` for cross product or `|` for dot product.
* Try to define functions in the same order as the prototypes.
* Don't forget that Handmade Math uses column-major order for matrices!

# Versioning

We use [semantic versioning](http://semver.org/) because it's reasonable.
