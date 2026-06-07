#include <cglm/cglm.h>

#include <rcge/rcge_master.h>
#include <rcge/rcge_transform.h>
#include <rcge/rcge_camera.h>
#include <rcge/rcge_codes.h>

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
    bool is_perspective;
};

void update_view_uniform(rcge_shader shader, rcge_transform transform)
{
    mat4 view;
    rcge_transform_model_view_get(transform, view);
    unsigned int view_index = rcge_shader_uniform_purpose_get(shader, SHADER_UNIFORM_VIEW);
    if (view_index == RCGE_UINT_ERROR) return;
    rcge_shader_uniform_mat4(shader, view_index, view);
}

void update_proj_uniform(rcge_shader shader, bool is_perspective, double size_or_fov, double near, double far, double ratio)
{
    mat4 proj;
    double size = (size_or_fov / 2);
    if (is_perspective) glm_perspective(glm_rad(size_or_fov), ratio, near, far, proj); 
    else glm_ortho(-size * ratio, size * ratio, -size, size, near, far, proj);
    unsigned int proj_index = rcge_shader_uniform_purpose_get(shader, SHADER_UNIFORM_PROJECTION);
    if (proj_index == RCGE_UINT_ERROR) return;
    rcge_shader_uniform_mat4(shader, proj_index, proj);
}

rcge_camera rcge_camera_create(rcge_shader shader, bool is_perspective, double size_or_fov, double near, double far)
{
    double ratio = rcge_display_ratio();
    
    if (shader == NULL) {printf("[RCGE Camera] Camera creation failed: shader does not exist.\n"); return NULL;}
    rcge_camera camera = malloc(sizeof(*camera));
    if (camera == NULL) {printf("[RCGE Camera] Camera creation failed: malloc failed.\n"); return NULL;}

    rcge_transform transform = rcge_transform_create_zero(true);
    if (transform == NULL) {printf("[RCGE Camera] Camera creation failed: transform creation failed.\n"); free(camera); return NULL;}

    update_proj_uniform(shader, is_perspective, size_or_fov, near, far, ratio);
    update_view_uniform(shader, transform);

    camera->shader = shader;
    camera->transform = transform;
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
    update_view_uniform(camera->shader, transform);
}

void rcge_camera_rot_set(rcge_camera camera, versor new_rot)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform rot set failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_rot_set(transform, new_rot);
    update_view_uniform(camera->shader, transform);
}
void rcge_camera_add_pos(rcge_camera camera, vec3 apply_pos)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform pos add failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_add_pos(transform, apply_pos);
    update_view_uniform(camera->shader, transform);
}

void rcge_camera_add_rot_euler(rcge_camera camera, vec3 apply_rot)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera transform rot add failed: camera does not exist.\n"); return;}
    rcge_transform transform = camera->transform;
    rcge_transform_add_rot_euler(transform, apply_rot);
    update_view_uniform(camera->shader, transform);
}

void rcge_camera_param_set(rcge_camera camera, bool is_perspective, double size_or_fov, double near, double far)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera param set failed: camera does not exist.\n"); return;}
    
    update_proj_uniform(camera->shader, is_perspective, size_or_fov, near, far, camera->ratio);

    camera->is_perspective = is_perspective;
    camera->size_or_fov = size_or_fov;
    camera->near = near;
    camera->far = far;
    //printf("[RCGE Camera] Camera params set to -> size/fov: %.2f, near: %.2f, far: %.2f\n", size_or_fov, near, far);
}

double rcge_camera_fov_size_get(rcge_camera camera)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera fov/size get failed: camera does not exist.\n"); return RCGE_DOUBLE_ERROR;}
    return camera->size_or_fov;
}

void rcge_camera_fov_size_set(rcge_camera camera, double size_or_fov)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera fov/size set failed: camera does not exist.\n"); return;}
    update_proj_uniform(camera->shader, camera->is_perspective, size_or_fov, camera->near, camera->far, camera->ratio);
    camera->size_or_fov = size_or_fov;
    //printf("[RCGE Camera] Camera fov set to %.2f\n", size_or_fov);
}

void rcge_camera_ratio_set(rcge_camera camera, double ratio)
{
    if (camera == NULL) {printf("[RCGE Camera] Camera ratio set failed: camera does not exist.\n"); return;}
    
    update_proj_uniform(camera->shader, camera->is_perspective, camera->size_or_fov, camera->near, camera->far, ratio);
    camera->ratio = ratio;
    //printf("[RCGE Camera] Camera ratio set to %.2f.\n", ratio);
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