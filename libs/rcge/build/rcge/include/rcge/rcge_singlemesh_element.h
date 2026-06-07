#ifndef RCGE_SINGLEMESH_H
#define RCGE_SINGLEMESH_H

/** 
 * @file rcge_singlemesh_element.h
 * @brief Single mesh element
 * 
 * @defgroup singlemesh Single Mesh Element
 * 
 * This module is a prebuilt element with a single mesh component inside it.
**/
#include <rcge/rcge_mesh.h>
#include <rcge/rcge_element.h>

/**
 * @ingroup singlemesh
 * @brief Creates a single mesh element (an element with a single mesh component inside it), then attach the newly created element to a specified manager.
 * @param[in] manager Element manager the newly created element to be attached to.
 * @param[in] shader Shader the mesh component uses. 
 * @param[in] texture The texture of the mesh component.
 * @param[in] vertices The vertex data array for the mesh component.
 * @param[in] vertices_size The array size (number of floats) of `vertices`.
 * @param[in] indices The index data array for the mesh component.
 * @param[in] indices_size The array size (number of integers) of `indices`.
 * @param[in] color The color you want to multiply to the mesh component.
 * @param[in] draw_type Draw frequency type of the mesh component. See @ref rcge_mesh_draw_type to see which one to choose.
 * @param[out] index The index of the element created in the manager. NULL if not needed.
 * @return The element created, NULL if failed.
 * @note Ensure the intended shader is currently active before creating the mesh by using @ref rcge_shader_use.
**/
rcge_element rcge_singlemesh_create_in_manager(rcge_element_manager manager, rcge_shader shader, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, vec4 color, rcge_mesh_draw_type draw_type, unsigned int* index);

/**
 * @ingroup singlemesh
 * @brief Creates a single mesh element (an element with a single mesh component inside it).
 * @param[in] shader Shader the mesh component uses. 
 * @param[in] texture The texture of the mesh component.
 * @param[in] vertices The vertex data array for the mesh component.
 * @param[in] vertices_size The array size (number of floats) of `vertices`.
 * @param[in] indices The index data array for the mesh component.
 * @param[in] indices_size The array size (number of integers) of `indices`.
 * @param[in] color The color you want to multiply to the mesh component.
 * @param[in] draw_type Draw frequency type of the mesh component. See @ref rcge_mesh_draw_type to see which one to choose.
 * @return The element created, NULL if failed.
 * @note Ensure the intended shader is currently active before creating the mesh by using @ref rcge_shader_use.
**/
rcge_element rcge_singlemesh_create(rcge_shader shader, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, vec4 color, rcge_mesh_draw_type draw_type);

/**
 * @ingroup singlemesh
 * @brief Get the mesh component within a single mesh element.
 * @return The mesh component within the specified single mesh element, NULL if failed.
**/
rcge_mesh rcge_singlemesh_mesh_get(rcge_element element);

/**
 * @ingroup singlemesh
 * @brief Get the transform of the mesh component within a single mesh element.
 * @return The transform required, NULL if failed.
**/
rcge_transform rcge_singlemesh_transform_get(rcge_element element);

#endif