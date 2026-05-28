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
rcge_camera camera;

void start(rcge_window window)
{
    int frame = 0;
    time = 0;
    printf("Testing app start!\n");

    rcge_shader_uniform_vec4(shader, 3, GLM_VEC4_ONE); //TODO SET MESH COLOR
}

void update_fps(double delta_time)
{
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

void update(rcge_window window, double delta_time)
{
    rcge_transform transform = rcge_mesh_transform_get(mesh);
    vec3 apply_rot_euler = {0.9f, 1.0f, 1.0f};
    glm_vec3_scale(apply_rot_euler, delta_time, apply_rot_euler);
    rcge_transform_add_rot_euler(transform, apply_rot_euler);

    rcge_mesh_draw(mesh);

    update_fps(delta_time);

    //rcge_camera_fov_size_set(camera, rcge_camera_fov_size_get(camera) + 10 * delta_time);
    vec3 newpos;
    vec3 sub = {0, 0, delta_time};
    rcge_camera_pos_get(camera, newpos);
    glm_vec3_add(newpos, sub, newpos);
    rcge_camera_pos_set(camera, newpos);
}

void resize(rcge_window window, int width, int height)
{
    rcge_camera_ratio_set(camera, rcge_window_ratio(window));
}

int main(void)
{
    rcge_init();
    rcge_window window = rcge_window_create(800, 600, "RCGE Test", true);
    
    rcge_shader_comp vertex_comp = rcge_shader_comp_create("shaders/default.vert", SHADER_VERT);
    rcge_shader_comp fragment_comp = rcge_shader_comp_create("shaders/default.frag", SHADER_FRAG);
    shader = rcge_shader_create(2, 5);
    rcge_shader_attach(shader, vertex_comp);
    rcge_shader_attach(shader, fragment_comp);
    rcge_shader_color_out_location(shader, 0, "outColor");
    rcge_shader_compile(shader);
    rcge_shader_attrib_set(shader, 0, "position", 3, DATATYPE_FLOAT, false);
    rcge_shader_attrib_set(shader, 1, "texcoord", 2, DATATYPE_FLOAT, false);
    rcge_shader_uniform_loc_set(shader, 0, "model");
    rcge_shader_uniform_loc_set(shader, 1, "view");
    rcge_shader_uniform_loc_set(shader, 2, "proj");
    rcge_shader_uniform_loc_set(shader, 3, "color");
    rcge_shader_uniform_loc_set(shader, 4, "tex");
    rcge_shader_use(shader);

    rcge_shader_comp_delete(vertex_comp);
    rcge_shader_comp_delete(fragment_comp);
    
    camera = rcge_camera_create(shader, 1, 2, true, 45.0f, 0.001f, 100.0f, rcge_window_ratio(window));
    //camera = rcge_camera_create(shader, 1, 2, false, 2.0f, 1.0f, 100.0f, rcge_window_ratio(window));
    vec3 cam_pos = {0.0f, 0.0f, 5.0f};
    rcge_camera_pos_set(camera, cam_pos);

    rcge_texture texture = rcge_texture_create("textures/keven.png", TEX_CLAMP_TO_EDGE, TEX_LINEAR);
    rcge_texture_use(texture);
    rcge_shader_uniform_int(shader, 4, 0); //OPTIONAL, default is 0 already, only need if multiple texture layer.

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

    mesh = rcge_mesh_create(shader, 0, texture, vertices, 120, indices, 36, MESH_STATIC);

    rcge_window_run(window, start, update, resize);
    
    rcge_mesh_delete(mesh);
    rcge_texture_delete(texture);
    rcge_camera_delete(camera);
    rcge_shader_delete(shader);
    rcge_terminate();
    return 0;
}