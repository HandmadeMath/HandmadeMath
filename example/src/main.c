#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "flextGL.h"
#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#include "../../HandmadeMath.h"

// TODO: Remove this
#include <stdio.h>

typedef struct {
    hmm_mat4 mvp;
    hmm_vec4 color;
} uniforms_t;

typedef struct {
    sg_bindings bindings;
    int numVerts;
} model_t;

model_t triangle;
model_t cube;
model_t cylinder;

model_t initModel(sg_buffer vbuf, sg_buffer ibuf, size_t sizeOfIndices) {
    model_t result = {
        .bindings = (sg_bindings) {
            .vertex_buffers[0] = vbuf,
            .index_buffer = ibuf,
        },
        .numVerts = sizeOfIndices / sizeof(uint16_t),
    };

    return result;
}

#define NUM_CYLINDER_SIDES 32

void initModels() {
    {
        // triangle
        const hmm_vec3 verts[] = {
            HMM_Vec3( 0.0f,  0.5f, 0.0f), HMM_Vec3(0.0f, 0.0f, 1.0f),
            HMM_Vec3( 0.5f, -0.5f, 0.0f), HMM_Vec3(0.0f, 0.0f, 1.0f),
            HMM_Vec3(-0.5f, -0.5f, 0.0f), HMM_Vec3(0.0f, 0.0f, 1.0f),
        };
        const uint16_t indices[] = { 0, 1, 2 };
        sg_buffer vbuf = sg_make_buffer(&(sg_buffer_desc){
            .size = sizeof(verts),
            .content = verts,
        });
        sg_buffer ibuf = sg_make_buffer(&(sg_buffer_desc){
            .type = SG_BUFFERTYPE_INDEXBUFFER,
            .size = sizeof(indices),
            .content = indices,
        });
        triangle = initModel(vbuf, ibuf, sizeof(indices));
    }

    {
        // cube
        const hmm_vec3 verts[] = {
            // front
            HMM_Vec3(-0.5f,  0.5f, 0.5f), HMM_Vec3(0.0f, 0.0f, 1.0f),
            HMM_Vec3(-0.5f, -0.5f, 0.5f), HMM_Vec3(0.0f, 0.0f, 1.0f),
            HMM_Vec3( 0.5f,  0.5f, 0.5f), HMM_Vec3(0.0f, 0.0f, 1.0f),
            HMM_Vec3( 0.5f, -0.5f, 0.5f), HMM_Vec3(0.0f, 0.0f, 1.0f),

            // back
            HMM_Vec3( 0.5f,  0.5f, -0.5f), HMM_Vec3(0.0f, 0.0f, -1.0f),
            HMM_Vec3( 0.5f, -0.5f, -0.5f), HMM_Vec3(0.0f, 0.0f, -1.0f),
            HMM_Vec3(-0.5f,  0.5f, -0.5f), HMM_Vec3(0.0f, 0.0f, -1.0f),
            HMM_Vec3(-0.5f, -0.5f, -0.5f), HMM_Vec3(0.0f, 0.0f, -1.0f),

            // left
            HMM_Vec3(-0.5f,  0.5f, -0.5f), HMM_Vec3(-1.0f, 0.0f, 0.0f),
            HMM_Vec3(-0.5f, -0.5f, -0.5f), HMM_Vec3(-1.0f, 0.0f, 0.0f),
            HMM_Vec3(-0.5f,  0.5f,  0.5f), HMM_Vec3(-1.0f, 0.0f, 0.0f),
            HMM_Vec3(-0.5f, -0.5f,  0.5f), HMM_Vec3(-1.0f, 0.0f, 0.0f),

            // right
            HMM_Vec3(0.5f,  0.5f,  0.5f), HMM_Vec3(1.0f, 0.0f, 0.0f),
            HMM_Vec3(0.5f, -0.5f,  0.5f), HMM_Vec3(1.0f, 0.0f, 0.0f),
            HMM_Vec3(0.5f,  0.5f, -0.5f), HMM_Vec3(1.0f, 0.0f, 0.0f),
            HMM_Vec3(0.5f, -0.5f, -0.5f), HMM_Vec3(1.0f, 0.0f, 0.0f),

            // top
            HMM_Vec3(-0.5f, 0.5f, -0.5f), HMM_Vec3(0.0f, 1.0f, 0.0f),
            HMM_Vec3(-0.5f, 0.5f,  0.5f), HMM_Vec3(0.0f, 1.0f, 0.0f),
            HMM_Vec3( 0.5f, 0.5f, -0.5f), HMM_Vec3(0.0f, 1.0f, 0.0f),
            HMM_Vec3( 0.5f, 0.5f,  0.5f), HMM_Vec3(0.0f, 1.0f, 0.0f),

            // bottom
            HMM_Vec3(-0.5f, -0.5f,  0.5f), HMM_Vec3(0.0f, -1.0f, 0.0f),
            HMM_Vec3(-0.5f, -0.5f, -0.5f), HMM_Vec3(0.0f, -1.0f, 0.0f),
            HMM_Vec3( 0.5f, -0.5f,  0.5f), HMM_Vec3(0.0f, -1.0f, 0.0f),
            HMM_Vec3( 0.5f, -0.5f, -0.5f), HMM_Vec3(0.0f, -1.0f, 0.0f),
        };
        const uint16_t indices[] = {
            0, 1, 2,        2, 1, 3,
            4, 5, 6,        6, 5, 7,
            8, 9, 10,       10, 9, 11,
            12, 13, 14,     14, 13, 15,
            16, 17, 18,     18, 17, 19,
            20, 21, 22,     22, 21, 23,
        };
        sg_buffer vbuf = sg_make_buffer(&(sg_buffer_desc){
            .size = sizeof(verts),
            .content = verts,
        });
        sg_buffer ibuf = sg_make_buffer(&(sg_buffer_desc){
            .type = SG_BUFFERTYPE_INDEXBUFFER,
            .size = sizeof(indices),
            .content = indices,
        });
        cube = initModel(vbuf, ibuf, sizeof(indices));
    }

    {
        // cylinder

        // the vertex order will be:
        // top middle, bottom middle, top cap ring, bottom cap ring, top side ring, bottom side ring

        hmm_vec3 verts[(2 * (1 + NUM_CYLINDER_SIDES) + (2 * NUM_CYLINDER_SIDES)) * 2];
        verts[0] = HMM_Vec3(0.0f, 0.5f, 0.0f);  verts[1] = HMM_Vec3(0.0f, 1.0f, 0.0f);
        verts[2] = HMM_Vec3(0.0f, -0.5f, 0.0f); verts[3] = HMM_Vec3(0.0f, -1.0f, 0.0f);

        const int baseVertIndexTopCapRing = 4; // middles are vert, normal, vert, normal
        const int baseVertIndexBottomCapRing = baseVertIndexTopCapRing + (NUM_CYLINDER_SIDES * 2);
        const int baseVertIndexTopSideRing = baseVertIndexBottomCapRing + (NUM_CYLINDER_SIDES * 2);
        const int baseVertIndexBottomSideRing = baseVertIndexTopSideRing + (NUM_CYLINDER_SIDES * 2);

        for (int i = 0; i < NUM_CYLINDER_SIDES; i++) {
            float t = 2 * HMM_PI32 * (i / (float)NUM_CYLINDER_SIDES);
            float x = HMM_CosF(t);
            float z = HMM_SinF(t);
            hmm_vec3 top = HMM_Vec3(x, 0.5f, z);
            hmm_vec3 bottom = HMM_Vec3(x, -0.5f, z);
            hmm_vec3 sideNormal = HMM_NormalizeVec3(HMM_Vec3(x, 0.0f, z));
            verts[baseVertIndexTopCapRing     + (2 * i)    ] = top;
            verts[baseVertIndexTopCapRing     + (2 * i) + 1] = HMM_Vec3(0.0f, 1.0f, 0.0f);
            verts[baseVertIndexBottomCapRing  + (2 * i)    ] = bottom;
            verts[baseVertIndexBottomCapRing  + (2 * i) + 1] = HMM_Vec3(0.0f, -1.0f, 0.0f);
            verts[baseVertIndexTopSideRing    + (2 * i)    ] = top;
            verts[baseVertIndexTopSideRing    + (2 * i) + 1] = sideNormal;
            verts[baseVertIndexBottomSideRing + (2 * i)    ] = bottom;
            verts[baseVertIndexBottomSideRing + (2 * i) + 1] = sideNormal;
        }

        uint16_t indices[3 * NUM_CYLINDER_SIDES + 3 * NUM_CYLINDER_SIDES + 3 * 2 * NUM_CYLINDER_SIDES];

        // top cap
        for (int i = 0; i < NUM_CYLINDER_SIDES; i++) {
            indices[3 * i] = 0;
            indices[3 * i + 1] = 2 + i;
            indices[3 * i + 2] = 2 + ((i + 1) % NUM_CYLINDER_SIDES);
        }

        // bottom cap
        const int bottomCapBaseIndex = 3 * NUM_CYLINDER_SIDES;
        for (int i = 0; i < NUM_CYLINDER_SIDES; i++) {
            indices[bottomCapBaseIndex + 3 * i]     = 1;
            indices[bottomCapBaseIndex + 3 * i + 1] = (2 + NUM_CYLINDER_SIDES) + ((i + 1) % NUM_CYLINDER_SIDES);
            indices[bottomCapBaseIndex + 3 * i + 2] = (2 + NUM_CYLINDER_SIDES) + i;
        }

        const int sideBaseIndex = bottomCapBaseIndex + 3 * NUM_CYLINDER_SIDES;
        const int topSideRingStart = 2 + NUM_CYLINDER_SIDES + NUM_CYLINDER_SIDES;
        const int bottomSideRingStart = topSideRingStart + NUM_CYLINDER_SIDES;
        for (int i = 0; i < NUM_CYLINDER_SIDES; i++) {
            indices[sideBaseIndex + 6 * i]     = topSideRingStart + i;
            indices[sideBaseIndex + 6 * i + 1] = bottomSideRingStart + i;
            indices[sideBaseIndex + 6 * i + 2] = topSideRingStart + ((i + 1) % NUM_CYLINDER_SIDES);
            indices[sideBaseIndex + 6 * i + 3] = topSideRingStart + ((i + 1) % NUM_CYLINDER_SIDES);
            indices[sideBaseIndex + 6 * i + 4] = bottomSideRingStart + i;
            indices[sideBaseIndex + 6 * i + 5] = bottomSideRingStart + ((i + 1) % NUM_CYLINDER_SIDES);
        }

        sg_buffer vbuf = sg_make_buffer(&(sg_buffer_desc){
            .size = sizeof(verts),
            .content = verts,
        });
        sg_buffer ibuf = sg_make_buffer(&(sg_buffer_desc){
            .type = SG_BUFFERTYPE_INDEXBUFFER,
            .size = sizeof(indices),
            .content = indices,
        });
        cylinder = initModel(vbuf, ibuf, sizeof(indices));
    }
}

