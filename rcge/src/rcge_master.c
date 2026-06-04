#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <rcge/rcge_master.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#include <cglm/cglm.h>

typedef struct
{
    GLFWwindow* gl_window;
    double last_update_time;

    rcge_start_callback start_cb;
    rcge_update_callback update_cb;
    rcge_resize_callback resize_cb;

    rcge_display_mode display_mode;

    unsigned int width, height;
    unsigned int last_window_pos_x, last_window_pos_y, last_window_size_x, last_window_size_y; 

    bool status;
} rcge_state;

rcge_state current_state = {NULL, 0, NULL, NULL, NULL, 0, 0, false};

void gl_resize(GLFWwindow* gl_window, int width, int height)
{
    glViewport(0, 0, width, height);
    current_state.width = width;
    current_state.height = height;
    rcge_resize_callback cb = (rcge_resize_callback) glfwGetWindowUserPointer(gl_window);
    if (cb != NULL) cb(width, height);
}

bool rcge_init(int width, int height, const char* title, bool resizable, rcge_start_callback start_cb, rcge_update_callback update_cb, rcge_resize_callback resize_cb)
{
    if(current_state.status) {printf("[RCGE Master] RCGE already initialised.\n"); return false;}

    //Setup GLFW
    if (!glfwInit()) {printf("[RCGE Master] RCGE failed to initalise: GLFW failed.\n"); return false;}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable? GL_TRUE: GL_FALSE);
    
    //Create GLFW Window
    GLFWwindow* gl_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (gl_window == NULL)
    {
        printf("[RCGE Master] Window failed to initialise: GLFW failed.\n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(gl_window);

    //Initialise GLAD (Manages function pointers)
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("[RCGE Master] Window failed to initialise: GLAD failed to initialise.\n");
        glfwDestroyWindow(gl_window);
        glfwTerminate();
        return false;
    }

    int buf_w, buf_h; 
    glfwGetFramebufferSize(gl_window, &buf_w, &buf_h); 
    gl_resize(gl_window, buf_w, buf_h);
    
    //Resize callback set
    glfwSetFramebufferSizeCallback(gl_window, gl_resize);
    glfwSetWindowUserPointer(gl_window, resize_cb);

    //TODO: TEMP
    glfwSwapInterval(0); //Vsync Off
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glfwSetInputMode(gl_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    //STBI Initialisation
    stbi_set_flip_vertically_on_load(1);
    
    //Change State
    current_state.gl_window = gl_window;
    current_state.last_update_time = glfwGetTime();
    current_state.start_cb = start_cb;
    current_state.update_cb = update_cb;
    current_state.resize_cb = resize_cb;
    current_state.display_mode = DISPLAY_WINDOW;
    current_state.status = true;

    printf("[RCGE Master] RCGE initialised.\n");
    return true;
}

void rcge_run(void)
{
    if (!current_state.status) {printf("[RCGE Master] RCGE run failed: RCGE is not initialised.\n"); return;}
    printf("[RCGE Master] RCGE main loop running.\n");

    if (current_state.start_cb != NULL) current_state.start_cb();
    GLFWwindow* gl_window = current_state.gl_window;
    glfwMakeContextCurrent(gl_window);

    while (!glfwWindowShouldClose(gl_window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double current_time = glfwGetTime();
        if (current_state.update_cb != NULL) current_state.update_cb(current_time - current_state.last_update_time);
        current_state.last_update_time = current_time;

        glfwSwapBuffers(gl_window); 
    }
    printf("[RCGE Master] RCGE stopped running.\n");
}

void rcge_stop(void)
{
    if (!current_state.status) {printf("[RCGE Master] RCGE stop failed: RCGE is not initialised.\n"); return;}
    glfwSetWindowShouldClose(current_state.gl_window, GL_TRUE);
}

void rcge_terminate(void)
{
    if (!current_state.status) {printf("[RCGE Master] RCGE stop failed: RCGE is not initialised.\n"); return;}
    glfwDestroyWindow(current_state.gl_window);
    glfwTerminate();
    current_state.status = false;
    printf("[RCGE Master] RCGE terminated.\n");
}

bool rcge_status(void)
{
    return current_state.status;
}

void rcge_display_dimensions(unsigned int* width, unsigned int* height)
{
    if (!current_state.status) {printf("[RCGE Master] RCGE get window dimensions get failed: RCGE is not initialised.\n"); return;}
    *width = current_state.width; *height = current_state.height;
}

double rcge_display_ratio(void)
{
    if (!current_state.status) {printf("[RCGE Master] RCGE get window aspect ratio get failed: RCGE is not initialised.\n"); return NAN;}
    return ((double) current_state.width) / current_state.height;
}

GLFWmonitor* get_gl_monitor_window_in(int center_x, int center_y, int* out_x, int* out_y)
{
    int monitor_no;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_no);
    for (int i = 0; i < monitor_no; i++)
    {
        int mon_pos_x, mon_pos_y, mon_size_x, mon_size_y;
        glfwGetMonitorWorkarea(monitors[i], &mon_pos_x, &mon_pos_y, &mon_size_x, &mon_size_y);
        if (center_x >= mon_pos_x && center_x < (mon_pos_x + mon_size_x) && center_y >= mon_pos_y && center_y < (mon_pos_y + mon_size_y)) 
        {
            *out_x = mon_pos_x; 
            *out_y = mon_pos_y;
            return monitors[i]; 
        }
    }
    *out_x = 0;
    *out_y = 0;
    return glfwGetPrimaryMonitor();
}

void rcge_display_mode_set(rcge_display_mode display_mode)
{
    int pos_x, pos_y, size_x, size_y;
    glfwGetWindowPos(current_state.gl_window, &pos_x, &pos_y);
    glfwGetWindowSize(current_state.gl_window, &size_x, &size_y);
    if (current_state.display_mode == DISPLAY_WINDOW) 
    {
        //Save last window pos and size to be restored if fullscreen is exited
        current_state.last_window_pos_x = pos_x;
        current_state.last_window_pos_y = pos_y;
        current_state.last_window_size_x = size_x;
        current_state.last_window_size_y = size_y;
    }

    int mon_pos_x, mon_pos_y;
    GLFWmonitor* gl_monitor = get_gl_monitor_window_in(pos_x + (size_x / 2), pos_y + (size_y / 2), &mon_pos_x, &mon_pos_y);
    const GLFWvidmode* gl_vid_mode = glfwGetVideoMode(gl_monitor);
    switch (display_mode)
    {
        case DISPLAY_BORDERLESS_FULLSCREEN:
            glfwSetWindowAttrib(current_state.gl_window, GLFW_DECORATED, GLFW_FALSE);
            glfwSetWindowMonitor(current_state.gl_window, NULL, mon_pos_x, mon_pos_y, gl_vid_mode->width, gl_vid_mode->height, gl_vid_mode->refreshRate);
            break;
        case DISPLAY_EXCLUSIVE_FULLSCREEN:
            glfwSetWindowMonitor(current_state.gl_window, gl_monitor, mon_pos_x, mon_pos_y, gl_vid_mode->width, gl_vid_mode->height, gl_vid_mode->refreshRate);
            break;
        case DISPLAY_WINDOW:
            glfwSetWindowAttrib(current_state.gl_window, GLFW_DECORATED, GLFW_TRUE);
            glfwSetWindowMonitor(current_state.gl_window, NULL, current_state.last_window_pos_x, current_state.last_window_pos_y, current_state.last_window_size_x, current_state.last_window_size_y, GLFW_DONT_CARE);
            break;
    }
    current_state.display_mode = display_mode;
}

void* rcge_window_raw_pointer(void)
{
   return (void*)current_state.gl_window;
}
