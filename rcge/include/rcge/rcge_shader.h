#ifndef RCGE_SHADER_H
#define RCGE_SHADER_H

/** 
 * @file rcge_shader.h
 * @brief Shader management.
 * 
 * @defgroup shaders Shader Components and Shaders
 * @brief Shader management.
 * 
 * This module allows the creating and using of shaders.
 * Shaders are programs run in the GPU that determines how graphics are rendered on screen.
 * They are necessary for all graphics rendering, even for simple unlit meshes.
 * 
 * To initialise a shader, you must:
 * 
 * 1. Create shader (See @ref rcge_shader_create)
 * 2. Attach shader components (See section @ref shaders_comp on what components are)
 * 3. Set outputs (See section @ref shaders_colorout on what outputs are)
 * 4. Compile (See @ref rcge_shader_compile)
 * 5. Set attributes & uniforms (See section @ref shaders_attrib and @ref shaders_uniform on what attributes and uniforms are)
 * 6. Use shader (See @ref rcge_shader_use)
 * 
 * An example has been provided in section @ref shaders_example.
 * <hr>
 * @subsection shaders_comp Shader Components and Pipeline
 * A shader is needed to be consisted of at least 2 components: a vertex, and a fragment component.
 * If you want, you can additionally make use of a geometric component.
 * 
 * Vertex shader component: Processes each vertex to determine its position in 3D space and pass data to the next stage.
 * Geometric Shader Component: Takes whole primitives and can create, modify, or discard geometry before shape assembly.
 * Fragment Shader Component: Calculates the final color and appearance of each pixel on the screen.
 * 
 * When mesh vertices data (i.e. Raw data of a 2D shape/3D model) are passed to the GPU for rendering, it goes through the shader component by component. The pipeline is as follows:
 * 1. Passes data of vertices to vertex component of the shader
 * 2. Passes output of vertex component to geometric component of the shader (optional)
 * 3. Assembles shapes and rasterizes with the output data from the vertex component and the optional geometric component (Automatically done by the engine, no components needed)
 * 4. Passes the shape data resulted to the fragment component of the shader
 * 5. Renders the colors obtained from the shader to the screen
 * 
 * i.e Mesh Vertices Data [Shader Input] --> Vertex Component -> Geometric Component (Opt.) -> Shape Assembly & Rasterisation (Auto.) -> Fragment Shader --> [Shader Output] Graphics Rendered
 * <hr>
 * @subsection shaders_comp_source Shader Component Code (GLSL)
 * In order to create your own shader component, you will need to write **GLSL (OpenGL Shader Language)** source code for it. Then, call @ref rcge_shader_comp_create to load it into the engine.
 * 
 * A brief guide of GLSL *(Credit: Learn OpenGL, by Joey de Vries)*:\n
 * GLSL is tailored for use with graphics and contains useful features specifically targeted at vector and matrix manipulation. Shaders always begin with a version declaration, followed by a list of input and output variables, uniforms and its main function. Each shader's entry point is at its main function where we process any input variables and output the results in its output variables. Don't worry if you don't know what uniforms are, we'll get to those shortly.
 * 
 * A shader typically has the following structure:
 * 
 * @code
 * #version version_number //Usually "150 core"
 * in type in_variable_name;
 * in type in_variable_name;
 * 
 * out type out_variable_name;
 *   
 * uniform type uniform_name;
 *   
 * void main()
 * {
 *   // process input(s) and do some weird graphics stuff
 *   ...
 *   // output processed stuff to output variable
 *   out_variable_name = weird_stuff_we_processed;
 * }
 * @endcode
 * 
 * **For details of implementation of shader and shader component creation, see**:
 * - @ref rcge_shader_comp_create
 * - @ref rcge_shader_comp_delete
 * - @ref rcge_shader_attach
 * - @ref rcge_shader_compile
 * - @ref rcge_shader_use
 * - @ref rcge_shader_delete
 * <hr>
 * @subsection shaders_attrib Shaders Attributes
 * Attributes are the mesh vertices input into the shader. Since the inputs are first passed through the vertex component, attributes can also be defined as the inputs of the shader vertex component.
 * So basically, attributes are to provide per-vertex data like position, normals, texture coordinates, and colors that define the shape and surface of a mesh.
 * Attributes are usually used to input position, and texture UV coordinates data of vertices of a mesh.
 * 
 * Suppose I have a vertex shader component with source code as following:
 * 
 * @code
 * #version 150 core
 * 
 * in vec3 position;
 * in vec2 texcoord;
 * ...
 * 
 * void main()
 * {
 *     ...
 * }
 * @endcode
 * Then the shader with this component would have two attributes: "position" and "texcoord".
 * 
 * This section only explains what an attribute is. To see the details on how to set them up, go to @ref rcge_shader_attrib_set.
 * <hr>
 * @subsection shaders_uniform Shaders Uniforms
 * Uniforms are another type of input of a shader. It is a shader input that is constant for the entire draw call (the same value is used for all vertices and fragments).
 * (Attributes, on the other hand, is an input that changes per vertex.)
 * Uniforms are usually used for global data that affects the whole object being drawn instead of just single vertices, like transformation matrices (model/view/projection), lighting parameters, time values, and texture settings.
 * 
 * Suppose I have a shader component with source code as following:
 * 
 * @code
 * #version 150 core
 * 
 * in vec3 position;
 * ...
 * uniform mat4 model;
 * uniform mat4 view;
 * uniform mat4 proj;
 * 
 * void main()
 * {
 *     ...
 * }
 * @endcode
 * Then the shader with this component would have uniforms "model", "view" and "proj", all of type mat4.
 * 
 * This section only explains what a uniform is. \n
 * To see the details on how to set them up, go to @ref rcge_shader_uniform_loc_set. \n
 * To see the details on how to set values of uniforms, see functions with naming format **rcge_shader_uniform_XXX**.
 * <hr>
 * @subsection shaders_colorout Shaders Output and Color Buffer
 * Shaders will output color values. Since the outputs are returned from the fragment component, they are the same as the outputs of the shader fragment component.
 * 
 * Suppose I have a shader having a fragment component with source code as following:
 * 
 * @code
 * #version 150 core
 * 
 * in vec2 _texcoord;
 * out vec4 outColor;
 * ...
 * void main()
 * {
 *     ...
 * }
 * @endcode
 * The shader has output "outColor".
 * 
 * To see how to setup outputs so that they could actually be rendered, please see @ref rcge_shader_color_out_location
 * <hr>
 * @subsection shaders_example Shader Setup Sample Code
 * 
 * @code
 * rcge_shader_comp vertex_comp = rcge_shader_comp_create("shaders/default.vert", SHADER_VERT);
 * rcge_shader_comp fragment_comp = rcge_shader_comp_create("shaders/default.frag", SHADER_FRAG);
 * shader = rcge_shader_create(2, 5);
 * rcge_shader_attach(shader, vertex_comp);
 * rcge_shader_attach(shader, fragment_comp);
 * rcge_shader_color_out_location(shader, 0, "outColor");
 * rcge_shader_compile(shader);
 * rcge_shader_attrib_set(shader, 0, "position", 3, DATATYPE_FLOAT, false);
 * rcge_shader_attrib_set(shader, 1, "texcoord", 2, DATATYPE_FLOAT, false);
 * rcge_shader_uniform_loc_set(shader, 0, "model");
 * rcge_shader_uniform_loc_set(shader, 1, "view");
 * rcge_shader_uniform_loc_set(shader, 2, "proj");
 * rcge_shader_uniform_loc_set(shader, 3, "color");
 * rcge_shader_uniform_loc_set(shader, 4, "tex");
 * rcge_shader_use(shader); 
 * rcge_shader_comp_delete(vertex_comp);
 * rcge_shader_comp_delete(fragment_comp);
 * @endcode
**/

