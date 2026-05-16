#include <glfw/glfw3.h>
#include <rcge/rcge_init.h>

#include <stdio.h>
#include <stdbool.h>

static bool status = false;

bool rcge_init(void)
{
    if(status) {printf("[RCGE INIT] RCGE already initialised.\n"); return true;}
    if (!glfwInit()) {printf("[RCGE INIT] RCGE failed to init: GLFW failed.\n"); return false;}
    printf("[RCGE INIT] RCGE initialised.\n");
    status = true;
    return true;
}
void rcge_terminate(void)
{
    if(!status) {printf("[RCGE INIT] RCGE failed to terminate: already terminated.\n"); return;}
    glfwTerminate();
    status = false;
    printf("[RCGE INIT] RCGE terminated.\n");
}
bool rcge_status() {return status;}
