#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <rcge/rcge_datatype.h>
#include <rcge/internal/rcge_datatype_internal.h>
#include <rcge/rcge_shader.h>
#include <rcge/rcge_io.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFERSIZE 512

struct rcge_shader_comp_CDT
{
    GLuint gl_shader;
};

typedef struct
{
    bool valid;
    bool normalised;
    rcge_datatype type;
    unsigned int size;
    GLint pos;
} rcge_shader_attrib;

struct rcge_shader_CDT
{
    rcge_shader_attrib* attribs;
    GLuint gl_shader_program;
    unsigned int attrib_no;
};

GLenum gl_shader_type(rcge_shader_comp_type type) {return (type == SHADER_VERT? GL_VERTEX_SHADER: (type == SHADER_GEOM? GL_GEOMETRY_SHADER: GL_FRAGMENT_SHADER));}

rcge_shader_comp rcge_shader_comp_create(char* path, rcge_shader_comp_type type)
{
    char* source = read_file_all(path, BUFFERSIZE);
    if (!source) {printf("[RCGE SHADER] Shader component failed to be created: file reading failure at \"%s\".\n", path); return NULL;}
    
    const char* source_const = source;
    GLuint gl_shader = glCreateShader(gl_shader_type(type));
    glShaderSource(gl_shader, 1, &source_const, NULL);
    glCompileShader(gl_shader);
    free(source);

    GLint compile_status;
    glGetShaderiv(gl_shader, GL_COMPILE_STATUS, &compile_status);
    
    char compile_log[BUFFERSIZE];
    glGetShaderInfoLog(gl_shader, BUFFERSIZE, NULL, compile_log);
    if (strlen(compile_log) > 0) printf("[RCGE SHADER] Shader component %d compilation log => %s", gl_shader, compile_log);

    if (compile_status == GL_FALSE) {printf("[RCGE SHADER] Shader component %d failed to be created: compilation failed.\n", gl_shader); return NULL;}

    rcge_shader_comp shader_comp = malloc(sizeof(*shader_comp));
    shader_comp->gl_shader = gl_shader;

    printf("[RCGE SHADER] Shader component %d created. (%s)\n", gl_shader, path);
    return shader_comp;
}

void rcge_shader_comp_delete(rcge_shader_comp shader_comp)
{
    if (shader_comp == NULL) {printf("[RCGE SHADER] Shader component delete failed: shader component does not exist.\n"); return;}

    GLuint gl_shader = shader_comp->gl_shader;
    glDeleteShader(gl_shader);
    free(shader_comp);
    printf("[RCGE SHADER] Shader component %d deleted.\n", gl_shader);
}

rcge_shader rcge_shader_create(unsigned int attrib_no)
{
    //TODO: TEST MALLOC AND ATTRIB SIZE
    GLuint gl_shader_program = glCreateProgram();
    rcge_shader shader = malloc(sizeof(*shader));
    shader->gl_shader_program = gl_shader_program;

    rcge_shader_attrib* attribs = malloc(attrib_no * sizeof(rcge_shader_attrib));
    shader->attribs = attribs;
    shader->attrib_no = attrib_no;
    for (int i = 0; i < attrib_no; i++) {(shader->attribs)[i].valid = false;}

    printf("[RCGE SHADER] Shader %d created with %d attributes.\n", gl_shader_program, attrib_no);
    return shader;
}

void rcge_shader_attach(rcge_shader shader, rcge_shader_comp shader_comp)
{
    if (shader_comp == NULL) {printf("[RCGE SHADER] Shader attach failed: shader component does not exist.\n"); return;}
    if (shader == NULL) {printf("[RCGE SHADER] Shader attach failed: shader does not exist.\n"); return;}

    GLuint gl_shader_program = shader->gl_shader_program;
    GLuint gl_shader = shader_comp->gl_shader;
    glAttachShader(gl_shader_program, gl_shader);
    printf("[RCGE SHADER] Shader component %d attached to shader %d.\n", gl_shader, gl_shader_program);
}

void rcge_shader_attrib_set(rcge_shader shader, unsigned int index, char* name, unsigned int size, rcge_datatype type, bool normalised)
{
    if (shader == NULL) {printf("[RCGE SHADER] Shader attrib set failed: shader does not exist.\n"); return;}

    GLuint gl_shader_program = shader->gl_shader_program;
    GLint gl_attrib_pos = glGetAttribLocation(gl_shader_program, name);
    rcge_shader_attrib attrib = {true, normalised, type, size, gl_attrib_pos};
    (shader->attribs)[index] = attrib; //TODO: CHECK IF INDEX OUT OF RANGE
    printf("[RCGE SHADER] Shader %d added attrib \"%s\".\n", gl_shader_program, name);
}

