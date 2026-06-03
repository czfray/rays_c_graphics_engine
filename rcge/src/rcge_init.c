#define STB_IMAGE_IMPLEMENTATION
#include <glfw/glfw3.h>
#include <stbi/stb_image.h>
#include <rcge/rcge_init.h>

#include <stdio.h>
#include <stdbool.h>

static bool status = false;

bool rcge_init(void)
{
    if(status) {printf("[RCGE Init] RCGE already initialised.\n"); return true;}
    if (!glfwInit()) {printf("[RCGE Init] RCGE failed to init: GLFW failed.\n"); return false;}
    stbi_set_flip_vertically_on_load(1);
    printf("[RCGE Init] RCGE initialised.\n");
    status = true;
    return true;
}
void rcge_terminate(void)
{
    if(!status) {printf("[RCGE Init] RCGE failed to terminate: already terminated.\n"); return;}
    glfwTerminate();
    status = false;
    printf("[RCGE Init] RCGE terminated.\n");
}
bool rcge_status(void) {return status;}
