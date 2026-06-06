#include <rcge/rcge.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int frame;
double time;

double lastX;
double lastY;

rcge_shader shader;
rcge_texture keven_texture;
unsigned int mesh_element_index;
rcge_camera camera;
rcge_element_manager element_manager;

void start()
{
    int frame = 0;
    time = 0;
    printf("Testing app start!\n");

    rcge_shader_uniform_vec4(shader, 3, GLM_VEC4_ONE); //TODO SET MESH COLOR
    rcge_io_mouse_loc(&lastX, &lastY);

    float vertices[] =
    {
        -0.5, -0.5, -0.5,   1.0, 0.0,
        -0.5, 0.5, -0.5,    1.0, 1.0,
        0.5, 0.5, -0.5,     0.0, 1.0,
        0.5, -0.5, -0.5,    0.0, 0.0, 

        -0.5, -0.5, 0.5,    1.0, 0.0,
        -0.5, 0.5, 0.5,     1.0, 1.0,
        -0.5, 0.5, -0.5,    0.0, 1.0,
        -0.5, -0.5, -0.5,   0.0, 0.0, 

        0.5, -0.5, 0.5,     1.0, 0.0,
        0.5, 0.5, 0.5,      1.0, 1.0,
        -0.5, 0.5, 0.5,     0.0, 1.0,
        -0.5, -0.5, 0.5,    0.0, 0.0, 

        0.5, -0.5, -0.5,    1.0, 0.0,
        0.5, 0.5, -0.5,     1.0, 1.0,
        0.5, 0.5, 0.5,      0.0, 1.0,
        0.5, -0.5, 0.5,     0.0, 0.0,

        -0.5, 0.5, -0.5,    1.0, 0.0,
        -0.5, 0.5, 0.5,     1.0, 1.0,
        0.5, 0.5, 0.5,      0.0, 1.0,
        0.5, 0.5, -0.5,     0.0, 0.0,

        -0.5, -0.5, 0.5,    1.0, 0.0,
        -0.5, -0.5, -0.5,   1.0, 1.0,
        0.5, -0.5, -0.5,    0.0, 1.0,
        0.5, -0.5, 0.5,     0.0, 0.0
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

    mesh_element_index = rcge_singlemesh_create_in_manager(element_manager, shader, RCGE_DEF_UNLIT_SHADER_MODEL_UNF, keven_texture, vertices, 120, indices, 36, MESH_STATIC);

    int no = 5;
    for (int k = -no; k < no; k++)
    {
        for (int j = -no; j < no; j++)
        {
            for (int i = -no; i < no; i++)
            {
                if (i == 0 && j == 0 && k == 0) continue;
                unsigned int index = rcge_singlemesh_create_in_manager(element_manager, shader, RCGE_DEF_UNLIT_SHADER_MODEL_UNF, keven_texture, vertices, 120, indices, 36, MESH_STATIC);
                rcge_transform transform = rcge_mesh_transform_get(rcge_singlemesh_mesh_get(rcge_element_manager_element_get(element_manager, index)));
                vec3 pos = {i * 3, j * 3, k * 3};
                rcge_transform_pos_set(transform, pos);
            }
        }
    }
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

bool fstest = false;

void update(double delta_time)
{
    if (rcge_io_input_pressed(IO_KEY_ESCAPE)) rcge_stop();
    
    rcge_transform transform = rcge_mesh_transform_get(rcge_singlemesh_mesh_get(rcge_element_manager_element_get(element_manager, mesh_element_index)));

    vec3 x_axis = {1, 0, 0};
    vec3 y_axis = {0, 1, 0};
    vec3 z_axis = {0, 0, 1};

    vec3 nx_axis = {-1, 0, 0};
    vec3 ny_axis = {0, -1, 0};
    vec3 nz_axis = {0, 0, -1};

    float currentfov = rcge_camera_fov_size_get(camera);
    if (rcge_io_input_pressed(IO_MOUSE_LEFT)) rcge_camera_fov_size_set(camera, currentfov + 100 * delta_time);
    if (rcge_io_input_pressed(IO_MOUSE_RIGHT)) rcge_camera_fov_size_set(camera, currentfov - 100 * delta_time);

    //cube scale
    vec3 apply_scl = GLM_VEC3_ZERO_INIT;
    if (rcge_io_input_pressed(IO_KEY_KP_ADD)) glm_vec3_add(apply_scl, GLM_VEC3_ONE, apply_scl); 
    if (rcge_io_input_pressed(IO_KEY_KP_SUBTRACT)) glm_vec3_sub(apply_scl, GLM_VEC3_ONE, apply_scl); 
    glm_vec3_scale(apply_scl, 3 * delta_time, apply_scl);

    rcge_transform_add_scl(transform, apply_scl);

    //cube pos
    vec3 apply_pos = GLM_VEC3_ZERO_INIT;
    if (rcge_io_input_pressed(IO_KEY_LEFT)) glm_vec3_add(apply_pos, x_axis, apply_pos); 
    if (rcge_io_input_pressed(IO_KEY_RIGHT)) glm_vec3_add(apply_pos, nx_axis, apply_pos); 
    if (rcge_io_input_pressed(IO_KEY_PAGE_UP)) glm_vec3_add(apply_pos, y_axis, apply_pos); 
    if (rcge_io_input_pressed(IO_KEY_PAGE_DOWN)) glm_vec3_add(apply_pos, ny_axis, apply_pos); 
    if (rcge_io_input_pressed(IO_KEY_UP)) glm_vec3_add(apply_pos, z_axis, apply_pos); 
    if (rcge_io_input_pressed(IO_KEY_DOWN)) glm_vec3_add(apply_pos, nz_axis, apply_pos); 
    glm_vec3_norm(apply_pos);
    glm_vec3_scale(apply_pos, 3 * delta_time, apply_pos);

    rcge_transform_add_pos(transform, apply_pos);

    //cube rot
    vec3 apply_rot_euler = GLM_VEC3_ZERO_INIT;
    if (rcge_io_input_pressed(IO_KEY_KP_8)) glm_vec3_add(apply_rot_euler, x_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(IO_KEY_KP_5)) glm_vec3_add(apply_rot_euler, nx_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(IO_KEY_KP_6)) glm_vec3_add(apply_rot_euler, y_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(IO_KEY_KP_4)) glm_vec3_add(apply_rot_euler, ny_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(IO_KEY_KP_9)) glm_vec3_add(apply_rot_euler, z_axis, apply_rot_euler); 
    if (rcge_io_input_pressed(IO_KEY_KP_7)) glm_vec3_add(apply_rot_euler, nz_axis, apply_rot_euler); 
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

    if (rcge_io_input_pressed(IO_KEY_A)) glm_vec3_add(apply_player_pos, cam_left, apply_player_pos); 
    if (rcge_io_input_pressed(IO_KEY_D)) glm_vec3_add(apply_player_pos, cam_right, apply_player_pos); 
    if (rcge_io_input_pressed(IO_KEY_W)) glm_vec3_add(apply_player_pos, cam_forward, apply_player_pos); 
    if (rcge_io_input_pressed(IO_KEY_S)) glm_vec3_add(apply_player_pos, cam_backward, apply_player_pos);

    if (rcge_io_input_pressed(IO_KEY_SPACE)) glm_vec3_add(apply_player_pos, y_axis, apply_player_pos); 
    if (rcge_io_input_pressed(IO_KEY_LEFT_SHIFT)) glm_vec3_add(apply_player_pos, ny_axis, apply_player_pos);        
    glm_vec3_norm(apply_player_pos);
    glm_vec3_scale(apply_player_pos, 5 * delta_time, apply_player_pos);

    rcge_camera_add_pos(camera, apply_player_pos);

    //player rot
    double x, y, dx, dy;
    rcge_io_mouse_loc(&x, &y);
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

    if (rcge_io_input_just_pressed(IO_KEY_BACKSPACE))
    {
        rcge_camera_rot_set(camera, GLM_QUAT_IDENTITY);
        vec3 def = {0, 0, -2};
        rcge_camera_pos_set(camera, def);
    }

    if (rcge_io_input_just_pressed(IO_KEY_F1))
    {
        fstest = !fstest;
        rcge_display_mode_set(fstest? DISPLAY_BORDERLESS_FULLSCREEN: DISPLAY_WINDOW);
    }

    rcge_element_manager_update(element_manager, delta_time);
    
    update_fps(delta_time);
}

void resize(int width, int height)
{
    rcge_camera_ratio_set(camera, rcge_display_ratio());
}

int main(void)
{
    if (!rcge_init(1000, 800, "RCGE Test", true, start, update, resize)) return 1;

    shader = rcge_default_unlit_shader_create();
    rcge_shader_use(shader);
    
    camera = rcge_camera_create(shader, RCGE_DEF_UNLIT_SHADER_VIEW_UNF, RCGE_DEF_UNLIT_SHADER_PROJ_UNF, true, 45.0f, 0.001f, 100.0f);
    //camera = rcge_camera_create(shader, 1, 2, false, 2.0f, 1.0f, 100.0f, rcge_display_ratio(window));
    vec3 cam_pos = {0.0f, 0.0f, -2.0f};
    rcge_camera_pos_set(camera, cam_pos);

    keven_texture = rcge_texture_create("textures/keven.png", TEX_CLAMP_TO_EDGE, TEX_LINEAR);
    rcge_texture_use(keven_texture);
    rcge_shader_uniform_int(shader, 4, 0); //OPTIONAL, default is 0 already, only need if multiple texture layer. //TODO THIS IS UGLY AF

    element_manager = rcge_element_manager_create(128);

    rcge_io_mouse_use_raw(true);

    rcge_run();
    
    rcge_element_manager_delete(element_manager);
    rcge_texture_delete(keven_texture);
    rcge_camera_delete(camera);
    rcge_shader_delete(shader);
    
    rcge_terminate();
    return 0;
}