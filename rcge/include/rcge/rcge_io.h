#ifndef RCGE_IO_H
#define RCGE_IO_H

/** 
 * @file rcge_io.h
 * @brief I/O management.
 * 
 * @defgroup io I/O 
 * @brief I/O management.
 * 
 * This modules allows read and write of files, as well as reading keyboard and mouse inputs.
**/

#include <rcge/rcge_window.h>
#include <stdbool.h>

/**
 * @ingroup io
 * @brief Get all lines of text from a file.
 * @param[in] path Relative path of the file to be read.
 * @param[in] buffer_size Read buffer size.
 * @return The text of file, NULL if failed.
**/
char* rcge_io_read_file_all(char *path, int buffer_size);

/**
 * @ingroup io
 * @brief Get pixel data from an image file.
 * @param[in] path Relative path of the file to be read.
 * @param[out] width Width of the image read.
 * @param[out] height Height of the image read.
 * @param[out] channel_no Number of channels of image read originally. (3=RGB, 4=RGBA)
 * @param[in] desired_channel_no Force the image to have this amount of number of channels. (0=original, 3=RGB, 4=RGBA)
 * @return The pixel data of image, NULL if failed.
 * @note Do not call free(), but call @ref rcge_io_free_image to free the pixel data.
**/
unsigned char* rcge_io_read_image(char *path, unsigned int* width, unsigned int* height, unsigned int* channel_no, unsigned int desired_channel_no);

/**
 * @ingroup io
 * @brief Free image pixel data. Prevents memory leaks.
 * @param[in] image Image data to be freed.
**/
void rcge_io_free_image(unsigned char* image);

/**
 * @ingroup io
 * @enum rcge_io_input
 * @brief All keyboard and mouse inputs.
**/
typedef enum
{
    IO_KEY_SPACE = 0,
    IO_KEY_APOSTROPHE,
    IO_KEY_COMMA,
    IO_KEY_MINUS,
    IO_KEY_PERIOD,
    IO_KEY_SLASH,
    IO_KEY_0,
    IO_KEY_1,
    IO_KEY_2,
    IO_KEY_3,
    IO_KEY_4,
    IO_KEY_5,
    IO_KEY_6,
    IO_KEY_7,
    IO_KEY_8,
    IO_KEY_9,
    IO_KEY_SEMICOLON,
    IO_KEY_EQUAL,
    IO_KEY_A,
    IO_KEY_B,
    IO_KEY_C,
    IO_KEY_D,
    IO_KEY_E,
    IO_KEY_F,
    IO_KEY_G,
    IO_KEY_H,
    IO_KEY_I,
    IO_KEY_J,
    IO_KEY_K,
    IO_KEY_L,
    IO_KEY_M,
    IO_KEY_N,
    IO_KEY_O,
    IO_KEY_P,
    IO_KEY_Q,
    IO_KEY_R,
    IO_KEY_S,
    IO_KEY_T,
    IO_KEY_U,
    IO_KEY_V,
    IO_KEY_W,
    IO_KEY_X,
    IO_KEY_Y,
    IO_KEY_Z,
    IO_KEY_LEFT_BRACKET,
    IO_KEY_BACKSLASH,
    IO_KEY_RIGHT_BRACKET,
    IO_KEY_GRAVE_ACCENT,
    IO_KEY_WORLD_1,
    IO_KEY_WORLD_2,
    IO_KEY_ESCAPE,
    IO_KEY_ENTER,
    IO_KEY_TAB,
    IO_KEY_BACKSPACE,
    IO_KEY_INSERT,
    IO_KEY_DELETE,
    IO_KEY_RIGHT,
    IO_KEY_LEFT,
    IO_KEY_DOWN,
    IO_KEY_UP,
    IO_KEY_PAGE_UP,
    IO_KEY_PAGE_DOWN,
    IO_KEY_HOME,
    IO_KEY_END,
    IO_KEY_CAPS_LOCK,
    IO_KEY_SCROLL_LOCK,
    IO_KEY_NUM_LOCK,
    IO_KEY_PRINT_SCREEN,
    IO_KEY_PAUSE,
    IO_KEY_F1,
    IO_KEY_F2,
    IO_KEY_F3,
    IO_KEY_F4,
    IO_KEY_F5,
    IO_KEY_F6,
    IO_KEY_F7,
    IO_KEY_F8,
    IO_KEY_F9,
    IO_KEY_F10,
    IO_KEY_F11,
    IO_KEY_F12,
    IO_KEY_F13,
    IO_KEY_F14,
    IO_KEY_F15,
    IO_KEY_F16,
    IO_KEY_F17,
    IO_KEY_F18,
    IO_KEY_F19,
    IO_KEY_F20,
    IO_KEY_F21,
    IO_KEY_F22,
    IO_KEY_F23,
    IO_KEY_F24,
    IO_KEY_F25,
    IO_KEY_KP_0,
    IO_KEY_KP_1,
    IO_KEY_KP_2,
    IO_KEY_KP_3,
    IO_KEY_KP_4,
    IO_KEY_KP_5,
    IO_KEY_KP_6,
    IO_KEY_KP_7,
    IO_KEY_KP_8,
    IO_KEY_KP_9,
    IO_KEY_KP_DECIMAL,
    IO_KEY_KP_DIVIDE,
    IO_KEY_KP_MULTIPLY,
    IO_KEY_KP_SUBTRACT,
    IO_KEY_KP_ADD,
    IO_KEY_KP_ENTER,
    IO_KEY_KP_EQUAL,
    IO_KEY_LEFT_SHIFT,
    IO_KEY_LEFT_CONTROL,
    IO_KEY_LEFT_ALT,
    IO_KEY_LEFT_SUPER,
    IO_KEY_RIGHT_SHIFT,
    IO_KEY_RIGHT_CONTROL,
    IO_KEY_RIGHT_ALT,
    IO_KEY_RIGHT_SUPER,
    IO_KEY_MENU,
    IO_KEY_LAST,

    IO_MOUSE_1, //121
    IO_MOUSE_2,
    IO_MOUSE_3,
    IO_MOUSE_4,
    IO_MOUSE_5,
    IO_MOUSE_6,
    IO_MOUSE_7,
    IO_MOUSE_8,
    IO_MOUSE_LAST,
    IO_MOUSE_LEFT,
    IO_MOUSE_RIGHT,
    IO_MOUSE_MIDDLE
} rcge_io_input;

/**
 * @ingroup io
 * @enum rcge_io_input_type
 * @brief Types of inputs.
**/
typedef enum
{
    IO_TYPE_KEYBOARD, ///< Keyboard
    IO_TYPE_MOUSE ///< Mouse
} rcge_io_input_type;

/**
 * @ingroup io
 * @brief See which input type is an input.
 * @param[in] input The input to check.
 * @return The input type of the specified input.
**/
rcge_io_input_type rcge_io_input_type_get(rcge_io_input input);

/**
 * @ingroup io
 * @brief See if a specific input is pressed.
 * @param[in] window The application window.
 * @param[in] input The input to check.
 * @return Whether the specified input is pressed or not.
**/
bool rcge_io_input_pressed(rcge_window window, rcge_io_input input);

/**
 * @ingroup io
 * @brief The location of mouse (cursor) on screen.
 * @param[in] window The application window.
 * @param[out] x The horizontal location of the cursor.
 * @param[out] y The vertical location of the cursor.
**/
void rcge_io_mouse_loc(rcge_window window, double* x, double* y);

#endif