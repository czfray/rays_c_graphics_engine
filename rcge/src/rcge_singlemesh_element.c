#include <rcge/rcge_singlemesh_element.h>
#include <rcge/rcge_mesh.h>
#include <rcge/rcge_element.h>

#include <stdlib.h>

void rcge_singlemesh_update(rcge_element element, double delta_time)
{
    rcge_mesh mesh = rcge_singlemesh_mesh_get(element);
    rcge_mesh_draw(mesh);
}

void rcge_singlemesh_delete(rcge_element element)
{
    rcge_mesh_delete(rcge_singlemesh_mesh_get(element));
}

rcge_element rcge_singlemesh_create(rcge_shader shader, int model_uniform_index, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, rcge_mesh_draw_type draw_type)
{
    rcge_mesh mesh = rcge_mesh_create(shader, model_uniform_index, texture, vertices, vertices_size, indices, indices_size, draw_type);
    rcge_element element = rcge_element_create(1, NULL, NULL, rcge_singlemesh_update, rcge_singlemesh_delete);
    rcge_element_attach(element, 0, mesh);
    rcge_element_start(element);
    return element;
}

unsigned int rcge_singlemesh_create_in_manager(rcge_element_manager manager, rcge_shader shader, int model_uniform_index, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, rcge_mesh_draw_type draw_type)
{
    rcge_element element = rcge_singlemesh_create(shader, model_uniform_index, texture, vertices, vertices_size, indices, indices_size, draw_type);
    return rcge_element_manager_attach(manager, element);
}

rcge_mesh rcge_singlemesh_mesh_get(rcge_element element)
{
    return (rcge_mesh) rcge_element_comp_get(element, 0);
}