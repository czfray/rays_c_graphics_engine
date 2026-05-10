#include <stdio.h>
#include <GLFW/glfw3.h>

/*
 * Run GCC Command:
 * gcc main.c -Iglfw\include -Lglfw\lib -lglfw3 -lopengl32 -lgdi32 -o rcge
 * .\rcge
 */

int main(void)
{
    printf("RCGE starting...\n");
    glfwInit();

    glfwTerminate();
    printf("RCGE terminated.");
    return 0;
}