int main() {
    /* create window and GL context via GLFW */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(640, 480, "Sokol Triangle GLFW", 0, 0);
    glfwMakeContextCurrent(w);
    glfwSwapInterval(1);
    flextInit(w);

    /* setup sokol_gfx */
    sg_setup(&(sg_desc){0});

    initModels();

    sg_layout_desc layout = {
        .attrs = {
            [0].format=SG_VERTEXFORMAT_FLOAT3,
            [1].format=SG_VERTEXFORMAT_FLOAT3,
        }
    };

    sg_shader shd = sg_make_shader(&(sg_shader_desc){
        .vs = {
            .source =
                "#version 330\n"
                "uniform mat4 mvp;"
                "uniform vec4 color0;"
                "layout(location=0) in vec4 position;\n"
                "out vec4 color;\n"
                "void main() {\n"
                "  gl_Position = mvp * position;\n"
                "  color = color0;\n"
                "}\n",
            .uniform_blocks[0] = {
                .size = sizeof(uniforms_t),
                .uniforms = {
                    [0] = { .name="mvp", .type=SG_UNIFORMTYPE_MAT4 },
                    [1] = { .name="color0", .type=SG_UNIFORMTYPE_FLOAT4 },
                },
            },
        },
        .fs.source =
            "#version 330\n"
            "in vec4 color;\n"
            "out vec4 frag_color;\n"
            "void main() {\n"
            "  frag_color = color;\n"
            "}\n",
    });

    /* a pipeline state object (default render states are fine for triangle) */
    sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
        .shader = shd,
        .layout = layout,
        .index_type = SG_INDEXTYPE_UINT16,
        .depth_stencil = {
            .depth_compare_func = SG_COMPAREFUNC_LESS_EQUAL,
            .depth_write_enabled = true,
        },
        .rasterizer = (sg_rasterizer_state) {
            .cull_mode = SG_CULLMODE_BACK,
            .face_winding = SG_FACEWINDING_CCW,
        },
    });

    /* default pass action (clear to grey) */
    sg_pass_action pass_action = {0};

    double previousTime = glfwGetTime();

    /* draw loop */
    while (!glfwWindowShouldClose(w)) {
        double time = glfwGetTime();
        double deltaTime = time - previousTime;
        double previousTime = time;

        int cur_width, cur_height;
        glfwGetFramebufferSize(w, &cur_width, &cur_height);
        sg_begin_default_pass(&pass_action, cur_width, cur_height);

        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                model_t model = cylinder;

                hmm_mat4 scale = HMM_Scale(HMM_Vec3(0.25f, 0.5f, 0.25f));
                hmm_mat4 rotateZ = HMM_Rotate(HMM_PI32 * i, HMM_Vec3(0.0f, 0.0f, 1.0f));
                hmm_mat4 rotateY = HMM_Rotate(HMM_PI32 / 2.0f * time, HMM_Vec3(0.0f, 1.0f, 0.0f));
                hmm_mat4 rotate = HMM_MultiplyMat4(rotateY, rotateZ);
                hmm_mat4 translate = HMM_Translate(HMM_Vec3(-0.5f + 0.5f * i, -0.5f + 0.5f * j, 0.0f));
                hmm_mat4 m = HMM_MultiplyMat4(translate, HMM_MultiplyMat4(rotate, scale));

                hmm_mat4 v = HMM_Translate(HMM_Vec3(0.0f, 0.0f, -1.0f));

                hmm_mat4 p = HMM_Perspective(HMM_PI32 / 2.0f, 1.0f, 0.01f, 10.0f);

                uniforms_t uniforms = {
                    .mvp = HMM_MultiplyMat4(p, HMM_MultiplyMat4(v, m)),
                    .color = HMM_Vec4((i + j) + 1 & 2, ((i + j) % 2) == 1, ((i + j) % 4) == 2, 1.0f),
                };

                sg_apply_pipeline(pip);
                sg_apply_bindings(&model.bindings);
                sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, &uniforms, sizeof(uniforms));
                sg_draw(0, model.numVerts, 1);
            }
        }

        sg_end_pass();
        sg_commit();
        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    /* cleanup */
    sg_shutdown();
    glfwTerminate();
    return 0;
}
