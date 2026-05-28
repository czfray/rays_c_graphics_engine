#include <cglm/cglm.h>

#include <rcge/rcge_transform.h>
#include <rcge/rcge_camera.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct rcge_camera_CDT
{
    rcge_shader shader;
    rcge_transform transform;
    double size_or_fov;
    double ratio;
    double near;
    double far;
    unsigned int view_uniform_index; 
    unsigned int proj_uniform_index; 
    bool is_perspective;
};

void update_view_uniform(rcge_shader shader, unsigned int view_index, rcge_transform transform)
{
    mat4 view;
    rcge_transform_model_view_get(transform, view);
    rcge_shader_uniform_mat4(shader, view_index, view);
}

void update_proj_uniform(rcge_shader shader, unsigned int proj_index, bool is_perspective, double size_or_fov, double near, double far, double ratio)
{
    mat4 proj;
    double size = (size_or_fov / 2);
    if (is_perspective) glm_perspective(glm_rad(size_or_fov), ratio, near, far, proj); 
    else glm_ortho(-size * ratio, size * ratio, -size, size, near, far, proj);
    rcge_shader_uniform_mat4(shader, proj_index, proj);
}

rcge_camera rcge_camera_create(rcge_shader shader, unsigned int view_uniform_index, unsigned int proj_uniform_index, bool is_perspective, double size_or_fov, double near, double far, double ratio)
{
    update_proj_uniform(shader, proj_uniform_index, is_perspective, size_or_fov, near, far, ratio);
    //TODO: malloc validation and shader
    rcge_transform transform = rcge_transform_create_zero(true);
    update_view_uniform(shader, view_uniform_index, transform);

    rcge_camera camera = malloc(sizeof(*camera));
    camera->shader = shader;
    camera->transform = transform;
    camera->view_uniform_index = view_uniform_index;
    camera->proj_uniform_index = proj_uniform_index;
    camera->is_perspective = is_perspective;
    camera->size_or_fov = size_or_fov;
    camera->near = near;
    camera->far = far;
    camera->ratio = ratio;
    printf("[RCGE Camera] Camera created.\n");
    return camera;
}

void rcge_camera_pos_get(rcge_camera camera, vec3 out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform pos get failed: camera does not exist.\n"); return;}
    rcge_transform_pos_get(camera->transform, out);
}

void rcge_camera_rot_get(rcge_camera camera, versor out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform rot get failed: camera does not exist.\n"); return;}
    rcge_transform_rot_get(camera->transform, out);
}

void rcge_camera_pos_set(rcge_camera camera, vec3 new_pos)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform pos set failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_pos_set(transform, new_pos);
    update_view_uniform(camera->shader, camera->view_uniform_index, transform);
}

void rcge_camera_rot_set(rcge_camera camera, versor new_rot)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform rot set failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_rot_set(transform, new_rot);
    update_view_uniform(camera->shader, camera->view_uniform_index, transform);
}

void rcge_camera_add_rot_euler(rcge_camera camera, vec3 apply_rot)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform rot add failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_add_rot_euler(transform, apply_rot);
    update_view_uniform(camera->shader, camera->view_uniform_index, transform);
}

void rcge_camera_param_set(rcge_camera camera, bool is_perspective, double size_or_fov, double near, double far)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera param set failed: camera does not exist.\n"); return;}
    
    update_proj_uniform(camera->shader, camera->proj_uniform_index, is_perspective, size_or_fov, near, far, camera->ratio);

    camera->is_perspective = is_perspective;
    camera->size_or_fov = size_or_fov;
    camera->near = near;
    camera->far = far;
    printf("[RCGE Camera] Camera params set to -> size/fov: %.2f, near: %.2f, far: %.2f\n", size_or_fov, near, far);
}

double rcge_camera_fov_size_get(rcge_camera camera)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera fov/size get failed: camera does not exist.\n"); return -1.0f;}
    return camera->size_or_fov;
}

void rcge_camera_fov_size_set(rcge_camera camera, double size_or_fov)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera fov/size set failed: camera does not exist.\n"); return;}
    update_proj_uniform(camera->shader, camera->proj_uniform_index, camera->is_perspective, size_or_fov, camera->near, camera->far, camera->ratio);
    camera->size_or_fov = size_or_fov;
    printf("[RCGE Camera] Camera fov set to %.2f\n", size_or_fov);
}

void rcge_camera_ratio_set(rcge_camera camera, double ratio)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera ratio set failed: camera does not exist.\n"); return;}
    
    update_proj_uniform(camera->shader, camera->proj_uniform_index, camera->is_perspective, camera->size_or_fov, camera->near, camera->far, ratio);
    camera->ratio = ratio;
    printf("[RCGE Camera] Camera ratio set to %.2f.\n", ratio);
}

void rcge_camera_up(rcge_camera camera, vec3 out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform dir get failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_up(transform, out);
}

void rcge_camera_right(rcge_camera camera, vec3 out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform dir get failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_right(transform, out);
}

void rcge_camera_forward(rcge_camera camera, vec3 out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform dir get failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_forward(transform, out);
}

void rcge_camera_down(rcge_camera camera, vec3 out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform dir get failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_down(transform, out);
}

void rcge_camera_left(rcge_camera camera, vec3 out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform dir get failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_left(transform, out);
}

void rcge_camera_backward(rcge_camera camera, vec3 out)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform dir get failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_backward(transform, out);
}


void rcge_camera_delete(rcge_camera camera)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera delete failed: camera does not exist.\n"); return;}
    rcge_transform_delete(camera->transform);
    free(camera);
    printf("[RCGE Camera] Camera deleted.\n");
}