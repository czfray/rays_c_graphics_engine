#ifndef RCGE_SINGLEMESH_H
#define RCGE_SINGLEMESH_H

#include <rcge/rcge_mesh.h>
#include <rcge/rcge_element.h>

unsigned int rcge_singlemesh_create_in_manager(rcge_element_manager manager, rcge_shader shader, int model_uniform_index, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, rcge_mesh_draw_type draw_type);
rcge_element rcge_singlemesh_create(rcge_shader shader, int model_uniform_index, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, rcge_mesh_draw_type draw_type);
rcge_mesh rcge_singlemesh_mesh_get(rcge_element element);
#endif