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

double lastX;
double lastY;

rcge_shader shader;
rcge_mesh mesh;
rcge_camera camera;

void start(rcge_window window)
{
    int frame = 0;
    time = 0;
    printf("Testing app start!\n");

    rcge_shader_uniform_vec4(shader, 3, GLM_VEC4_ONE); //TODO SET MESH COLOR
    rcge_io_mouse_loc(window, &lastX, &lastY);
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
    if (rcge_io_input_pressed(window, IO_KEY_ESCAPE)) rcge_window_stop(window);
    
    rcge_transform transform = rcge_mesh_transform_get(mesh);

    vec3 x_axis = {1, 0, 0};
    vec3 y_axis = {0, 1, 0};
    vec3 z_axis = {0, 0, 1};

    vec3 nx_axis = {-1, 0, 0};
    vec3 ny_axis = {0, -1, 0};
    vec3 nz_axis = {0, 0, -1};

    //cube scale
    vec3 apply_scl = GLM_VEC3_ZERO_INIT;
    if (rcge_io_input_pressed(window, IO_MOUSE_LEFT)) glm_vec3_sub(apply_scl, GLM_VEC3_ONE, apply_scl); 
    if (rcge_io_input_pressed(window, IO_MOUSE_RIGHT)) glm_vec3_add(apply_scl, GLM_VEC3_ONE, apply_scl); 
    glm_vec3_scale(apply_scl, 3 * delta_time, apply_scl);

    vec3 new_scl;
    rcge_transform_scl_get(transform, new_scl);
    glm_vec3_add(new_scl, apply_scl, new_scl);
    rcge_transform_scl_set(transform, new_scl);

    //cube pos
    vec3 apply_pos = GLM_VEC3_ZERO_INIT;
    if (rcge_io_input_pressed(window, IO_KEY_LEFT)) glm_vec3_add(apply_pos, x_axis, apply_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_RIGHT)) glm_vec3_add(apply_pos, nx_axis, apply_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_PAGE_UP)) glm_vec3_add(apply_pos, y_axis, apply_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_PAGE_DOWN)) glm_vec3_add(apply_pos, ny_axis, apply_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_UP)) glm_vec3_add(apply_pos, z_axis, apply_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_DOWN)) glm_vec3_add(apply_pos, nz_axis, apply_pos); 
    glm_vec3_norm(apply_pos);
    glm_vec3_scale(apply_pos, 3 * delta_time, apply_pos);

    vec3 new_pos;
    rcge_transform_pos_get(transform, new_pos);
    glm_vec3_add(apply_pos, new_pos, new_pos);
    rcge_transform_pos_set(transform, new_pos);

    //cube rot
    vec3 apply_rot_euler = GLM_VEC3_ZERO_INIT;
    if (rcge_io_input_pressed(window, IO_KEY_KP_8)) glm_vec3_add(apply_rot_euler, x_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(window, IO_KEY_KP_5)) glm_vec3_add(apply_rot_euler, nx_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(window, IO_KEY_KP_6)) glm_vec3_add(apply_rot_euler, y_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(window, IO_KEY_KP_4)) glm_vec3_add(apply_rot_euler, ny_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(window, IO_KEY_KP_9)) glm_vec3_add(apply_rot_euler, z_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(window, IO_KEY_KP_7)) glm_vec3_add(apply_rot_euler, nz_axis, apply_rot_euler); 

    glm_vec3_norm(apply_rot_euler);
    glm_vec3_scale(apply_rot_euler, 5 * delta_time, apply_rot_euler);
    rcge_transform_add_rot_euler(transform, apply_rot_euler);

    //player pos
    vec3 apply_player_pos = GLM_VEC3_ZERO_INIT;
    vec3 cam_left, cam_forward, cam_backward, cam_right, cam_up;
    rcge_camera_forward(camera, cam_forward);
    rcge_camera_left(camera, cam_left);
    rcge_camera_backward(camera, cam_backward);
    rcge_camera_right(camera, cam_right);
    cam_forward[1] = 0;
    glm_vec3_normalize(cam_forward);
    cam_left[1] = 0;
    glm_vec3_normalize(cam_left);
    cam_backward[1] = 0;
    glm_vec3_normalize(cam_backward);
    cam_right[1] = 0;
    glm_vec3_normalize(cam_right);

    if (rcge_io_input_pressed(window, IO_KEY_A)) glm_vec3_add(apply_player_pos, cam_left, apply_player_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_D)) glm_vec3_add(apply_player_pos, cam_right, apply_player_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_W)) glm_vec3_add(apply_player_pos, cam_forward, apply_player_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_S)) glm_vec3_add(apply_player_pos, cam_backward, apply_player_pos);

    if (rcge_io_input_pressed(window, IO_KEY_SPACE)) glm_vec3_add(apply_player_pos, y_axis, apply_player_pos); 
    if (rcge_io_input_pressed(window, IO_KEY_LEFT_SHIFT)) glm_vec3_add(apply_player_pos, ny_axis, apply_player_pos);        
    glm_vec3_norm(apply_player_pos);
    glm_vec3_scale(apply_player_pos, 5 * delta_time, apply_player_pos);

    rcge_camera_pos_get(camera, new_pos);
    glm_vec3_add(apply_player_pos, new_pos, new_pos);
    rcge_camera_pos_set(camera, new_pos);

    //player rot
    double x, y, dx, dy;
    rcge_io_mouse_loc(window, &x, &y);
    dx = x - lastX;
    dy = y - lastY;
    lastX = x;
    lastY = y;
    
    vec3 apply_player_x_rot, apply_player_y_rot, apply_player_rot;
    glm_vec3_scale(cam_left, dy, apply_player_x_rot);
    glm_vec3_scale(ny_axis, dx, apply_player_y_rot);
    glm_vec3_add(apply_player_x_rot, apply_player_y_rot, apply_player_rot);
    glm_vec3_scale(apply_player_rot, 0.004, apply_player_rot);
    rcge_camera_add_rot_euler(camera, apply_player_rot);

    rcge_mesh_draw(mesh);
    
    update_fps(delta_time);
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
    vec3 cam_pos = {0.0f, 0.0f, -5.0f};
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