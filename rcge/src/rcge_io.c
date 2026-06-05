#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stbi/stb_image.h>

#include <rcge/rcge_io.h>
#include <rcge/rcge_master.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RCGE_IO_KEY_THRESHOLD 0
#define RCGE_IO_MOUSE_THRESHOLD 121
#define RCGE_IO_INPUT_TOTAL_NO 133

bool current_input_pressed[RCGE_IO_INPUT_TOTAL_NO] = {false};
bool current_input_just_pressed[RCGE_IO_INPUT_TOTAL_NO] = {false};
bool current_input_just_released[RCGE_IO_INPUT_TOTAL_NO] = {false};

char *rcge_io_read_file_all(char *path, int buffer_size)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("[RCGE IO] File \"%s\" failed to open: fopen failed.\n", path);
        return NULL;
    }

    char *result = (char *)malloc(1);
    int resultLen = 0;
    if (result == NULL)
    {
        printf("[RCGE IO] File \"%s\" failed to load: malloc failed.\n", path);
        return NULL;
    }

    char buffer[buffer_size];
    while (fgets(buffer, sizeof(buffer), file))
    {
        int bufferLen = strlen(buffer);
        result = (char *)realloc(result, resultLen + bufferLen + 1);
        if (result == NULL)
        {
            printf("[RCGE IO] File \"%s\" failed to load: realloc failed.\n", path);
            free(result);
            return NULL;
        }
        strcpy(result + resultLen, buffer);
        resultLen += bufferLen;
    }
    printf("[RCGE IO] File \"%s\" all lines read.\n", path);
    fclose(file);
    return result;
}

unsigned char* rcge_io_read_image(char *path, unsigned int* width, unsigned int* height, unsigned int* channel_no, unsigned int desired_channel_no)
{
    char* image = stbi_load(path, width, height, channel_no, desired_channel_no);
    if (image == NULL)
    {
        printf("[RCGE IO] Image file \"%s\" failed to be read: STBI failed. Log -> %s.\n", path, stbi_failure_reason());
        return NULL;
    }
    return image;
}

void rcge_io_free_image(unsigned char* image)
{
    stbi_image_free(image);
}

