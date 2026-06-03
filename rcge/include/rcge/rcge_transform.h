#ifndef RCGE_TRANSFORM_H
#define RCGE_TRANSFORM_H

/** 
 * @file rcge_transform.h
 * @brief Transformation management.
 * 
 * @defgroup transforms Transforms
 * @brief Transformation management.
 * 
 * This module allows the transformations of graphical 2D/3D objects.
 * A transform is a transformation management object that allows the translation, rotation and scaling of objects.
 * 
 * @note In RCGE, it is defined that +X is **LEFTWARDS**, +Y is UPWARDS, and +Z is FORWARD.
**/
#include <cglm/cglm.h>
#include <stdbool.h>
/**
 * @ingroup transforms
 * Datatype representing a transform. 
**/
typedef struct rcge_transform_CDT* rcge_transform;

/**
 * @ingroup transforms
 * @brief Creates a transform.
 * @param[in] pos Initial position of transform to be created.
 * @param[in] rot Initial rotation of transform to be created.
 * @param[in] scl Initial scale of transform to be created.
 * @param[in] update_view Whether you want the transform to update view instead of model matrix. (i.e. TRUE if is for a camera, FALSE otherwise)
 * @return The transform created, NULL if failed.
**/
rcge_transform rcge_transform_create(vec3 pos, versor rot, vec3 scl, bool update_view);

/**
 * @ingroup transforms
 * @brief Creates a transform with initial position at (0, 0, 0), rotation (0, 0, 0) in euler and scale (1, 1, 1).
 * @param[in] update_view Whether you want the transform to update view instead of model matrix. (i.e. TRUE if is for a camera, FALSE otherwise)
 * @return The transform created, NULL if failed.
**/
rcge_transform rcge_transform_create_zero(bool update_view);

/**
 * @ingroup transforms
 * @brief Get the position of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The position of the specified transform.
**/
void rcge_transform_pos_get(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Get the rotation of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The rotation (in quaternion) of the specified transform.
**/
void rcge_transform_rot_get(rcge_transform transform, versor out);

/**
 * @ingroup transforms
 * @brief Get the scale of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The scale of the specified transform.
**/
void rcge_transform_scl_get(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Get the model or view matrix of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The model matrix (if update_view false) or view matrix (if update_view true) of the specified transform.
**/
void rcge_transform_model_view_get(rcge_transform transform, mat4 out);

/**
 * @ingroup transforms
 * @brief Set the position of a specified transform.
 * @param[in] transform The transform you want to change.
 * @param[in] new_pos The position you want to set to the transform.
**/
void rcge_transform_pos_set(rcge_transform transform, vec3 new_pos);

/**
 * @ingroup transforms
 * @brief Set the rotation of a specified transform.
 * @param[in] transform The transform you want to change.
 * @param[in] new_rot The rotation (in quaternion) you want to set to the transform.
**/
void rcge_transform_rot_set(rcge_transform transform, versor new_rot);

/**
 * @ingroup transforms
 * @brief Set the scale of a specified transform.
 * @param[in] transform The transform you want to change.
 * @param[in] new_scl The scale you want to set to the transform.
**/
void rcge_transform_scl_set(rcge_transform transform, vec3 new_scl);

/**
 * @ingroup transforms
 * @brief Add an euler rotation to current rotation of a specified transform.
 * @param[in] transform The transform you want to change.
 * @param[in] apply_rot The rotation (in euler) you want to add to the transform.
**/
void rcge_transform_add_rot_euler(rcge_transform transform, vec3 apply_rot);

/**
 * @ingroup transforms
 * @brief Get the upward direction normalised vector of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The upward direction normalised vector of a specified transform.
**/
void rcge_transform_up(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Get the rightward direction normalised vector of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The rightward direction normalised vector of a specified transform.
**/
void rcge_transform_right(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Get the forward direction normalised vector of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The forward direction normalised vector of a specified transform.
**/
void rcge_transform_forward(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Get the downward direction normalised vector of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The downward direction normalised vector of a specified transform.
**/
void rcge_transform_down(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Get the leftward direction normalised vector of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The leftward direction normalised vector of a specified transform.
**/
void rcge_transform_left(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Get the backward direction normalised vector of a specified transform.
 * @param[in] transform The transform you want to access.
 * @param[out] out The backward direction normalised vector of a specified transform.
**/
void rcge_transform_backward(rcge_transform transform, vec3 out);

/**
 * @ingroup transforms
 * @brief Deletes a transform. 
 * 
 * Transform deletion must be done before the program finishes. Prevents memory leaks.
 * 
 * @param[in] transform The transform you want to delete.
**/
void rcge_transform_delete(rcge_transform transform);

#endif