#include <cglm/cglm.h>
#include <rcge/rcge_datatype.h>
#include <stdbool.h>

/**
 * @ingroup shaders
 * Datatype representing a component of a shader.
**/
typedef struct rcge_shader_comp_CDT* rcge_shader_comp;

/**
 * @ingroup shaders
 * @enum rcge_shader_comp_type
 * @brief Shader component types.
**/
typedef enum 
{
    SHADER_VERT, ///< Vertex shader component
    SHADER_GEOM, ///< Geometric shader component
    SHADER_FRAG ///< Fragment shader component
} rcge_shader_comp_type;

/**
 * @ingroup shaders
 * @brief Creates a shader component from source code file (written in GLSL).
 * @param[in] path Relative path of the shader component source code file to be used for the new component. 
 * @param[in] type The type of the new shader component. See @ref rcge_shader_comp_type.
 * @return The shader component created, NULL if failed.
**/
rcge_shader_comp rcge_shader_comp_create(char* path, rcge_shader_comp_type type);

/**
 * @ingroup shaders
 * @brief Deletes a shader component. 
 * Shader component deletion must be done after it has been attached to a shader AND the shader has compiled. This prevents memory leaks.
 * @param[in] shader_comp The shader component to be deleted.
**/
void rcge_shader_comp_delete(rcge_shader_comp shader_comp);

