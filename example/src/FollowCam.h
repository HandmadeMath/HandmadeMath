#include <stdio.h>

#ifndef HMME_FOLLOWCAM_H
#define HMME_FOLLOWCAM_H

#include "Entity.h"
#include "HandmadeMath.h"

#include "debug.h"

class FollowCam : public Entity {
public:
    Entity *target;

    FollowCam(Entity *t) {
        target = t;
    }

    // HI BEN HERE IS YOUR STREAM OF CONSCIOUSNESS
    // 
    // Up is wonky. Really this whole thing is a little wonky, although it's
    // gotten pretty close. You need to figure out how to directly calculate the
    // axis and angle so you don't have to do this in two steps. Then it should
    // Just Work.
    // 
    // Although you may have to figure out how to make the camera keep a consistent up vector.
    // 
    // Actually that shouldn't be too hard, because once you have a quaternion
    // LookAt thing, you can just always pass world up to it.

    void Tick(float deltaSeconds) override {
        hmm_vec3 fwd = (parentModelMatrix * HMM_Vec4(1.0f, 0.0f, 0.0f, 0.0f)).XYZ;
        hmm_vec3 up = (parentModelMatrix * HMM_Vec4(0.0f, 1.0f, 0.0f, 0.0f)).XYZ;
        hmm_vec3 to = target->worldPosition() - worldPosition();
        
        hmm_quaternion justPointAt = HMM_QuaternionFromAxisAngle(
            HMM_Cross(fwd, to),
            HMM_ACosF(HMM_Dot(HMM_Normalize(fwd), HMM_Normalize(to)))
        );
        hmm_vec3 newUp = (HMM_QuaternionToMat4(justPointAt) * HMM_Vec4v(up, 0.0f)).XYZ;
        hmm_quaternion backUpright = HMM_QuaternionFromAxisAngle(
            to,
            // TODO: This angle is not quite right! After this corrective rotation,
            // the new up vector will *not* necessarily align with world up! So this
            // will overshoot a little bit.
            // 
            // You should probably project the world up vector onto the plane of the
            // to vector before you do the dot product. This is a good opportunity to
            // add the vector projection stuff that we somehow have left out!
            -HMM_ACosF(HMM_Dot(HMM_Normalize(newUp), HMM_Vec3(0.0f, 1.0f, 0.0f)))
        );
        rotation = backUpright * justPointAt;

        // BEN
        // 
        // YOU MUST ALWAYS REMEMBER THAT QUATERNION MULTIPLICATION IS NOT COMMUTATIVE
        // AND THAT IT GOES RIGHT TO LEFT
        // 
        // NEVER FORGET THIS LEST YOU SUFFER THROUGH THIS MESS AGAIN
    }
};

#endif
