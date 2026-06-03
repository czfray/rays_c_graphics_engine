#ifndef RCGE_CAMERA_H
#define RCGE_CAMERA_H
/** 
 * @file rcge_camera.h
 * @brief Camera management
 * 
 * @defgroup cameras Cameras
 * @brief Camera management.
 * 
 * This module manages the camera. Sets the perspective of render.
 * 
 * A Camera is required for a thing to actually be rendered on the screen. Christopher Nolan wont be able to make peak batman movies without a camera, right?
 * 
 * One camera per shader.
 * 
 * A camera can be in perspective mode (for 3D rendering) or orthogonal mode (for 2D rendering). In perspective mode, you set the field of view (fov). In orthogonal mode, you set the size.
 *
 * This module can be considered an element component. See @ref elements to know what it means.
 **/

#include <cglm/cglm.h>
#include <rcge/rcge_shader.h>
#include <stdbool.h>

/**
 * @ingroup cameras
 * Datatype representing a camera. Can be used as an element component. See @ref elements.
**/
typedef struct rcge_camera_CDT* rcge_camera;

/**
 * @ingroup cameras
 * @brief Creates a camera.
 * @param[in] shader The shader to use for the camera.
 * @param[in] view_uniform_index The index of the view matrix uniform in the shader used.
 * @param[in] proj_uniform_index The index of the projection matrix uniform in the shader used.
 * @param[in] is_perspective Whether the camera is perspective (3D) or orthogonal (Flat 2D).
 * @param[in] size_or_fov The fov (in radians, if perspective) or the size (if orthogonal) you want the camera to have.
 * @param[in] near The near plane of the camera. Things with less distance of `near` units from the camera would not be rendered.
 * @param[in] far The far plane of the camera. Things with further distance of `near` units from the camera would not be rendered.
 * @param[in] ratio The window aspect ratio at the time of creation.
 * @return The camera created, NULL if failed.
 * @note Make sure `shader` is currently active before calling this by using @ref rcge_shader_use.
**/
rcge_camera rcge_camera_create(rcge_shader shader, unsigned int view_uniform_index, unsigned int proj_uniform_index, bool is_perspective, double size_or_fov, double near, double far, double ratio);
//TODO: Ratio is fucking stupid?

/**
 * @ingroup cameras
 * @brief Change parameters like perspective/orthogonal, fov, far, and near plane for a specified camera.
 * @param[in] camera The camera to change.
 * @param[in] is_perspective Whether you want to change the camera to perspective (3D) or orthogonal (Flat 2D).
 * @param[in] size_or_fov The fov (in radians, if perspective) or the size (if orthogonal) you want the camera to change to.
 * @param[in] near The near plane of the camera to change to. Things with less distance of `near` units from the camera would not be rendered.
 * @param[in] far The far plane of the camera to change to. Things with further distance of `near` units from the camera would not be rendered.
 * @param[in] ratio The window aspect ratio at the time of creation.
 * @note Make sure the shader camera uses is currently active before calling this by using @ref rcge_shader_use.
**/
void rcge_camera_param_set(rcge_camera camera, bool is_perspective, double size_or_fov, double near, double far);

/**
 * @ingroup cameras
 * @brief Get the fov (if perspective) or size (if orthogonal) of a specified camera.
 * @param[in] camera The camera to access.
 * @return The fov (if perspective) or size (if orthogonal) of a specified camera, NAN if failed.
**/
double rcge_camera_fov_size_get(rcge_camera camera);

/**
 * @ingroup cameras
 * @brief Change the fov (if perspective) or size (if orthogonal) of a specified camera.
 * @param[in] camera The camera to change.
 * @param[in] size_or_fov The fov (in radians, if perspective) or the size (if orthogonal) you want the camera to change to.
 * @note Make sure the shader the camera uses is currently active before calling this by using @ref rcge_shader_use.
**/
void rcge_camera_fov_size_set(rcge_camera camera, double size_or_fov);

/**
 * @ingroup cameras
 * @brief Set the window aspect ratio of the screen to the camera. Called everytime the window is resized.
 * @param[in] camera The camera to change.
 * @param[in] ratio The window's aspect ratio.
 * @note Make sure the shader the camera uses is currently active before calling this by using @ref rcge_shader_use.
**/
void rcge_camera_ratio_set(rcge_camera camera, double ratio);

/**
 * @ingroup cameras
 * @brief Get the position of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The position of the specified camera.
**/
void rcge_camera_pos_get(rcge_camera camera, vec3 out);

/**
 * @ingroup cameras
 * @brief Get the rotation of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The rotation (in quaternion) of the specified camera.
**/

void rcge_camera_rot_get(rcge_camera camera, versor out);

/**
 * @ingroup cameras
 * @brief Set the position of a specified camera.
 * @param[in] camera The camera you want to change.
 * @param[in] new_pos The position you want to set to the camera.
 * @note Make sure the shader the camera uses is currently active before calling this by using @ref rcge_shader_use. 
**/
void rcge_camera_pos_set(rcge_camera camera, vec3 new_pos);

/**
 * @ingroup cameras
 * @brief Set the rotation of a specified camera.
 * @param[in] camera The camera you want to change.
 * @param[in] new_rot The rotation (in quaternion) you want to set to the camera.
 * @note Make sure the shader the camera uses is currently active before calling this by using @ref rcge_shader_use. 
**/
void rcge_camera_rot_set(rcge_camera camera, versor new_rot);


/**
 * @ingroup cameras
 * @brief Add an euler rotation to current rotation of a specified camera.
 * @param[in] camera The camera you want to change.
 * @param[in] apply_rot The rotation (in euler) you want to add to the camera.
 * @note Make sure the shader the camera uses is currently active before calling this by using @ref rcge_shader_use. 
**/

void rcge_camera_add_rot_euler(rcge_camera camera, vec3 apply_rot);

/**
 * @ingroup cameras
 * @brief Get the upward direction normalised vector of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The upward direction normalised vector of a specified camera.
**/
void rcge_camera_up(rcge_camera camera, vec3 out);

/**
 * @ingroup cameras
 * @brief Get the rightward direction normalised vector of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The rightward direction normalised vector of a specified camera.
**/
void rcge_camera_right(rcge_camera camera, vec3 out);

/**
 * @ingroup cameras
 * @brief Get the forward direction normalised vector of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The forward direction normalised vector of a specified camera.
**/
void rcge_camera_forward(rcge_camera camera, vec3 out);

/**
 * @ingroup cameras
 * @brief Get the downward direction normalised vector of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The downward direction normalised vector of a specified camera.
**/
void rcge_camera_down(rcge_camera camera, vec3 out);

/**
 * @ingroup cameras
 * @brief Get the leftward direction normalised vector of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The leftward direction normalised vector of a specified camera.
**/

void rcge_camera_left(rcge_camera camera, vec3 out);

/**
 * @ingroup cameras
 * @brief Get the backward direction normalised vector of a specified camera.
 * @param[in] camera The camera you want to access.
 * @param[out] out The backward direction normalised vector of a specified camera.
**/
void rcge_camera_backward(rcge_camera camera, vec3 out);

/**
 * @ingroup cameras
 * @brief Deletes a camera.
 * 
 * Camera deletion must be done before program terminates. Prevents memory leaks.
 * 
 * @param[in] camera The camera you want to delete.
**/
void rcge_camera_delete(rcge_camera camera);

#endif