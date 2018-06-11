#include <vector>

#include <HandmadeMath.h>

#ifndef HMME_ENTITY_H
#define HMME_ENTITY_H

#include "RenderComponent.h"

class Entity {
public:
    hmm_vec3 position = HMM_Vec3(0.0f, 0.0f, 0.0f);
    hmm_quaternion rotation = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    hmm_vec3 scale = HMM_Vec3(1.0f, 1.0f, 1.0f);

    std::vector<Entity*> children;

    void AddChild(Entity* e) {
        children.push_back(e);
    }

    virtual void Tick(float deltaSeconds) {}

    RenderComponent *renderComponent = NULL;

    struct CameraInfo {
        float fov = 90.0f;
        float aspect = 1024.0f / 768.0f;
        float near = 0.1f;
        float far = 100.0f;
    };
    CameraInfo camera;

    hmm_mat4 projectionMatrix() {
        return HMM_Perspective(camera.fov, camera.aspect, camera.near, camera.far);
    }

    hmm_mat4 viewMatrix() {
        return HMM_LookAt(worldPosition(), worldPosition() + forward(), up());
    }

    hmm_vec3 worldPosition() {
        return (modelMatrix * HMM_Vec4(0.0f, 0.0f, 0.0f, 1.0f)).XYZ;
    }

    hmm_vec3 up() {
        return (modelMatrix * HMM_Vec4(0.0f, 1.0f, 0.0f, 1.0f)).XYZ - worldPosition();
    }

    hmm_vec3 forward() {
        return (modelMatrix * HMM_Vec4(1.0f, 0.0f, 0.0f, 1.0f)).XYZ - worldPosition();
    }

    hmm_vec3 right() {
        return (modelMatrix * HMM_Vec4(0.0f, 0.0f, 1.0f, 1.0f)).XYZ - worldPosition();
    }

    // Context for rendering and stuff
    hmm_mat4 parentModelMatrix;
    hmm_mat4 modelMatrix;
};

class EntityIterator {
public:
    typedef struct State {
        Entity *entity;
        int childIndex;

        State(Entity *e) {
            entity = e;
            childIndex = -1;
        }
    } State;

    EntityIterator(Entity *e) {
        stack.push_back(State(e));
    }

    bool HasNext() {
        return !stack.empty();
    }

    Entity *Next() {
        Entity *result = 0;

        // Pass 1 - get a result by either grabbing the current entity or making another state
        while (true) {
            State *state = &stack.back();

            if (state->childIndex < 0) {
                result = state->entity;
                state->childIndex = 0;
                break;
            } else {
                int nextIndex = state->childIndex;
                state->childIndex++;
                stack.push_back(State(state->entity->children[nextIndex]));
            }
        }

        // Pass 2 - remove exhausted states from the stack
        while (!stack.empty()) {
            State state = stack.back();

            if (state.childIndex >= state.entity->children.size()) {
                stack.pop_back();
            } else {
                break;
            }
        }

        return result;
    }

private:
    std::vector<State> stack;
};

#endif
