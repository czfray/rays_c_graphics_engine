#ifndef RCGE_MASTER_H
#define RCGE_MASTER_H
/**
 * @file rcge_master.h
 * @brief Master of RCGE. 
 * 
 * @defgroup master Master (RCGE Manager)
 * 
 * This module handles engine initialisation, engine termination, window settings and the main loop.
 * 
 * The process of using RCGE is: \n
 * Initialise RCGE -> Initialise textures and shaders -> Run RCGE -> Update graphics in update callbacks -> Stop RCGE (On some condition in update or window closed) -> Terminate RCGE
**/

#include <stdbool.h>

/**
 * @ingroup master
 * Function pointer representing callbacks executed when rcge starts running. (When @ref rcge_run is called)
**/
typedef void (*rcge_start_callback)(void); 

/**
 * @ingroup master
 * @brief Function pointer representing callbacks executed when rcge updates per frame.
 * @param[in] delta_time The time passed from the last frame update.
**/
typedef void (*rcge_update_callback)(double);

/**
 * @ingroup master
 * @brief Function pointer representing callbacks executed when the rcge window resizes.
 * @param[in] width The new width of the window
 * @param[in] height The new height of the window
**/
typedef void (*rcge_resize_callback)(int, int);

/**
 * @ingroup master
 * @brief Types of display modes.
**/
typedef enum
{
    DISPLAY_EXCLUSIVE_FULLSCREEN, ///< Exclusive Fullscreen Display, disappears when out of focus.
    DISPLAY_BORDERLESS_FULLSCREEN,  ///< Borderless Fullscreen Display, stays on screen when out of focus.
    DISPLAY_WINDOW ///< Windowed display.
} rcge_display_mode;

/**
 * @ingroup master
 * @brief Initialises RCGE. Creates a window for rendering.
 * @param[in] width The width of the window to be created.
 * @param[in] height The height of the window to be created.
 * @param[in] title The name of the window to be created.
 * @param[in] resizable Whether you want the window to be resizable by mouse by users.
 * @param[in] start_cb The function to be called when rcge starts running. (See @ref rcge_start_callback)
 * @param[in] update_cb The function to be called when rcge updates per frame. (See @ref rcge_update_callback)
 * @param[in] resize_cb The function to be called when rcge window resizes. (See @ref rcge_resize_callback)
 * @return true if initialisation succeed, false if failed.
**/
bool rcge_init(int width, int height, const char* title, bool resizable, rcge_start_callback start_cb, rcge_update_callback update_cb, rcge_resize_callback resize_cb);

/**
 * @ingroup master
 * Starts running RCGE.
**/
void rcge_run(void);

/**
 * @ingroup master
 * Stop running RCGE.
**/
void rcge_stop(void);

/**
 * @ingroup master
 * @brief Terminates RCGE.
 * 
 * RCGE termination must be done at the end of the program. Prevents memory leaks.
**/
void rcge_terminate(void);

/**
 * @ingroup master
 * @brief Get current RCGE status.
 * @return true if RCGE is initialised, false otherwise.
**/
bool rcge_status(void);

/**
 * @ingroup master
 * @brief Set the icon of the window to an image file.
 * @param[in] path The relative path of the image file you want to set as icon.
**/
void rcge_icon(char* path);

/**
 * @ingroup master
 * @brief Get the current dimensions of the RCGE display.
 * @param[out] width The width of the RCGE display. NULL if not needed.
 * @param[out] height The height of the RCGE display. NULL if not needed.
**/
void rcge_display_dimensions_get(unsigned int* width, unsigned int* height);

/**
 * @ingroup master
 * @brief Set the current dimensions of the RCGE display.
 * @param[in] width The width to set for the RCGE display.
 * @param[in] height The height to set for the RCGE display.
 * @note If display is not in fullscreen, it will change to window mode if this function is called. Dimensions of fullscreen cannot be forced to changed (at least yet).
**/
void rcge_display_dimensions_set(unsigned int width, unsigned int height);

/**
 * @ingroup master
 * @brief Get the aspect ratio (width/height) of the RCGE display.
 * @return The aspect ratio of the RCGE display, @ref RCGE_DOUBLE_ERROR if RCGE not initialised.
**/
double rcge_display_ratio(void);

/**
 * @ingroup master
 * @brief Get the current display mode of RCGE. (Windowed, Exclusive Fullscreen, Borderless Fullscreen)
 * @return The current display mode of RCGE. 
**/
rcge_display_mode rcge_display_mode_get(void);

/**
 * @ingroup master
 * @brief Set the display mode of RCGE. (Windowed, Exclusive Fullscreen, Borderless Fullscreen)
 * @param[in] display_mode The display mode you want to set.
**/
void rcge_display_mode_set(rcge_display_mode display_mode);

/**
 * @ingroup master
 * @brief Set whether you want VSync for your display or not.
 * 
 * If VSync is on, the frame rate will be synchronised with the monitor's refresh rate.
 * 
 * @param[in] vsync Whether you want VSync for your display or not.
**/
void rcge_display_vsync(bool vsync);

/**
 * @ingroup master
 * @brief Enable or disable backface culling.
 * 
 * When backface culling is enabled, only front faces are rendered. Outside of a mesh should be drawn in clockwise to be considered a front face. 
 * @note In RCGE, +X is to the LEFT, +Y upwards and +Z forwards. Vertices might seem clockwise but is actually flipped and is actually anti-clockwise.
 * 
 * @param[in] status Whether you want to enable backface culling or not.
**/
void rcge_backface_cull(bool status);

/**
 * @internal
 * @warning This is an RCGE Internal Function.
 * @endinternal
 */
void* rcge_window_raw_pointer(void);

#endif