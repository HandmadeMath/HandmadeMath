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
* Put macros and return types on a separate line from the function definition:
  ```cpp
  HINLINE float
  HMM_MyFunction()
  {
      // ...
  }
  ```
* Explicitly initialize variables to zero:
  ```cpp
  HINLINE float
  HMM_MyFunction()
  {
      float MyFloat = 0.0f;
      hmm_vec3 MyVector = {0};
  }
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
