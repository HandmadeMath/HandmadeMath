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

    void Tick(float deltaSeconds, Input previousInput, Input input) override {
        // TODO: Find a way to do this rotation routine in a single quaternion. Maybe that
        // just means finding a correct method, then doing some quaternion multiplication
        // on paper to see how the axis and angle shake out.

        rotation = GetLookAtRotation();
    }

    hmm_quaternion GetLookAtRotation() {
        hmm_vec3 fwd = (parentModelMatrix * HMM_Vec4(1.0f, 0.0f, 0.0f, 0.0f)).XYZ;
        hmm_vec3 up = (parentModelMatrix * HMM_Vec4(0.0f, 1.0f, 0.0f, 0.0f)).XYZ;
        hmm_vec3 to = target->worldPosition() - worldPosition();
        
        hmm_vec3 pointAxis = HMM_Cross(fwd, to);
        hmm_quaternion justPointAt;

        // TODO: proper epsilon! and probably implement some kind of nan
        // protection because a single nan ruins everything.
        if (HMM_ABS(HMM_Length(pointAxis)) < 0.0001f) {
            // Already pointing at the thing!
            justPointAt = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
        } else {
            justPointAt = HMM_QuaternionFromAxisAngle(
                pointAxis,
                HMM_ACosF(HMM_Dot(HMM_Normalize(fwd), HMM_Normalize(to)))
            );
        }
        
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

        return backUpright * justPointAt;

        // BEN
        // 
        // YOU MUST ALWAYS REMEMBER THAT QUATERNION MULTIPLICATION IS NOT COMMUTATIVE
        // AND THAT IT GOES RIGHT TO LEFT
        // 
        // NEVER FORGET THIS LEST YOU SUFFER THROUGH THIS MESS AGAIN
    }
};

#endif
