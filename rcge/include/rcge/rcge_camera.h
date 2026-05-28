#ifndef RCGE_CAMERA_H
#define RCGE_CAMERA_H
#include <cglm/cglm.h>
#include <rcge/rcge_transform.h>
#include <rcge/rcge_shader.h>
#include <stdbool.h>

typedef struct rcge_camera_CDT* rcge_camera;

rcge_camera rcge_camera_create(rcge_shader shader, unsigned int view_uniform_index, unsigned int proj_uniform_index, bool is_perspective, double size_or_fov, double near, double far, double ratio);
void rcge_camera_param_set(rcge_camera camera, bool is_perspective, double size_or_fov, double near, double far);
double rcge_camera_fov_size_get(rcge_camera camera);
void rcge_camera_fov_size_set(rcge_camera camera, double size_or_fov);
void rcge_camera_ratio_set(rcge_camera camera, double ratio);

void rcge_camera_pos_get(rcge_camera camera, vec3 out);
void rcge_camera_rot_get(rcge_camera camera, versor out);
void rcge_camera_pos_set(rcge_camera camera, vec3 new_pos);
void rcge_camera_rot_set(rcge_camera camera, versor new_rot);
void rcge_camera_add_rot_euler(rcge_camera camera, vec3 apply_rot);

void rcge_camera_delete(rcge_camera camera);

#endif