/**
 * @ingroup shaders
 * Datatype representing a shader.
**/
typedef struct rcge_shader_CDT* rcge_shader;

/**
 * @ingroup shaders
 * @brief Creates a shader. 
 * @param[in] attrib_no Number of attributes that the new shader will have.
 * @param[in] uniform_no Number of uniforms that the new shader will have.
 * @return The shader created, NULL if failed.
**/
rcge_shader rcge_shader_create(unsigned int attrib_no, unsigned int uniform_no);

/**
 * @ingroup shaders
 * @brief Attaches a specified shader component to a specified shader.
 * @note Has to be called after @ref rcge_shader_create and before @ref rcge_shader_compile.
 * @param[in] shader Shader to be attached.
 * @param[in] shader_comp Shader component to attach.
**/
void rcge_shader_attach(rcge_shader shader, rcge_shader_comp shader_comp);

/**
 * @ingroup shaders
 * @brief Compiles the shader. 
 * @note Do not @ref rcge_shader_attach or @ref rcge_shader_color_out_location after running this.
 * @param[in] shader Shader to be compiled.
**/
void rcge_shader_compile(rcge_shader shader);

/**
 * @ingroup shaders
 * @brief Set the shader to be the active one.
 * @param[in] shader Shader to be used.
**/
void rcge_shader_use(rcge_shader shader);

/**
 * @ingroup shaders
 * @brief Initialises a shader attribute, and assigning an index for it.
 * During shader initialisation, you must initialise each shader attributes one by one.
 * This function determines how mesh data is read. If you assign a lower index for an attribute, that attribute would be read first.
 * e.g. if I assign vector3 attribute "a" to index 0, vector2 attribute "b" to index "0", the data {0.0, 1.0, 2.0, 3.0, 4.0} would be read as `a = vec3(0.0, 1.0, 2.0)` and `b = vec2(3.0, 4.0)`.
 * @note Two attributes cannot share the same index. 
 * @note Shader attribute index is SEPERATE from uniform index.
 * @param[in] shader The shader to have it's attribute initialised.
 * @param[in] index The index to assign to for the attribute to be initialised. It must be a non-negative int smaller than the total number of attributes the shader has.
 * @param[in] name The name of the attribute to be initialised set in the source code of the shaders' components.
 * @param[in] size The number of data the attribute to be initialised has. 
 * @param[in] type The datatype of the attribute to be initialised. See @ref rcge_datatype to see what to input here for each datatype.
 * @param[in] normalised Whether you want the attribute to be normalised. 
 * @note Regarding @ref size: Attributes containing either 5 floats, ints or bools have all have size 5. The sizeof datatype does not matter here.
 * @note Regarding @ref normalised: Normalised attribute example -> Passing vec3(128, 128, 128) to a normalised attribute would become vec3(1, 1, 1)
**/
void rcge_shader_attrib_set(rcge_shader shader, unsigned int index, char* name, unsigned int size, rcge_datatype type, bool normalised);

