# Handmade-Math
------

[![Build Status](https://travis-ci.org/StrangeZak/Handmade-Math.svg?branch=master)](https://travis-ci.org/StrangeZak/Handmade-Math)

Single-file cross-platform public domain game math library for C/C++


Version         | Changes        | 
----------------|----------------|
**0.6**   | Made HMM_Power faster, Fixed possible efficiency problem with HMM_Normalize, RENAMED HMM_LengthSquareRoot to HMM_LengthSquared, RENAMED HMM_RSqrtF to HMM_RSquareRootF, RENAMED HMM_SqrtF to HMM_SquareRootF, REMOVED Inner function (user should use Dot now), REMOVED HMM_FastInverseSquareRoot function declaration |
**0.5.2**   | Fixed SSE code in HMM_SqrtF and HMM_RSqrtF |
**0.5.1**   | Fixed HMM_Translate producing row-major matrices, ensured column-major order for matrices throughout |
**0.5**     | Added scalar operations on vectors and matrices, added += and -= for hmm_mat4, reconciled headers and implementations, tidied up in general |
**0.4**     | Added SSE Optimized HMM_SqrtF, HMM_RSqrtF, Removed use of C Runtime | 
**0.3**     | Added +=,-=, *=, /= for hmm_vec2, hmm_vec3, hmm_vec4 | 
**0.2b**    | Disabled warning C4201 on MSVC, Added 64bit percision on HMM_PI | 
**0.2a**    | Prefixed Macros | 
**0.2**     | Updated Documentation, Fixed C Compliance, Prefixed all functions, and added better operator overloading | 
**0.1**     | Initial Version | 

-----
_This library is free and will stay free, but if you would like to support development, or you are a company using HandmadeMath, please consider financial support._


[![Patreon](https://cloud.githubusercontent.com/assets/8225057/5990484/70413560-a9ab-11e4-8942-1a63607c0b00.png)](http://www.patreon.com/strangezak) [![PayPal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif)](https://www.paypal.me/zakarystrange)


## FAQ

**What's the license?**

This library is in the public domain. You can do whatever you want with them.

**Where can I contact you to ask questions?**

You can email me at: Zak@Handmade.Network
