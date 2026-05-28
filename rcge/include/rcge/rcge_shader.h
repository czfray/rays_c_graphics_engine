#ifndef RCGE_SHADER_H
#define RCGE_SHADER_H

#include <cglm/cglm.h>
#include <rcge/rcge_datatype.h>
#include <stdbool.h>

typedef struct rcge_shader_comp_CDT* rcge_shader_comp;
typedef struct rcge_shader_CDT* rcge_shader;
typedef enum {SHADER_VERT, SHADER_FRAG, SHADER_GEOM} rcge_shader_comp_type;

rcge_shader_comp rcge_shader_comp_create(char* path, rcge_shader_comp_type type);
void rcge_shader_comp_delete(rcge_shader_comp shader_comp);

rcge_shader rcge_shader_create(unsigned int attrib_no, unsigned int uniform_no);
void rcge_shader_attach(rcge_shader shader, rcge_shader_comp shader_comp);
void rcge_shader_compile(rcge_shader shader);
void rcge_shader_use(rcge_shader shader);
void rcge_shader_attrib_set(rcge_shader shader, unsigned int index, char* name, unsigned int size, rcge_datatype type, bool normalised);
void rcge_shader_attrib_activate_mesh(rcge_shader shader); //Assumes VAO of mesh is active.
void rcge_shader_uniform_loc_set(rcge_shader shader, unsigned int index, char* name);
void rcge_shader_delete(rcge_shader shader);

void rcge_shader_color_out_location(rcge_shader shader, unsigned int color_no, char* loc_name);

void rcge_shader_uniform_float(rcge_shader shader, unsigned int uniform_loc_index, float value); //Assume shader is active
void rcge_shader_uniform_vec2(rcge_shader shader, unsigned int uniform_loc_index, vec2 value);
void rcge_shader_uniform_vec3(rcge_shader shader, unsigned int uniform_loc_index, vec3 value);
void rcge_shader_uniform_vec4(rcge_shader shader, unsigned int uniform_loc_index, vec4 value);
void rcge_shader_uniform_int(rcge_shader shader, unsigned int uniform_loc_index, int value);
void rcge_shader_uniform_ivec2(rcge_shader shader, unsigned int uniform_loc_index, ivec2 value);
void rcge_shader_uniform_ivec3(rcge_shader shader, unsigned int uniform_loc_index, ivec3 value);
void rcge_shader_uniform_ivec4(rcge_shader shader, unsigned int uniform_loc_index, ivec4 value);
void rcge_shader_uniform_uint(rcge_shader shader, unsigned int uniform_loc_index, unsigned int value);
void rcge_shader_uniform_mat2(rcge_shader shader, unsigned int uniform_loc_index, mat2 value);
void rcge_shader_uniform_mat3(rcge_shader shader, unsigned int uniform_loc_index, mat3 value);
void rcge_shader_uniform_mat4(rcge_shader shader, unsigned int uniform_loc_index, mat4 value);

#endif