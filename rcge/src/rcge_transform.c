#include <cglm/cglm.h>
#include <rcge/rcge_transform.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct rcge_transform_CDT
{
    mat4 model_view;
    versor rotation;
    vec3 position;
    vec3 scale;
    bool view_updater;

    vec3 forward;
    vec3 up;
    vec3 left;
};

void update_model(rcge_transform transform)
{
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, transform->position);

    mat4 rot;
    glm_quat_mat4(transform->rotation, rot);
    glm_mat4_mul(model, rot, model);

    glm_scale(model, transform->scale);

    glm_mat4_copy(model, transform->model_view);
}

void update_view(rcge_transform transform)
{
    vec3 pos, target, up;
    rcge_transform_pos_get(transform, pos);
    rcge_transform_forward(transform, target);
    glm_vec3_add(target, pos, target);
    rcge_transform_up(transform, up);
    glm_lookat(pos, target, up, transform->model_view);
}

void update_matrix(rcge_transform transform)
{
    if (transform->view_updater) update_view(transform);
    else update_model(transform);
}

void update_dir(rcge_transform transform)
{
    vec3 left = {1.0f, 0.0f, 0.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 forward;

    versor rot;
    rcge_transform_rot_get(transform, rot);
    glm_quat_rotatev(rot, left, left);
    glm_quat_rotatev(rot, up, up);
    glm_vec3_cross(left, up, forward);
    glm_vec3_normalize(forward);
    
    glm_vec3_copy(left, transform->left);
    glm_vec3_copy(up, transform->up);
    glm_vec3_copy(forward, transform->forward);

}

rcge_transform rcge_transform_create(vec3 pos, versor rot, vec3 scl, bool view_updater)
{
    rcge_transform transform = malloc(sizeof(*transform)); //TODO: Malloc Check
    glm_vec3_copy(pos, transform->position);
    glm_quat_copy(rot, transform->rotation);
    glm_vec3_copy(scl, transform->scale);
    transform->view_updater = view_updater;
    update_dir(transform);
    update_matrix(transform);
    return transform;
}

rcge_transform rcge_transform_create_zero(bool update_view) {return rcge_transform_create(GLM_VEC3_ZERO, GLM_QUAT_IDENTITY, GLM_VEC3_ONE, update_view);}

void rcge_transform_pos_get(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform position get failed: transform does not exist.\n"); return;}
    glm_vec3_copy(transform->position, out);
}

void rcge_transform_rot_get(rcge_transform transform, versor out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform rotation get failed: transform does not exist.\n"); return;}
    glm_quat_copy(transform->rotation, out);
}

void rcge_transform_scl_get(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform scale get failed: transform does not exist.\n"); return;}
    glm_vec3_copy(transform->scale, out);
}

void rcge_transform_model_view_get(rcge_transform transform, mat4 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform model or view get failed: transform does not exist.\n"); return;}
    glm_mat4_copy(transform->model_view, out);
}

void rcge_transform_pos_set(rcge_transform transform, vec3 new_pos)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform position set failed: transform does not exist.\n"); return;}
    glm_vec3_copy(new_pos, transform->position);
    update_matrix(transform);
}

void rcge_transform_rot_set(rcge_transform transform, versor new_rot)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform rotation set failed: transform does not exist.\n"); return;}
    glm_quat_copy(new_rot, transform->rotation);
    update_dir(transform);
    update_matrix(transform);
}

void rcge_transform_scl_set(rcge_transform transform, vec3 new_scl)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform scale set failed: transform does not exist.\n"); return;}
    glm_vec3_copy(new_scl, transform->scale);
    update_matrix(transform);
}

void rcge_transform_add_pos(rcge_transform transform, vec3 apply_pos)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform add position failed: transform does not exist.\n"); return;}
    vec3 cur_pos;
    rcge_transform_pos_get(transform, cur_pos);
    vec3 new_pos;
    glm_vec3_add(cur_pos, apply_pos, new_pos);
    rcge_transform_pos_set(transform, new_pos);
}

void rcge_transform_add_rot_euler(rcge_transform transform, vec3 apply_rot)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform add rotation failed: transform does not exist.\n"); return;}
    versor cur_rot;
    rcge_transform_rot_get(transform, cur_rot);
    versor apply_rot_quat;
    glm_euler_xyz_quat(apply_rot, apply_rot_quat);
    glm_quat_mul(apply_rot_quat, cur_rot, cur_rot);
    rcge_transform_rot_set(transform, cur_rot);
}

void rcge_transform_add_scl(rcge_transform transform, vec3 apply_scl)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform add scale failed: transform does not exist.\n"); return;}
    vec3 cur_scl;
    rcge_transform_scl_get(transform, cur_scl);
    vec3 new_scl;
    glm_vec3_add(cur_scl, apply_scl, new_scl);
    rcge_transform_scl_set(transform, new_scl);
}

void rcge_transform_up(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform up get failed: transform does not exist.\n"); return;}
    glm_vec3_copy(transform->up, out);
}

void rcge_transform_left(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform left get failed: transform does not exist.\n"); return;}
    glm_vec3_copy(transform->left, out);
}

void rcge_transform_forward(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform forward get failed: transform does not exist.\n"); return;}
    glm_vec3_copy(transform->forward, out);
}

void rcge_transform_down(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform down get failed: transform does not exist.\n"); return;}
    vec3 res;
    glm_vec3_negate_to(transform->up, res);
    glm_vec3_copy(res, out);
}

void rcge_transform_right(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform right get failed: transform does not exist.\n"); return;}
    vec3 res;
    glm_vec3_negate_to(transform->left, res);
    glm_vec3_copy(res, out);
}

void rcge_transform_backward(rcge_transform transform, vec3 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform back get failed: transform does not exist.\n"); return;}
    vec3 res;
    glm_vec3_negate_to(transform->forward, res);
    glm_vec3_copy(res, out);
}

void rcge_transform_delete(rcge_transform transform)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform delete failed: transform does not exist.\n"); return;}
    free(transform);
}