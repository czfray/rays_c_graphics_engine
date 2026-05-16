#ifndef RCGE_MESH_H
#define RCGE_MESH_H

#include <rcge/rcge_shader.h>
#include <rcge/rcge_transform.h>
#include <rcge/rcge_texture.h>

typedef struct rcge_mesh_CDT* rcge_mesh;
typedef enum {MESH_STATIC, MESH_DYNAMIC, MESH_STREAM} rcge_mesh_draw_type;

rcge_mesh rcge_mesh_create(rcge_shader shader, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, rcge_mesh_draw_type draw_type);
rcge_transform rcge_mesh_transform_get(rcge_mesh mesh);
void rcge_mesh_draw(rcge_mesh mesh);
void rcge_mesh_delete(rcge_mesh mesh);

#endif