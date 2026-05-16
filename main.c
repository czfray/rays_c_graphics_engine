#include <rcge/rcge.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 *
 * Ray's C Graphics Engine (RCGE)
 * A OpenGL-based graphic engine written in plain C.
 * 
 * Author: Chan Ray
 * Start Date: May 10th, 2026
 * 
 */

int frame;
double time;
rcge_shader shader;
rcge_mesh mesh;

mat4 model;
mat4 proj;
mat4 view;

int model_loc;
int proj_loc;
int view_loc;

void start(rcge_window window)
{
    int frame = 0;
    time = 0;
    printf("Testing app start!\n");

    glm_mat4_identity(model);
    glm_mat4_identity(proj);
    glm_mat4_identity(view);

    model_loc = rcge_shader_uniform_loc_get(shader, "model");
    proj_loc = rcge_shader_uniform_loc_get(shader, "proj");
    view_loc = rcge_shader_uniform_loc_get(shader, "view");
    
    vec3 cam = {0.0f, 0.0f, 3.0f};
    vec3 target = {0.0f, 0.0f, 0.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    glm_lookat(cam, target, up, view);

    glm_perspective(glm_rad(45.0f), rcge_window_ratio(window), 1.0f, 10.0f, proj);
    
    rcge_shader_uniform_mat4(model_loc, model);
    rcge_shader_uniform_mat4(proj_loc, proj);
    rcge_shader_uniform_mat4(view_loc, view);
    rcge_shader_uniform_vec4(rcge_shader_uniform_loc_get(shader, "color"), GLM_VEC4_ONE);
}

void update(rcge_window window, double delta_time)
{
    glm_perspective(glm_rad(45.0f), rcge_window_ratio(window), 1.0f, 10.0f, proj);
    rcge_shader_uniform_mat4(proj_loc, proj);
    
    rcge_transform transform = rcge_mesh_transform_get(mesh);
    versor cur_rot;
    rcge_transform_rot_get(transform, cur_rot);
    versor apply_rot;
    vec3 apply_rot_euler = {0.1f, 0.5f, 0.1f};
    glm_vec3_scale(apply_rot_euler, delta_time, apply_rot_euler);
    glm_euler_xyz_quat(apply_rot_euler, apply_rot);
    glm_quat_mul(apply_rot, cur_rot, cur_rot);
    rcge_transform_rot_set(transform, cur_rot);

    rcge_transform_model_get(rcge_mesh_transform_get(mesh), model);
    rcge_shader_uniform_mat4(model_loc, model);

    rcge_mesh_draw(mesh);

    frame++;
    time += delta_time;
    if (time > 1.0)
    {
        int fps = (int) (frame / time);
        printf("Testing app update: %d FPS\n", fps);
        frame = 0;
        time = time - (int) (time);
    }
}

int main(void)
{
    rcge_init();
    rcge_window window = rcge_window_create(800, 600, "RCGE Test", true);
    
    rcge_shader_comp vertex_comp = rcge_shader_comp_create("shaders/default.vert", SHADER_VERT);
    rcge_shader_comp fragment_comp = rcge_shader_comp_create("shaders/default.frag", SHADER_FRAG);
    shader = rcge_shader_create(2);
    rcge_shader_attach(shader, vertex_comp);
    rcge_shader_attach(shader, fragment_comp);
    rcge_shader_color_out_location(shader, 0, "outColor");
    rcge_shader_compile(shader);
    rcge_shader_attrib_set(shader, 0, "position", 3, DATATYPE_FLOAT, false);
    rcge_shader_attrib_set(shader, 1, "texcoord", 2, DATATYPE_FLOAT, false);
    rcge_shader_use(shader);

    rcge_shader_comp_delete(vertex_comp);
    rcge_shader_comp_delete(fragment_comp);
    
    rcge_texture texture = rcge_texture_create("textures/keven.png", TEX_CLAMP_TO_EDGE, TEX_LINEAR);
    rcge_texture_use(texture);
    rcge_shader_uniform_int(rcge_shader_uniform_loc_get(shader, "tex"), 0); //OPTIONAL, default is 0 already, only need if multiple texture layer.

    float vertices[] =
    {
        -0.5, -0.5, -0.5,   1.0, 1.0,
        -0.5, 0.5, -0.5,    1.0, 0,
        0.5, 0.5, -0.5,     0, 0,
        0.5, -0.5, -0.5,    0, 1.0, 

        -0.5, -0.5, 0.5,    1.0, 1.0,
        -0.5, 0.5, 0.5,     1.0, 0,
        -0.5, 0.5, -0.5,    0, 0,
        -0.5, -0.5, -0.5,   0, 1.0, 

        0.5, -0.5, 0.5,     1.0, 1.0,
        0.5, 0.5, 0.5,      1.0, 0,
        -0.5, 0.5, 0.5,     0, 0,
        -0.5, -0.5, 0.5,    0, 1.0, 

        0.5, -0.5, -0.5,    1.0, 1.0,
        0.5, 0.5, -0.5,     1.0, 0,
        0.5, 0.5, 0.5,      0, 0,
        0.5, -0.5, 0.5,     0, 1.0, 

        -0.5, 0.5, -0.5,    1.0, 1.0,
        -0.5, 0.5, 0.5,     1.0, 0,
        0.5, 0.5, 0.5,      0, 0,
        0.5, 0.5, -0.5,     0, 1.0, 

        -0.5, -0.5, 0.5,    1.0, 1.0,
        -0.5, -0.5, -0.5,   1.0, 0,
        0.5, -0.5, -0.5,    0, 0,
        0.5, -0.5, 0.5,     0, 1.0, 
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    mesh = rcge_mesh_create(shader, texture, vertices, 120, indices, 36, MESH_STATIC);

    rcge_window_run(window, start, update);
    
    rcge_mesh_delete(mesh);
    rcge_texture_delete(texture);
    rcge_shader_delete(shader);
    rcge_terminate();
    return 0;
}