int gl_input_id(rcge_io_input input)
{
    switch (input)
    {
        case IO_KEY_SPACE:
            return GLFW_KEY_SPACE;
        case IO_KEY_APOSTROPHE:
            return GLFW_KEY_APOSTROPHE;
        case IO_KEY_COMMA:
            return GLFW_KEY_COMMA;
        case IO_KEY_MINUS:
            return GLFW_KEY_MINUS;
        case IO_KEY_PERIOD:
            return GLFW_KEY_PERIOD;
        case IO_KEY_SLASH:
            return GLFW_KEY_SLASH;
        case IO_KEY_0:
            return GLFW_KEY_0;
        case IO_KEY_1:
            return GLFW_KEY_1;
        case IO_KEY_2:
            return GLFW_KEY_2;
        case IO_KEY_3:
            return GLFW_KEY_3;
        case IO_KEY_4:
            return GLFW_KEY_4;
        case IO_KEY_5:
            return GLFW_KEY_5;
        case IO_KEY_6:
            return GLFW_KEY_6;
        case IO_KEY_7:
            return GLFW_KEY_7;
        case IO_KEY_8:
            return GLFW_KEY_8;
        case IO_KEY_9:
            return GLFW_KEY_9;
        case IO_KEY_SEMICOLON:
            return GLFW_KEY_SEMICOLON;
        case IO_KEY_EQUAL:
            return GLFW_KEY_EQUAL;
        case IO_KEY_A:
            return GLFW_KEY_A;
        case IO_KEY_B:
            return GLFW_KEY_B;
        case IO_KEY_C:
            return GLFW_KEY_C;
        case IO_KEY_D:
            return GLFW_KEY_D;
        case IO_KEY_E:
            return GLFW_KEY_E;
        case IO_KEY_F:
            return GLFW_KEY_F;
        case IO_KEY_G:
            return GLFW_KEY_G;
        case IO_KEY_H:
            return GLFW_KEY_H;
        case IO_KEY_I:
            return GLFW_KEY_I;
        case IO_KEY_J:
            return GLFW_KEY_J;
        case IO_KEY_K:
            return GLFW_KEY_K;
        case IO_KEY_L:
            return GLFW_KEY_L;
        case IO_KEY_M:
            return GLFW_KEY_M;
        case IO_KEY_N:
            return GLFW_KEY_N;
        case IO_KEY_O:
            return GLFW_KEY_O;
        case IO_KEY_P:
            return GLFW_KEY_P;
        case IO_KEY_Q:
            return GLFW_KEY_Q;
        case IO_KEY_R:
            return GLFW_KEY_R;
        case IO_KEY_S:
            return GLFW_KEY_S;
        case IO_KEY_T:
            return GLFW_KEY_T;
        case IO_KEY_U:
            return GLFW_KEY_U;
        case IO_KEY_V:
            return GLFW_KEY_V;
        case IO_KEY_W:
            return GLFW_KEY_W;
        case IO_KEY_X:
            return GLFW_KEY_X;
        case IO_KEY_Y:
            return GLFW_KEY_Y;
        case IO_KEY_Z:
            return GLFW_KEY_Z;
        case IO_KEY_LEFT_BRACKET:
            return GLFW_KEY_LEFT_BRACKET;
        case IO_KEY_BACKSLASH:
            return GLFW_KEY_BACKSLASH;
        case IO_KEY_RIGHT_BRACKET:
            return GLFW_KEY_RIGHT_BRACKET;
        case IO_KEY_GRAVE_ACCENT:
            return GLFW_KEY_GRAVE_ACCENT;
        case IO_KEY_WORLD_1:
            return GLFW_KEY_WORLD_1;
        case IO_KEY_WORLD_2:
            return GLFW_KEY_WORLD_2;
        case IO_KEY_ESCAPE:
            return GLFW_KEY_ESCAPE;
        case IO_KEY_ENTER:
            return GLFW_KEY_ENTER;
        case IO_KEY_TAB:
            return GLFW_KEY_TAB;
        case IO_KEY_BACKSPACE:
            return GLFW_KEY_BACKSPACE;
        case IO_KEY_INSERT:
            return GLFW_KEY_INSERT;
        case IO_KEY_DELETE:
            return GLFW_KEY_DELETE;
        case IO_KEY_RIGHT:
            return GLFW_KEY_RIGHT;
        case IO_KEY_LEFT:
            return GLFW_KEY_LEFT;
        case IO_KEY_DOWN:
            return GLFW_KEY_DOWN;
        case IO_KEY_UP:
            return GLFW_KEY_UP;
        case IO_KEY_PAGE_UP:
            return GLFW_KEY_PAGE_UP;
        case IO_KEY_PAGE_DOWN:
            return GLFW_KEY_PAGE_DOWN;
        case IO_KEY_HOME:
            return GLFW_KEY_HOME;
        case IO_KEY_END:
            return GLFW_KEY_END;
        case IO_KEY_CAPS_LOCK:
            return GLFW_KEY_CAPS_LOCK;
        case IO_KEY_SCROLL_LOCK:
            return GLFW_KEY_SCROLL_LOCK;
        case IO_KEY_NUM_LOCK:
            return GLFW_KEY_NUM_LOCK;
        case IO_KEY_PRINT_SCREEN:
            return GLFW_KEY_PRINT_SCREEN;
        case IO_KEY_PAUSE:
            return GLFW_KEY_PAUSE;
        case IO_KEY_F1:
            return GLFW_KEY_F1;
        case IO_KEY_F2:
            return GLFW_KEY_F2;
        case IO_KEY_F3:
            return GLFW_KEY_F3;
        case IO_KEY_F4:
            return GLFW_KEY_F4;
        case IO_KEY_F5:
            return GLFW_KEY_F5;
        case IO_KEY_F6:
            return GLFW_KEY_F6;
        case IO_KEY_F7:
            return GLFW_KEY_F7;
        case IO_KEY_F8:
            return GLFW_KEY_F8;
        case IO_KEY_F9:
            return GLFW_KEY_F9;
        case IO_KEY_F10:
            return GLFW_KEY_F10;
        case IO_KEY_F11:
            return GLFW_KEY_F11;
        case IO_KEY_F12:
            return GLFW_KEY_F12;
        case IO_KEY_F13:
            return GLFW_KEY_F13;
        case IO_KEY_F14:
            return GLFW_KEY_F14;
        case IO_KEY_F15:
            return GLFW_KEY_F15;
        case IO_KEY_F16:
            return GLFW_KEY_F16;
        case IO_KEY_F17:
            return GLFW_KEY_F17;
        case IO_KEY_F18:
            return GLFW_KEY_F18;
        case IO_KEY_F19:
            return GLFW_KEY_F19;
        case IO_KEY_F20:
            return GLFW_KEY_F20;
        case IO_KEY_F21:
            return GLFW_KEY_F21;
        case IO_KEY_F22:
            return GLFW_KEY_F22;
        case IO_KEY_F23:
            return GLFW_KEY_F23;
        case IO_KEY_F24:
            return GLFW_KEY_F24;
        case IO_KEY_F25:
            return GLFW_KEY_F25;
        case IO_KEY_KP_0:
            return GLFW_KEY_KP_0;
        case IO_KEY_KP_1:
            return GLFW_KEY_KP_1;
        case IO_KEY_KP_2:
            return GLFW_KEY_KP_2;
        case IO_KEY_KP_3:
            return GLFW_KEY_KP_3;
        case IO_KEY_KP_4:
            return GLFW_KEY_KP_4;
        case IO_KEY_KP_5:
            return GLFW_KEY_KP_5;
        case IO_KEY_KP_6:
            return GLFW_KEY_KP_6;
        case IO_KEY_KP_7:
            return GLFW_KEY_KP_7;
        case IO_KEY_KP_8:
            return GLFW_KEY_KP_8;
        case IO_KEY_KP_9:
            return GLFW_KEY_KP_9;
        case IO_KEY_KP_DECIMAL:
            return GLFW_KEY_KP_DECIMAL;
        case IO_KEY_KP_DIVIDE:
            return GLFW_KEY_KP_DIVIDE;
        case IO_KEY_KP_MULTIPLY:
            return GLFW_KEY_KP_MULTIPLY;
        case IO_KEY_KP_SUBTRACT:
            return GLFW_KEY_KP_SUBTRACT;
        case IO_KEY_KP_ADD:
            return GLFW_KEY_KP_ADD;
        case IO_KEY_KP_ENTER:
            return GLFW_KEY_KP_ENTER;
        case IO_KEY_KP_EQUAL:
            return GLFW_KEY_KP_EQUAL;
        case IO_KEY_LEFT_SHIFT:
            return GLFW_KEY_LEFT_SHIFT;
        case IO_KEY_LEFT_CONTROL:
            return GLFW_KEY_LEFT_CONTROL;
        case IO_KEY_LEFT_ALT:
            return GLFW_KEY_LEFT_ALT;
        case IO_KEY_LEFT_SUPER:
            return GLFW_KEY_LEFT_SUPER;
        case IO_KEY_RIGHT_SHIFT:
            return GLFW_KEY_RIGHT_SHIFT;
        case IO_KEY_RIGHT_CONTROL:
            return GLFW_KEY_RIGHT_CONTROL;
        case IO_KEY_RIGHT_ALT:
            return GLFW_KEY_RIGHT_ALT;
        case IO_KEY_RIGHT_SUPER:
            return GLFW_KEY_RIGHT_SUPER;
        case IO_KEY_MENU:
            return GLFW_KEY_MENU;
        case IO_KEY_LAST:
            return GLFW_KEY_LAST;
        case IO_MOUSE_1:
            return GLFW_MOUSE_BUTTON_1;
        case IO_MOUSE_2:
            return GLFW_MOUSE_BUTTON_2;
        case IO_MOUSE_3:
            return GLFW_MOUSE_BUTTON_3;
        case IO_MOUSE_4:
            return GLFW_MOUSE_BUTTON_4;
        case IO_MOUSE_5:
            return GLFW_MOUSE_BUTTON_5;
        case IO_MOUSE_6:
            return GLFW_MOUSE_BUTTON_6;
        case IO_MOUSE_7:
            return GLFW_MOUSE_BUTTON_7;
        case IO_MOUSE_8:
            return GLFW_MOUSE_BUTTON_8;
        case IO_MOUSE_LAST:
            return GLFW_MOUSE_BUTTON_LAST;
        case IO_MOUSE_LEFT:
            return GLFW_MOUSE_BUTTON_LEFT;
        case IO_MOUSE_RIGHT:
            return GLFW_MOUSE_BUTTON_RIGHT;
        case IO_MOUSE_MIDDLE:
            return GLFW_MOUSE_BUTTON_MIDDLE;
    }
    return GLFW_KEY_UNKNOWN;
}

