#ifndef RCGE_TRANSFORM_H
#define RCGE_TRANSFORM_H

#include <cglm/cglm.h>
#include <stdbool.h>

typedef struct rcge_transform_CDT* rcge_transform;

rcge_transform rcge_transform_create(vec3 pos, versor rot, vec3 scl, bool update_view);
rcge_transform rcge_transform_create_zero(bool update_view);

void rcge_transform_pos_get(rcge_transform transform, vec3 out);
void rcge_transform_rot_get(rcge_transform transform, versor out);
void rcge_transform_scl_get(rcge_transform transform, vec3 out);
void rcge_transform_model_view_get(rcge_transform transform, mat4 out);

void rcge_transform_pos_set(rcge_transform transform, vec3 new_pos);
void rcge_transform_rot_set(rcge_transform transform, versor new_rot);
void rcge_transform_scl_set(rcge_transform transform, vec3 new_scl);

void rcge_transform_add_rot_euler(rcge_transform transform, vec3 apply_rot);

void rcge_transform_delete(rcge_transform transform);

#endif