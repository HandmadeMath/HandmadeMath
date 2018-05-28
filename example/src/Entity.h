#include <vector>

#include <HandmadeMath.h>

#ifndef HMME_ENTITY_H
#define HMME_ENTITY_H

class Entity {
public:
    hmm_vec3 position = HMM_Vec3(0.0f, 0.0f, 0.0f);
    hmm_quaternion rotation = HMM_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    hmm_vec3 scale = HMM_Vec3(1.0f, 1.0f, 1.0f);

    std::vector<Entity*> children;

    void AddChild(Entity* e) {
        children.push_back(e);
    }

    virtual void Tick(float deltaTime) {}

    struct RenderComponent {
        GLuint vaoID;
        GLuint vertexBufferID;
        GLuint colorBufferID;
    };
    RenderComponent renderComponent;

    // Context for rendering and stuff
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
