#include <stdio.h>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <HandmadeMath.h>

#include "shaders.h"

#include "Entity.h"
#include "Cube.h"

void TickTree(Entity *e, float deltaSeconds);
void ComputeModelMatrices(Entity *ep, hmm_mat4 parentModelMatrix);

using std::chrono::high_resolution_clock;

int main()
{
    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if (!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if (window == NULL) {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("src/vertex.glsl", "src/fragment.glsl");
    if (!programID) {
        return 1;
    }

    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    Cube root = Cube();

    Cube child = Cube();
    child.position = HMM_Vec3(2.1f, 0.0f, 0.0f);

    Cube c = Cube();
    child.position = HMM_Vec3(2.1f, 0.0f, 0.0f);

    child.AddChild(&c);
    root.AddChild(&child);

    bool hasTicked = false;
    high_resolution_clock::time_point lastTickTime;

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        hmm_mat4 projection = HMM_Perspective(90.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
        hmm_mat4 view = HMM_LookAt(HMM_Vec3(3.0f, 3.0f, 4.0f), HMM_Vec3(0.0f, 0.0f, 0.0f), HMM_Vec3(0.0f, 1.0f, 0.0f));
        hmm_mat4 vp = projection * view;

        auto now = high_resolution_clock::now();
        if (hasTicked) {
            auto elapsedNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTickTime).count();
            float elapsedSeconds = elapsedNanoseconds / 1000000000.0f;
            TickTree(&root, elapsedSeconds);
        }
        lastTickTime = now;
        hasTicked = true;

        ComputeModelMatrices(&root, HMM_Mat4d(1.0f));

        auto it = EntityIterator(&root);

        while (it.HasNext()) {
            Entity *e = it.Next();

            if (!e->renderComponent.vaoID) {
                continue;
            }

            Entity::RenderComponent rc = e->renderComponent;

            glBindVertexArray(rc.vaoID);

            // 1st attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, rc.vertexBufferID);
            glVertexAttribPointer(
               0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
               3,                  // size
               GL_FLOAT,           // type
               GL_FALSE,           // normalized?
               0,                  // stride
               (void*)0            // array buffer offset
            );

            // 2nd attribute buffer : colors
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, rc.colorBufferID);
            glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
            );
            
            // Use our shader
            glUseProgram(programID);

            hmm_mat4 mvp = vp * e->modelMatrix;

            // Send our transformation to the currently bound shader, in the "MVP" uniform
            // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp.Elements[0][0]);

            // Draw the triangle!
            glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices total -> 1 triangle
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (
        // Check if the ESC key was pressed or the window was closed
        glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0
    );
}

void TickTree(Entity *e, float deltaSeconds) {
    e->Tick(deltaSeconds);

    for (auto child : e->children) {
        TickTree(child, deltaSeconds);
    }
}

void ComputeModelMatrices(Entity *e, hmm_mat4 parentModelMatrix) {
    e->modelMatrix = parentModelMatrix * HMM_Translate(e->position) * HMM_QuaternionToMat4(e->rotation) * HMM_Scale(e->scale);

    for (int i = 0; i < e->children.size(); i++) {
        ComputeModelMatrices(e->children[i], e->modelMatrix);
    }
}
