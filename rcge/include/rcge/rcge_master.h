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

#define RCGE_UINT_ERROR (unsigned int) -1

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
 * @brief Get the current dimensions of the RCGE display.
 * @param[out] width The width of the RCGE display.
 * @param[out] height The height of the RCGE display.
**/
void rcge_display_dimensions(unsigned int* width, unsigned int* height);

/**
 * @ingroup master
 * @brief Get the aspect ratio (width/height) of the RCGE display.
 * @return The aspect ratio of the RCGE display.
**/
double rcge_display_ratio(void);

/**
 * @ingroup master
 * @brief Set the display mode of RCGE. (Windowed, Exclusive Fullscreen, Borderless Fullscreen)
 * @param[in] display_mode The display mode you want to set.
**/
void rcge_display_mode_set(rcge_display_mode display_mode);

/**
 * @internal
 * @warning This is an RCGE Internal Function.
 * @endinternal
 */
void* rcge_window_raw_pointer(void);

#endif