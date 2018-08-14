#include <stdio.h>
#include <tgmath.h>

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

    // all angles in radians
    float yaw = 0;
    float pitch = 0;
    float sensitivity = 0.002f;

    FPSCam() {
        target = Entity();
        target.position = HMM_Vec3(0.0f, 0.0f, -1.0f);

        cam = FollowCam(&target);

        AddChild(&target);
        AddChild(&cam);
    }

    void Tick(float deltaSeconds, Input previousInput, Input input) override {
        double deltaX = input.mouseX - previousInput.mouseX;
        double deltaY = input.mouseY - previousInput.mouseY;

        // HACK: Pitch is being weird for reasons I don't understand. It works fine for
        // 360 degrees, then does something silly for 360 degrees, then repeats. I suspect
        // I'm just doing something wrong with quaternions because I know they encode twice
        // the angle or whatever. In any case, I've hacked around it for now to splice
        // together ranges that work.

        yaw = yaw + (-deltaX * sensitivity);
        pitch = HMM_Clamp(-HMM_PI32 / 2, pitch + (-deltaY * sensitivity), HMM_PI32 / 2);

        // HACK: MEGAHACK: why the heck is the apparent rotation twice what it should be?
        float hackyPitch = HMM_PI32;
        if (pitch > 0) {
            hackyPitch = HMM_PI32 + pitch / 2;
        } else if (pitch < 0) {
            hackyPitch = 2 * HMM_PI32 + pitch / 2;
        }
        printf("%f\t%f\n", pitch, hackyPitch);

        hmm_quaternion rotationYaw = HMM_QuaternionFromAxisAngle(HMM_Vec3(0.0f, 1.0f, 0.0f), yaw);
        hmm_quaternion rotationPitch = HMM_QuaternionFromAxisAngle(HMM_Vec3(1.0f, 0.0f, 0.0f), hackyPitch);

        rotation = rotationPitch * rotationYaw;
    }
};

#endif
