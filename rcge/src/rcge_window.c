#include <rcge/rcge_window.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct rcge_window_CDT
{
    GLFWwindow* gl_window;
    double last_update_time;
    rcge_resize_callback resize_cb;
};

void gl_resize(GLFWwindow* gl_window, int width, int height)
{
    glViewport(0, 0, width, height);
    rcge_window window = (rcge_window) glfwGetWindowUserPointer(gl_window);
    rcge_resize_callback cb = window->resize_cb;
    if (cb != NULL) cb(window, width, height);
}

rcge_window rcge_window_create(int width, int height, const char* title, bool resizable)
{
    //CHECKS FOR GLFW INIT NEEDED
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable? GL_TRUE: GL_FALSE);

    GLFWwindow* gl_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (gl_window == NULL)
    {
        printf("[RCGE Window] Window failed to initialise: GLFW failed.\n");
        return NULL;
    }

    glfwMakeContextCurrent(gl_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) //Initialise GLAD (Manages function pointers)
    {
        printf("[RCGE Window] Window failed to initialise: GLAD failed to initialise.\n");
        glfwDestroyWindow(gl_window);
        return NULL;
    }

    glfwSwapInterval(0); //Vsync Off
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(gl_window, gl_resize);

    //TODO: TEMP
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glfwSetInputMode(gl_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //

    rcge_window window = malloc(sizeof(*window)); //TODO: MALLOC CHECK?
    window->gl_window = gl_window;
    window->last_update_time = glfwGetTime();
    window->resize_cb = NULL;
    glfwSetWindowUserPointer(gl_window, (void*) window);

    int buf_w, buf_h; 
    glfwGetFramebufferSize(gl_window, &buf_w, &buf_h); 
    gl_resize(gl_window, buf_w, buf_h);
    printf("[RCGE Window] Window created.\n");
    return window;
}

//Assumes only one window can run at the same time.
void rcge_window_run(rcge_window window, rcge_start_callback start_cb, rcge_update_callback update_cb, rcge_resize_callback resize_cb)
{
    //CHECKS FOR GLFW INIT and PARAMS NEEDED
    printf("[RCGE Window] Window started running.\n");
    window->resize_cb = resize_cb;

    if (start_cb != NULL) start_cb(window);
    GLFWwindow* gl_window = window->gl_window;
    glfwMakeContextCurrent(gl_window);

    while (!glfwWindowShouldClose(gl_window))
    {
        glfwPollEvents(); //Retrieve window events

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double current_time = glfwGetTime();
        if (update_cb != NULL) update_cb(window, current_time - window->last_update_time);
        window->last_update_time = current_time;

        glfwSwapBuffers(gl_window); //Swap back and front buffers
    }

    glfwDestroyWindow(gl_window);
    free(window);
    printf("[RCGE Window] Window terminated as intended.\n");
}

float rcge_window_ratio(rcge_window window)
{
    int buf_w, buf_h; 
    glfwGetFramebufferSize(window->gl_window, &buf_w, &buf_h); 
    return ((float) buf_w) / buf_h;
}

//TODO: Merge this with init?

void* rcge_window_raw_pointer(rcge_window window) {return (void*)window->gl_window;}

void rcge_window_stop(rcge_window window) {glfwSetWindowShouldClose(window->gl_window, GL_TRUE);}