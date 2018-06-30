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
        // rotation = HMM_QuaternionFromAxisAngle(target->worldPosition() - worldPosition(), 0.0f);
        // rotation = HMM_QuaternionFromAxisAngle(HMM_Vec3(0.0f, 1.0f, 0.0f), HMM_ToRadians(0.0f));
        // rotation = HMM_Qu
        
        hmm_vec3 fwd = (parentModelMatrix * HMM_Vec4(1.0f, 0.0f, 0.0f, 0.0f)).XYZ;
        hmm_vec3 up = (parentModelMatrix * HMM_Vec4(0.0f, 1.0f, 0.0f, 0.0f)).XYZ;
        hmm_vec3 to = target->worldPosition() - worldPosition();
        float dot = HMM_DotVec3(fwd, HMM_NormalizeVec3(to));

        if (HMM_ABS(dot - 1.0f) < 0.000001f) {
            // do nothing to the rotation
        } else if (HMM_ABS(dot + 1.0f) < 0.000001f) {
            // rotate 180 I guess but for now do nothing
        } else {
            hmm_vec3 cross = HMM_Normalize(HMM_Cross(fwd, to));

            rotation = HMM_QuaternionFromAxisAngle(    
                cross,
                HMM_ACOSF(dot)
            );
            rotation *= HMM_QuaternionFromAxisAngle(
                HMM_Vec3(1.0f, 0.0f, 0.0f),
                -HMM_ACOSF(HMM_DotVec3(cross, up))
            );
        }

        printf("Sort of working:\n");
        printQuaternion(rotation);
        printVec4(HMM_QuaternionToMat4(rotation) * HMM_Vec4(1.0f, 0.0f, 0.0f, 0.0f));
        printMat4(HMM_QuaternionToMat4(rotation));
        // return;

        hmm_mat4 look = HMM_LookAt(HMM_Vec3(0.0f, 0.0f, 0.0f), HMM_Normalize(target->worldPosition() - worldPosition()), HMM_Vec3(0.0f, 1.0f, 0.0f));
        rotation = HMM_Mat4ToQuaternion(look);
        printf("New stuff:\n");
        printQuaternion(rotation);
        printVec4(HMM_QuaternionToMat4(rotation) * HMM_Vec4(1.0f, 0.0f, 0.0f, 0.0f));
        printMat4(HMM_QuaternionToMat4(rotation));
        // return;

        rotation = HMM_QuaternionFromVectors(HMM_Vec3(0.001462f, -0.449079f, -0.893491f), HMM_Vec3(0.0f, 1.0f, 0.0f));
        printf("Newer stuff:\n");
        printQuaternion(rotation);
        printVec4(HMM_QuaternionToMat4(rotation) * HMM_Vec4(1.0f, 0.0f, 0.0f, 0.0f));
        printMat4(HMM_QuaternionToMat4(rotation));
        // return;
        
        printf("nighttime genius:\n");
        hmm_vec3 right = HMM_Cross(to, up);
        hmm_quaternion tiltUp = HMM_QuaternionFromAxisAngle(
            right,
            HMM_PI / 2 - HMM_ACosF(HMM_Dot(HMM_Normalize(to), HMM_Normalize(up)))
        );
        hmm_vec3 tiltedFwd = (HMM_QuaternionToMat4(tiltUp) * HMM_Vec4v(fwd, 0.0f)).XYZ;
        hmm_quaternion pointAt = HMM_QuaternionFromAxisAngle(
            HMM_Cross(right, to),
            HMM_ACosF(HMM_Dot(HMM_Normalize(tiltedFwd), HMM_Normalize(to)))
        );
        rotation = tiltUp * pointAt;
        printQuaternion(rotation);
        printVec4(HMM_QuaternionToMat4(rotation) * HMM_Vec4(1.0f, 0.0f, 0.0f, 0.0f));
        printMat4(HMM_QuaternionToMat4(rotation));
        // dot products make this bad :(
        
        // rotate around up vector first?
        
        // just look, forget the up direction for a bit
        hmm_quaternion justPointAt = HMM_QuaternionFromAxisAngle(
            HMM_Cross(fwd, to),
            HMM_ACosF(HMM_Dot(HMM_Normalize(fwd), HMM_Normalize(to)))
        );
        hmm_vec3 newUp = (HMM_QuaternionToMat4(justPointAt) * HMM_Vec4v(up, 0.0f)).XYZ;
        hmm_quaternion backUpright = HMM_QuaternionFromAxisAngle(
            to,
            -HMM_ACosF(HMM_Dot(HMM_Normalize(newUp), HMM_Vec3(0.0f, 1.0f, 0.0f)))
        );
        rotation = backUpright * justPointAt;
    }
};

#endif