rcge_io_input_type rcge_io_input_type_get(rcge_io_input input)
{
    if ((int)input >= RCGE_IO_MOUSE_THRESHOLD) return IO_TYPE_MOUSE;
    else return IO_TYPE_KEYBOARD;
}

bool rcge_io_input_pressed(rcge_io_input input)
{
    return current_input_pressed[(int) input];
}

bool rcge_io_input_just_pressed(rcge_io_input input)
{
    return current_input_just_pressed[(int)input];
}

bool rcge_io_input_just_released(rcge_io_input input)
{
    return current_input_just_released[(int)input];
}

void rcge_io_mouse_use_raw(bool raw)
{
    GLFWwindow* gl_window = (GLFWwindow*) rcge_window_raw_pointer();
    if (glfwRawMouseMotionSupported()) glfwSetInputMode(gl_window, GLFW_RAW_MOUSE_MOTION, raw? GLFW_TRUE: GLFW_FALSE);
}

void rcge_io_mouse_loc(double* x, double* y)
{
    GLFWwindow* gl_window = (GLFWwindow*) rcge_window_raw_pointer();
    glfwGetCursorPos(gl_window, x, y);
}

void rcge_io_update(void)
{
    glfwPollEvents();
    for (int i = 0; i < RCGE_IO_INPUT_TOTAL_NO; i++)
    {
        rcge_io_input input = (rcge_io_input) i;
        int gl_input = gl_input_id(input);
        GLFWwindow *gl_window = (GLFWwindow *)rcge_window_raw_pointer();
        bool pressed = false;
        switch (rcge_io_input_type_get(input))
        {
            case IO_TYPE_KEYBOARD:
                pressed = glfwGetKey(gl_window, gl_input) == GLFW_PRESS;
                break;
            case IO_TYPE_MOUSE:
                pressed = glfwGetMouseButton(gl_window, gl_input) == GLFW_PRESS;
                break;
        }

        bool prev_pressed = current_input_pressed[i];
        if (pressed && !prev_pressed) current_input_just_pressed[i] = true;
        else current_input_just_pressed[i] = false;
        
        if (!pressed && prev_pressed) current_input_just_released[i] = true;
        else current_input_just_released[i] = false;

        current_input_pressed[i] = pressed;
    }
}