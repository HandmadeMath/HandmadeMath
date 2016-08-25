# Handmade-Math
------
Single-file public domain game math library for C/C++


Version         | Changes        | 
----------------|----------------|
**0.5**         | Added scalar operations on vectors and matrices, added += and -= for hmm_mat4, reconciled headers and implementations, tidied up in general |
**0.4**         | Added SSE Optimized HMM_SqrtF, HMM_RSqrtF, Removed use of CRT | 
**0.3**         | Added +=,-=, *=, /= for hmm_vec2, hmm_vec3, hmm_vec4 | 
**0.2b**        | Disabled warning C4201 on MSVC, Added 64bit percision on HMM_PI | 
**0.2a**        | Prefixed Macros | 
**0.2**         | Updated Documentation, Fixed C Compliance, Prefixed all functions, and added better operator overloading | 
**0.1**         | Initial Version | 

_ID: In Development_


## FAQ

**What's the license?**

This library is in the public domain. You can do whatever you want with them.

**Where can I contact you to ask questions?**

You can email me at: Zak@Handmade.Network


## Testing

```shell
cd test
make
./hmm_test
```