/**
 * @ingroup shaders
 * @brief Initialise a shader uniform, and assigning an index for it.
 * During shader initialisation, you must initialise each shader uniforms one by one.
 * The index can be used later to set values of specified uniforms later on.
 * @note Two uniforms cannot share the same index. 
 * @note Shader uniform index is SEPERATE from attribute index.
 * @param[in] shader The shader to have it's uniform initialised.
 * @param[in] index The index to assign to for the uniform to be initialised. It must be a non-negative int smaller than the total number of uniforms the shader has.
 * @param[in] name The name of the uniform to be initialised set in the source code of the shaders' components.
**/
void rcge_shader_uniform_loc_set(rcge_shader shader, unsigned int index, char* name);

/**
 * @ingroup shaders
 * @brief Set shader output color buffer location.
 * All shader after passing through the fragment component would have color output(s).
 * For the output(s) to be drawn, it (or each of them) has to be assigned to a color buffer location.
 * Only after assigning, can the shader color outputs be sent to a color buffer and rendered. 
 * @note Has to be called after @ref rcge_shader_create and before @ref rcge_shader_compile.
 * @param[in] shader The shader to have it's output color buffer location set.
 * @param[in] color_no The color buffer location to be assigned to the output. 
 * @param[in] name The name of the output set in the source code of the shaders' components.
**/
void rcge_shader_color_out_location(rcge_shader shader, unsigned int color_no, char* name);

/**
 * @ingroup shaders
 * @brief Deletes a shader. 
 * Shader deletion must be done before the program terminates. This prevents memory leaks.
 * @param[in] shader The shader to be deleted.
**/
void rcge_shader_delete(rcge_shader shader);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *float* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_float(rcge_shader shader, unsigned int uniform_loc_index, float value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *vec2* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_vec2(rcge_shader shader, unsigned int uniform_loc_index, vec2 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *vec3* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_vec3(rcge_shader shader, unsigned int uniform_loc_index, vec3 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *vec4* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_vec4(rcge_shader shader, unsigned int uniform_loc_index, vec4 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *int* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_int(rcge_shader shader, unsigned int uniform_loc_index, int value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *ivec2* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_ivec2(rcge_shader shader, unsigned int uniform_loc_index, ivec2 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *ivec3* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_ivec3(rcge_shader shader, unsigned int uniform_loc_index, ivec3 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *ivec4* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_ivec4(rcge_shader shader, unsigned int uniform_loc_index, ivec4 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *uint* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_uint(rcge_shader shader, unsigned int uniform_loc_index, unsigned int value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *mat2* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_mat2(rcge_shader shader, unsigned int uniform_loc_index, mat2 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *mat3* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_mat3(rcge_shader shader, unsigned int uniform_loc_index, mat3 value);

/**
 * @ingroup shaders
 * @brief Sets value of a specified *mat4* uniform of a specified shader.
 * @note Please ensure the target shader is set active before calling this with @ref rcge_shader_use.
 * @param[in] shader The shader to have it's uniform changed.
 * @param[in] uniform_loc_index The index of the uniform to be changed. (Assigned when user call @ref rcge_shader_uniform_loc_set)
 * @param[in] value The value to set to.
**/
void rcge_shader_uniform_mat4(rcge_shader shader, unsigned int uniform_loc_index, mat4 value);

//TODO: More uniform types to be added here!


void rcge_shader_attrib_activate_mesh(rcge_shader shader); //Assumes VAO of mesh is active. //TODO: MOVE THIS TO INTERNAL
#endif