void rcge_shader_attrib_activate_mesh(rcge_shader shader)
{
    if (shader == NULL) {printf("[RCGE SHADER] Shader attrib activate in mesh failed: shader does not exist.\n"); return;}

    int attrib_no = shader->attrib_no;
    rcge_shader_attrib* attrib_array = shader->attribs;

    unsigned int stride = 0; 
    for (int i = 0; i < attrib_no; i++) 
    {
        rcge_shader_attrib attrib = attrib_array[i];
        if (!attrib.valid) {printf("[RCGE SHADER] Shader %d attrib activate in mesh failed: attrib %d not set.\n", shader->gl_shader_program, i); return;}
        stride += attrib.size;
    }

    unsigned int pointer = 0;

    for (int i = 0; i < attrib_no; i++)
    {
        rcge_shader_attrib attrib = attrib_array[i];
        GLboolean normalised = attrib.normalised? GL_TRUE: GL_FALSE;
        GLint type = (GLint) rcge_datatype_to_gl(attrib.type);
        unsigned int type_size = rcge_datatype_size(attrib.type);
        glVertexAttribPointer(attrib.pos, attrib.size, type, normalised, stride * type_size, (void*)(uintptr_t)(pointer * type_size));
        glEnableVertexAttribArray(attrib.pos);

        pointer += attrib.size;
    }
    
}

void rcge_shader_compile(rcge_shader shader)
{
    if (shader == NULL) {printf("[RCGE SHADER] Shader compile failed: shader does not exist.\n"); return;}

    GLuint gl_shader_program = shader->gl_shader_program;
    glLinkProgram(gl_shader_program);
    
    GLint compile_status;
    glGetProgramiv(gl_shader_program, GL_LINK_STATUS, &compile_status);
    
    char compile_log[BUFFERSIZE];
    glGetProgramInfoLog(gl_shader_program, BUFFERSIZE, NULL, compile_log);

    if (strlen(compile_log) > 0) printf("[RCGE SHADER] Shader %d compile log => %s", gl_shader_program, compile_log);
    if (compile_status == GL_FALSE) printf("[RCGE SHADER] Shader %d compile failed: linking error.\n", gl_shader_program);
    else printf("[RCGE SHADER] Shader %d compiled.\n", gl_shader_program);
}

void rcge_shader_use(rcge_shader shader)
{
    if (shader == NULL) {printf("[RCGE SHADER] Shader use failed: shader does not exist.\n"); return;}

    GLuint gl_shader_program = shader->gl_shader_program;
    glUseProgram(gl_shader_program);
    printf("[RCGE SHADER] Shader %d now using.\n", gl_shader_program);
}

void rcge_shader_delete(rcge_shader shader)
{
    if (shader == NULL) {printf("[RCGE SHADER] Shader delete failed: shader does not exist.\n"); return;}
    free(shader->attribs);
    GLuint gl_shader_program = shader->gl_shader_program;
    glDeleteProgram(gl_shader_program);
    free(shader);
    printf("[RCGE SHADER] Shader %d deleted.\n", gl_shader_program);
}

void rcge_shader_color_out_location(rcge_shader shader, unsigned int color_no, char* loc_name)
{
    if (shader == NULL) {printf("[RCGE SHADER] Shader set color out location failed: shader does not exist.\n"); return;}
    GLuint gl_shader_program = shader->gl_shader_program;
    glBindFragDataLocation(gl_shader_program, color_no, loc_name);
    printf("[RCGE SHADER] Shader %d set color out location of %d to \"%s\".\n", gl_shader_program, color_no, loc_name);
}

unsigned int rcge_shader_uniform_loc_get(rcge_shader shader, char* name)
{
    if (shader == NULL) {printf("[RCGE SHADER] Shader uniform loc get failed: shader does not exist.\n"); return 999999;}
    return glGetUniformLocation(shader->gl_shader_program, name); 
}

void rcge_shader_uniform_float(unsigned int location, float value){glUniform1f(location, value);}
void rcge_shader_uniform_vec2(unsigned int location, vec2 value) {glUniform2f(location, value[0], value[1]);}
void rcge_shader_uniform_vec3(unsigned int location, vec3 value) {glUniform3f(location, value[0], value[1], value[2]);}
void rcge_shader_uniform_vec4(unsigned int location, vec4 value) {glUniform4f(location, value[0], value[1], value[2], value[3]);}
void rcge_shader_uniform_int(unsigned int location, int value) {glUniform1i(location, value);}
void rcge_shader_uniform_ivec2(unsigned int location, ivec2 value) {glUniform2i(location, value[0], value[1]);}
void rcge_shader_uniform_ivec3(unsigned int location, ivec3 value) {glUniform3i(location, value[0], value[1], value[2]);}
void rcge_shader_uniform_ivec4(unsigned int location, ivec4 value) {glUniform4i(location, value[0], value[1], value[2], value[3]);}
void rcge_shader_uniform_uint(unsigned int location, unsigned int value) {glUniform1ui(location, value);}
void rcge_shader_uniform_mat2(unsigned int location, mat2 value) {glUniformMatrix2fv(location, 1, GL_FALSE, (float*) value);}
void rcge_shader_uniform_mat3(unsigned int location, mat3 value) {glUniformMatrix3fv(location, 1, GL_FALSE, (float*) value);}
void rcge_shader_uniform_mat4(unsigned int location, mat4 value) {glUniformMatrix4fv(location, 1, GL_FALSE, (float*) value);}

//TODO: NOT ALL UNIFORM ADDED: no uvecs and arrays