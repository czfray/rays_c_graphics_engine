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
    vec3 inverse_pos;
    glm_vec3_negate_to(transform->position, inverse_pos);

    versor inverse_rot;
    glm_quat_conjugate(transform->rotation, inverse_rot);

    mat4 pos_mat, rot_mat, view;
    glm_translate_make(pos_mat, inverse_pos);
    glm_quat_mat4(inverse_rot, rot_mat);
    glm_mat4_mul(rot_mat, pos_mat, view);

    glm_mat4_copy(view, transform->model_view);
}

void update_matrix(rcge_transform transform)
{
    if (transform->view_updater) update_view(transform);
    else update_model(transform);
}

rcge_transform rcge_transform_create(vec3 pos, versor rot, vec3 scl, bool view_updater)
{
    rcge_transform transform = malloc(sizeof(*transform)); //TODO: Malloc Check
    glm_vec3_copy(pos, transform->position);
    glm_quat_copy(rot, transform->rotation);
    glm_vec3_copy(scl, transform->scale);
    transform->view_updater = view_updater;
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
    update_matrix(transform);
}

void rcge_transform_scl_set(rcge_transform transform, vec3 new_scl)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform scale set failed: transform does not exist.\n"); return;}
    glm_vec3_copy(new_scl, transform->scale);
    update_matrix(transform);
}

void rcge_transform_add_rot_euler(rcge_transform transform, vec3 apply_rot)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform scale set failed: transform does not exist.\n"); return;}
    versor cur_rot;
    rcge_transform_rot_get(transform, cur_rot);
    versor apply_rot_quat;
    glm_euler_xyz_quat(apply_rot, apply_rot_quat);
    glm_quat_mul(apply_rot_quat, cur_rot, cur_rot);
    rcge_transform_rot_set(transform, cur_rot);
}

void rcge_transform_delete(rcge_transform transform)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform delete failed: transform does not exist.\n"); return;}
    free(transform);
}