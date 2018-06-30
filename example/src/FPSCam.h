#include <stdio.h>

#ifndef HMME_FPSCAM_H
#define HMME_FPSCAM_H

#include "Entity.h"
#include "FollowCam.h"
#include "HandmadeMath.h"

#include "debug.h"

class FPSCam : public Entity {
public:
    FollowCam cam = FollowCam(0); // TODO: Why on earth is this necessary?? Remove this and fix the error.
    Entity target;

    FPSCam() {
        target = Entity();
        target.position = HMM_Vec3(1.0f, 0.0f, 0.0f);

        cam = FollowCam(&target);

        AddChild(&target);
        AddChild(&cam);
    }

    float x = 0;

    void Tick(float deltaSeconds) override {
        x += deltaSeconds;
        rotation *= HMM_QuaternionFromAxisAngle(HMM_Vec3(0.0f, 1.0f, 0.0f), deltaSeconds * HMM_ToRadians(45.0f));
    }
};

#endif
