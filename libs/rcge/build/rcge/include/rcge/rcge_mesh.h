#ifndef RCGE_MESH_H
#define RCGE_MESH_H

/** 
 * @file rcge_mesh.h
 * @brief Mesh management.
 * 
 * @defgroup meshes Meshes
 * 
 * This module allows the drawing of meshes. It manages how the mesh data is sent to the GPU, and allows the mesh to be drawn.
 * 
 * A mesh is a 2D/3D graphical objects, and is represented by a vertex data array and an Index Data Array.
 * This module can be considered an element component. See @ref elements to know what it means.
 * 
 * @subsection meshes_vertex Vertex Data Array
 * @ingroup meshes
 * The vertex data array stores all the vertices (points) of an object.
 * Each vertex represents a point in 2D or 3D space and can include multiple attributes, such as:
 * - Position (e.g., x, y, z coordinates)
 * - Color
 * - Normal vector (used for lighting)
 * - Texture coordinates (UV)
 * 
 * How a vertex data array is read and interpreted depends on how attributes are set up in the shader the mesh is using. See section @ref shaders_attrib.
 * 
 * Suppose I have a vertex data array below:
 * @code
 * float[] vertices = 
 * {
 *     -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
 *     0, 0.5f, 0.0, 0.5f, 1.0f,
 *     0.5f, 0.0, 0.0, 1.0f, 0.0f,
 * }
 * @endcode
 * and shader attributes are set like this:
 * @code
 * rcge_shader_attrib_set(shader, 0, "position", 3, DATATYPE_FLOAT, false);
 * rcge_shader_attrib_set(shader, 1, "texcoord", 2, DATATYPE_FLOAT, false);
 * @endcode
 * Then each vertex will be represented by 3+2=5 floating point number. For my example, the array `vertices` represents 3 vertices: 
 * 1. A vertex with "position" (-0.5, 0, 0) with "texcoord" (0, 0)
 * 2. A vertex with "position" (0, 0.5, 0) with "texcoord" (0.5, 1)
 * 3. A vertex with "position" (0.5, 0, 0) with "texcoord" (1, 0)
 * 
 * A vertex data array only represent vertices, but not shapes. 
 * 
 * @subsection meshes_indices Index Data Array
 * @ingroup meshes
 * To represent a shape, we need an addition integer array, called an index data array, on top of the vertex data array.
 * 
 * Lets take the following vertex data array:
 * @code
 * float[] vertices = 
 * {
 *     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //Index 0
 *     -0.5, 0.5f, 0.0f, 0.0f, 1.0f, //Index 1
 *     0.5f, 0.5f, 0.0f, 1.0f, 1.0f, //Index 2
 *     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //Index 3
 * }
 * @endcode
 * The array `vertices` represents 4 vertices. Each vertices will have an index, the first vertex has index 0, second has index 1, etc. 
 * If we want to represent a square with these 4 vertices, we need to make use of the 4 vertex indices.
 * 
 * @note RCGE draws triangles, and cannot directly draw a square. 
 * 
 * To use the above 4 vertices to draw a square, we need to draw two triangles:
 * - Triangle 1 has vertices of index 0, 1, 2
 * - Triangle 2 has vertices of index 2, 3, 0
 * 
 * Meaning that a square shape can be represented with the following array:
 * @code
 * unsigned int[] indices =
 * {
 *     0, 1, 2,
 *     2, 3, 0
 * }
 * @endcode
 * This array represents a square, and tells the engine to draw two triangles:
 * - 1st triangle, drawing from vertex 0, to vertex 1, to vertex 2, and then back to vertex 0
 * - 2nd triangle, drawing from vertex 2, to vertex 3, to vertex 0, and then back to vertex 2
 * 
 * The above order of vertices is clockwise. You can also draw the square with anti-clockwise order:
 * @code
 * unsigned int[] indices =
 * {
 *     2, 1, 0
 *     0, 3, 2
 * }
 * @endcode
 * But a clockwise order is recommended, since if backface culling is enabled, only clockwise ordered will be regarded as front-facing, and only front-facing shapes are rendered.
 * 
 * To see the specific implementation of mesh creation with a vertices and an index data array, go to @ref rcge_mesh_create. 
 * To draw a mesh, you need to run @ref rcge_mesh_draw every frame.
**/

#include <rcge/rcge_shader.h>
#include <rcge/rcge_transform.h>
#include <rcge/rcge_texture.h>
#include <cglm/cglm.h>

/**
 * @ingroup meshes
 * Datatype representing a mesh. Can be used as an element component. See @ref elements.
**/
typedef struct rcge_mesh_CDT* rcge_mesh;

/**
 * @ingroup meshes
 * @brief Draw frequency type of a mesh.
**/
typedef enum
{
    MESH_STATIC, ///< Static, mesh data is set only once, used many times.
    MESH_DYNAMIC, ///< Dynamic, mesh data is set only once, used at most few times.
    MESH_STREAM ///< Stream, mesh data is changed a lot, used many times.
} rcge_mesh_draw_type;

/**
 * @ingroup meshes
 * @brief Creates a mesh.
 * @param[in] shader Shader the mesh to be created uses. 
 * @param[in] texture The texture of the mesh to be created.
 * @param[in] vertices The vertex data array for the mesh to be created.
 * @param[in] vertices_size The array size (number of floats) of `vertices`.
 * @param[in] indices The index data array for the mesh to be created.
 * @param[in] indices_size The array size (number of integers) of `indices`.
 * @param[in] color The color you want to multiply to the mesh to be created.
 * @param[in] draw_type Draw frequency type of the mesh to be created. See @ref rcge_mesh_draw_type to see which one to choose.
 * @return The mesh created, NULL if failed.
 * @note Ensure the intended shader is currently active before creating the mesh by using @ref rcge_shader_use.
**/
rcge_mesh rcge_mesh_create(rcge_shader shader, rcge_texture texture, float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, vec4 color, rcge_mesh_draw_type draw_type);

/**
 * @ingroup meshes
 * @brief Get the transform of a specified mesh. 
 * @param[in] mesh The mesh to access.
 * @return The transform of the specified mesh, NULL if failed.
**/
rcge_transform rcge_mesh_transform_get(rcge_mesh mesh);

/**
 * @ingroup meshes
 * @brief Set a color for a specific mesh.
 * @param[in] mesh The mesh to access.
 * @param[in] color The color to set to.
**/
void rcge_mesh_color_set(rcge_mesh mesh, vec4 color);

/**
 * @ingroup meshes
 * @brief Draw the specified mesh for a frame.
 * @param[in] mesh The mesh to draw.
 * @note Ensure the shader of the mesh is currently active before drawing by using @ref rcge_shader_use.
**/
void rcge_mesh_draw(rcge_mesh mesh);

/**
 * @ingroup meshes
 * @brief Deltes the mesh.
 * 
 * Mesh deletion needs to be done before the program terminates. Prevent memory leaks.
 * 
 * @param[in] mesh The mesh to delete.
**/
void rcge_mesh_delete(rcge_mesh mesh);  

#endif