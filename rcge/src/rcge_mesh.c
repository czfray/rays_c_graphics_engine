#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <rcge/rcge_shader.h>
#include <rcge/rcge_transform.h>
#include <rcge/rcge_texture.h>
#include <rcge/rcge_mesh.h>
#include <rcge/rcge_datatype.h>

#include <stdio.h>
#include <stdlib.h>

struct rcge_mesh_CDT
{
    rcge_transform transform;
    rcge_texture texture;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    unsigned int vert_no;
};

GLenum gl_mesh_draw_type(rcge_mesh_draw_type type)
{
    switch(type)
    {
        case MESH_DYNAMIC: return GL_DYNAMIC_DRAW;
        case MESH_STATIC: return GL_STATIC_DRAW;
        case MESH_STREAM: return GL_STREAM_DRAW;
    }
    return GL_DYNAMIC_DRAW;
}

rcge_mesh rcge_mesh_create(rcge_shader shader, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, rcge_mesh_draw_type draw_type)
{
    GLenum gl_draw_type = gl_mesh_draw_type(draw_type);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(float), vertices, gl_draw_type);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(float), indices, gl_draw_type);

    rcge_shader_attrib_activate_mesh(shader);

    rcge_mesh mesh = malloc(sizeof(*mesh)); //TODO: malloc check
    mesh->transform = rcge_transform_create_zero();
    mesh->texture = texture;
    mesh->vao = vao;
    mesh->vbo = vbo;
    mesh->ebo = ebo;
    mesh->vert_no = indices_size;
    printf("[RCGE Mesh] Mesh %d created.\n", vao);
    return mesh;
}

rcge_transform rcge_mesh_transform_get(rcge_mesh mesh)
{
    if (mesh == NULL) {printf("[RCGE Mesh] Mesh transform get failed: mesh does not exist.\n"); return NULL;}
    return mesh->transform;
}

void rcge_mesh_draw(rcge_mesh mesh)
{
    if (mesh == NULL) {printf("[RCGE Mesh] Mesh draw failed: mesh does not exist.\n"); return;}
    rcge_texture_use(mesh->texture);
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->vert_no, GL_UNSIGNED_INT, 0);
}

void rcge_mesh_delete(rcge_mesh mesh)
{
    if (mesh == NULL) {printf("[RCGE Mesh] Mesh delete failed: mesh does not exist.\n"); return;}
    GLuint vao = mesh->vao;
    glDeleteBuffers(1, &(mesh->vbo));
    glDeleteBuffers(1, &(mesh->ebo));
    glDeleteVertexArrays(1, &vao);
    rcge_transform_delete(mesh->transform);
    free(mesh);
    printf("[RCGE Mesh] Mesh %d deleted.\n", vao);
}