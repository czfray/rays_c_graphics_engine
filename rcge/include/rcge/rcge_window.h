#ifndef RCGE_WINDOW_H
#define RCGE_WINDOW_H

/** 
 * @file rcge_window.h
 * @brief Window and main loop management.
 * 
 * @defgroup windows Windows
 * @brief Window and main loop management.
 * 
 * This module allows the creating and managing of application windows for rendering.
 * It also handles the main loop that retrieves window events and clears screen buffers every frame.
 * Windows can call user-defined functions when the it starts, resizes or updates (every frame). 
**/

#include <stdbool.h>

/**
 * @ingroup windows 
 * Datatype representing an application window.
**/
typedef struct rcge_window_CDT* rcge_window; 

/**
 * @ingroup windows
 * @typedef rcge_start_callback
 * @brief Function pointer representing callbacks executed when a window starts.
 * @param window The window that just started.
**/
typedef void (*rcge_start_callback)(rcge_window); 

/**
 * @ingroup windows
 * @typedef rcge_update_callback
 * @brief Function pointer representing callbacks executed when a window updates every frame.
 * @param window The window that is updating.
 * @param delta_time The time elapsed since the last frame update.
**/
typedef void (*rcge_update_callback)(rcge_window, double);

/**
 * @ingroup windows
 * @typedef rcge_resize_callback
 * @brief Function pointer representing callbacks executed when a window resizes.
 * @param window The window that just started.
 * @param width The new width (in pixels) of the window.
 * @param height The new height (in pixels) of the window.
**/
typedef void (*rcge_resize_callback)(rcge_window, int, int);

/**
 * @ingroup windows
 * @brief Creates an application window.
 * @param[in] width The width (in pixels) of the window to be created.
 * @param[in] height The height (in pixels) of the window to be created.
 * @param[in] title The name of the window to be created.
 * @param[in] resizable Whether the window to be created can be resized freely with cursor.
 * @return The window created, NULL if failed.
**/
rcge_window rcge_window_create(int width, int height, const char* title, bool resizable);

/**
 * @ingroup windows
 * @brief Starts to run an application window.
 * @param[in] window The window to run.
 * @param[in] start_cb User-defined function to be called when the window starts before the main loop. Can be NULL if not needed.
 * @param[in] update_cb User-defined function to be called for every frame updates in the main loop. Can be NULL if not needed.
 * @param[in] resize_cb User-defined function to be called when the window resizes. Can be NULL if not needed.
**/
void rcge_window_run(rcge_window window, rcge_start_callback start_cb, rcge_update_callback update_cb, rcge_resize_callback resize_cb);

/**
 * @ingroup windows
 * @brief Gets the aspect ratio of a specified window.
 * 
 * Formula: Width of window / Height of window.
 * 
 * @param[in] window The window concerned.
 * @return Aspect ratio of the window concerned.
**/
float rcge_window_ratio(rcge_window window);

/**
 * @ingroup windows
 * @brief Stops a window from running.
 * 
 * Interrupts the main loop.
 * 
 * @param[in] window The window to be stopped.
**/
void rcge_window_stop(rcge_window window);

void* rcge_window_raw_pointer(rcge_window window); //TODO: Move this to internal

#endif