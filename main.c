#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

/*
 *
 * Ray's C Graphics Engine (RCGE)
 * A OpenGL-based graphic engine written in plain C.
 * 
 * Author: Chan Ray
 * Start Date: May 10th, 2026
 * 
 * Run GCC command:
 * gcc main.c glad\src\glad.c -Iglfw\include -Iglad\include -Lglfw\lib -lglfw3 -lopengl32 -lgdi32 -o rcge
 * .\rcge
 * 
 */

int main(void)
{
    printf("RCGE starting...\n");
    glfwInit();

    //Require OpenGL context of version 3.3+, with Core profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Set if user resizing is allowed.
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //Create window in context, and set context active
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    //Initialise GLAD (Manages function pointers)
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("GLAD failed to initialise.");
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); //Retrieve window events

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);

        glfwSwapBuffers(window); //Swap back and front buffers
    }

    glfwTerminate();
    printf("RCGE terminated.");
    return 0;
}