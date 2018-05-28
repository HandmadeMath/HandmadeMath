#include <string>
#include <vector>

#ifndef HMME_MESH_RENDER_COMPONENT_H
#define HMME_MESH_RENDER_COMPONENT_H

#include "tiny_obj_loader.h"

class MeshRenderComponent : public RenderComponent {
public:
    bool didLoad = false;

    struct Shape {
        GLuint vaoID = 0;
        GLuint vertexBufferID = 0;
        GLuint normalBufferID = 0;
        GLuint uvBufferID = 0;
        GLuint colorBufferID = 0;
        int numVerts = 0;
    };
    std::vector<Shape> renderShapes;

    MeshRenderComponent(const char *filename) {
        // Load the model
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename);
          
        if (!err.empty()) { // `err` may contain warning message.
            printf("Failed to load mesh: %s\n", err.c_str());
        }

        if (!ret) {
            return;
        }

        for (auto shape : shapes) {
            std::vector<tinyobj::real_t> vertices;
            std::vector<tinyobj::real_t> normals;
            std::vector<tinyobj::real_t> uvs;
            std::vector<tinyobj::real_t> colors;

            for (auto indices : shape.mesh.indices) {
                if (indices.vertex_index > -1) {
                    for (int i = 0; i < 3; i++) {
                        int attribIndex = 3 * indices.vertex_index + i;
                        vertices.push_back(attrib.vertices[attribIndex]);
                        colors.push_back(attrib.colors[attribIndex]);
                    }
                }
                if (indices.normal_index > -1) {
                    for (int i = 0; i < 3; i++) {
                        int attribIndex = 3 * indices.normal_index + i;
                        normals.push_back(attrib.normals[attribIndex]);
                    }
                }
                if (indices.texcoord_index > -1) {
                    for (int i = 0; i < 2; i++) {
                        int attribIndex = 2 * indices.texcoord_index + i;
                        uvs.push_back(attrib.texcoords[attribIndex]);
                    }
                }
            }

            Shape s; // the new shape to insert into our list

            glGenVertexArrays(1, &s.vaoID);

            if (!vertices.empty()) {
                glGenBuffers(1, &s.vertexBufferID);
                glBindBuffer(GL_ARRAY_BUFFER, s.vertexBufferID);
                glBufferData(GL_ARRAY_BUFFER, sizeof(tinyobj::real_t) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

                glGenBuffers(1, &s.colorBufferID);
                glBindBuffer(GL_ARRAY_BUFFER, s.colorBufferID);
                glBufferData(GL_ARRAY_BUFFER, sizeof(tinyobj::real_t) * colors.size(), &colors.front(), GL_STATIC_DRAW);
            }
            
            if (!normals.empty()) {
                glGenBuffers(1, &s.normalBufferID);
                glBindBuffer(GL_ARRAY_BUFFER, s.normalBufferID);
                glBufferData(GL_ARRAY_BUFFER, sizeof(tinyobj::real_t) * normals.size(), &normals.front(), GL_STATIC_DRAW);
            }

            if (!uvs.empty()) {
                glGenBuffers(1, &s.uvBufferID);
                glBindBuffer(GL_ARRAY_BUFFER, s.uvBufferID);
                glBufferData(GL_ARRAY_BUFFER, sizeof(tinyobj::real_t) * uvs.size(), &uvs.front(), GL_STATIC_DRAW);
            }

            s.numVerts = vertices.size() / 3;

            renderShapes.push_back(s);
        }

        didLoad = true;
    }

    void Draw() override {
        if (!didLoad) {
            return;
        }

        for (auto s : renderShapes) {
            glBindVertexArray(s.vaoID);

            // 1st attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, s.vertexBufferID);
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
            glBindBuffer(GL_ARRAY_BUFFER, s.colorBufferID);
            glVertexAttribPointer(
                1,                 // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                 // size
                GL_FLOAT,          // type
                GL_FALSE,          // normalized?
                0,                 // stride
                (void*)0           // array buffer offset
            );

            if (s.normalBufferID != 0) {
                // 3rd attribute buffer : normals
                glEnableVertexAttribArray(2);
                glBindBuffer(GL_ARRAY_BUFFER, s.normalBufferID);
                glVertexAttribPointer(
                    2,                 // must match the layout in the shader
                    3,                 // size
                    GL_FLOAT,          // type
                    GL_FALSE,          // normalized?
                    0,                 // stride
                    (void*)0           // array buffer offset
                );
            }

            if (s.uvBufferID != 0) {
                // 4th attribute buffer : uvs
                glEnableVertexAttribArray(3);
                glBindBuffer(GL_ARRAY_BUFFER, s.normalBufferID);
                glVertexAttribPointer(
                    3,                 // must match the layout in the shader
                    2,                 // size
                    GL_FLOAT,          // type
                    GL_FALSE,          // normalized?
                    0,                 // stride
                    (void*)0           // array buffer offset
                );
            }
            
            // Shader??

            // Draw the triangle!
            glDrawArrays(GL_TRIANGLES, 0, s.numVerts); // Starting from vertex 0; 3 vertices total -> 1 triangle
            
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            if (s.normalBufferID != 0) {
                glDisableVertexAttribArray(2);
            }
            if (s.uvBufferID != 0) {
                glDisableVertexAttribArray(3);
            }
        }
    }
};

#endif
