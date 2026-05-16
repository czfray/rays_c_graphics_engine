#include <cglm/cglm.h>
#include <rcge/rcge_transform.h>

#include <stdio.h>
#include <stdlib.h>

struct rcge_transform_CDT
{
    mat4 model;
    versor rotation;
    vec3 position;
    vec3 scale;
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

    glm_mat4_copy(model, transform->model);
}

rcge_transform rcge_transform_create(vec3 pos, versor rot, vec3 scl)
{
    rcge_transform transform = malloc(sizeof(*transform)); //TODO: Malloc Check
    glm_vec3_copy(pos, transform->position);
    glm_quat_copy(rot, transform->rotation);
    glm_vec3_copy(scl, transform->scale);
    update_model(transform);
    return transform;
}

rcge_transform rcge_transform_create_zero() {return rcge_transform_create(GLM_VEC3_ZERO, GLM_QUAT_IDENTITY, GLM_VEC3_ONE);}

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

void rcge_transform_model_get(rcge_transform transform, mat4 out)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform model get failed: transform does not exist.\n"); return;}
    glm_mat4_copy(transform->model, out);
}

void rcge_transform_pos_set(rcge_transform transform, vec3 new_pos)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform position set failed: transform does not exist.\n"); return;}
    glm_vec3_copy(new_pos, transform->position);
    update_model(transform);
}

void rcge_transform_rot_set(rcge_transform transform, versor new_rot)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform rotation set failed: transform does not exist.\n"); return;}
    glm_quat_copy(new_rot, transform->rotation);
    update_model(transform);
}

void rcge_transform_scl_set(rcge_transform transform, vec3 new_scl)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform scale set failed: transform does not exist.\n"); return;}
    glm_vec3_copy(new_scl, transform->scale);
    update_model(transform);
}

void rcge_transform_delete(rcge_transform transform)
{
    if (transform == NULL) {printf("[RCGE Transform] Transform delete failed: transform does not exist.\n"); return;}
    free(transform);
}