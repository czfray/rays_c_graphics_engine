#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <soil/SOIL.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 *
 * Ray's C Graphics Engine (RCGE)
 * A OpenGL-based graphic engine written in plain C.
 * 
 * Author: Chan Ray
 * Start Date: May 10th, 2026
 * 
 * Run GCC command:
 * gcc main.c glad\src\glad.c -Iglfw\include -Iglad\include -Isoil\include -Icglm/include -Lglfw\lib -Lsoil\lib -lglfw3 -lsoil -lopengl32 -lgdi32 -o rcge
 * .\rcge
 * 
 */

char* loadText(char* path, int bufferSize)
{
    FILE* file = fopen(path, "r");
    if (file == NULL) {printf("%s file failed to open.\n", path); return NULL;}

    char* result = (char*) malloc(1);
    int resultLen = 0;
    if (result == NULL) {printf("%s file failed to load as malloc failed.\n", path); return NULL;}

    char buffer[bufferSize];
    while (fgets(buffer, sizeof(buffer), file)) 
    {
        int bufferLen = strlen(buffer);
        result = (char*) realloc(result, resultLen + bufferLen + 1);
        if (result == NULL) 
        {
            printf("%s file failed to load as realloc failed.\n", path);
            free(result);
            return NULL;
        }
        strcpy(result + resultLen, buffer);
        resultLen += bufferLen;
    }

    fclose(file);
    return result;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


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
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    //Create window in context, and set context active
    GLFWwindow* window = glfwCreateWindow(800, 600, "Ray's C Graphics Engine", NULL, NULL);
    glfwMakeContextCurrent(window);

    //Initialise GLAD (Manages function pointers)
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("GLAD failed to initialise.");
        return -1;
    }
    
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    printf("%d %d", w, h);
    glViewport(0, 0, w, h);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    char* vertexSource = loadText("shaders/default.vert", 128);
    if (!vertexSource) {exit(1);}
    const char* vertexSourceConst = vertexSource;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourceConst, NULL);
    glCompileShader(vertexShader);
    free(vertexSource);

    GLint status;
    char buffer[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    printf("Vertex Shader Compile Status: %d \nVertex Shader Compile Log: %s\n", status == GL_TRUE, buffer);

    char* fragSource = loadText("shaders/default.frag", 128);
    if (!fragSource) {exit(1);}
    const char* fragSourceConst = fragSource;
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSourceConst, NULL);
    glCompileShader(fragShader);
    free(fragSource);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(fragShader, 512, NULL, buffer);
    printf("Fragment Shader Compile Status: %d \nFragment Shader Compile Log: %s\n", status == GL_TRUE, buffer);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLuint tex;
    glGenTextures(1, &tex);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char* image = SOIL_load_image("textures/keven.png", &width, &height, 0, SOIL_LOAD_RGBA);
    if (image == NULL) {printf("Texture failed to load: %s", SOIL_last_result()); exit(1);}
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glGenerateMipmap(GL_TEXTURE_2D);
    //glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0); OPTIONAL, default is 0 already, only need if multiple texture layer.

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float vertices[] =
    {
        -0.5, -0.5, -0.5,   1.0, 1.0,
        -0.5, 0.5, -0.5,    1.0, 0,
        0.5, 0.5, -0.5,     0, 0,
        0.5, -0.5, -0.5,    0, 1.0, 

        -0.5, -0.5, 0.5,    1.0, 1.0,
        -0.5, 0.5, 0.5,     1.0, 0,
        -0.5, 0.5, -0.5,    0, 0,
        -0.5, -0.5, -0.5,   0, 1.0, 

        0.5, -0.5, 0.5,     1.0, 1.0,
        0.5, 0.5, 0.5,      1.0, 0,
        -0.5, 0.5, 0.5,     0, 0,
        -0.5, -0.5, 0.5,    0, 1.0, 

        0.5, -0.5, -0.5,    1.0, 1.0,
        0.5, 0.5, -0.5,     1.0, 0,
        0.5, 0.5, 0.5,      0, 0,
        0.5, -0.5, 0.5,     0, 1.0, 

        -0.5, 0.5, -0.5,    1.0, 1.0,
        -0.5, 0.5, 0.5,     1.0, 0,
        0.5, 0.5, 0.5,      0, 0,
        0.5, 0.5, -0.5,     0, 1.0, 

        -0.5, -0.5, 0.5,    1.0, 1.0,
        -0.5, -0.5, -0.5,   1.0, 0,
        0.5, -0.5, -0.5,    0, 0,
        0.5, -0.5, 0.5,     0, 1.0, 
    };

    GLuint elements[] = 
    {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    GLuint vbo;
    glGenBuffers(1, &vbo); //Make 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Set VBO active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Set VBO Data

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    GLint texcoAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glVertexAttribPointer(texcoAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(texcoAttrib);

    mat4 trans;
    glm_mat4_identity(trans);
    vec3 axis = {0.33f, 1.0f, 0.0f};
    glm_rotate(trans, glm_rad(180.0f), axis);
    
    vec3 cam = {0.0f, 0.0f, 3.0f};
    vec3 target = {0.0f, 0.0f, 0.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    mat4 view;
    glm_lookat(cam, target, up, view);

    mat4 proj;
    glm_perspective(glm_rad(45.0f), w/h, 1.0f, 10.0f, proj);

    GLint uniTrans = glGetUniformLocation(shaderProgram, "model"); 
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, (float*) trans);
    GLint viewTrans = glGetUniformLocation(shaderProgram, "view"); 
    glUniformMatrix4fv(viewTrans, 1, GL_FALSE, (float*) view);
    GLint projTrans = glGetUniformLocation(shaderProgram, "proj"); 
    glUniformMatrix4fv(projTrans, 1, GL_FALSE, (float*) proj);
    GLint colorUniform = glGetUniformLocation(shaderProgram, "color"); 
    glUniform4f(colorUniform, 1.0f, 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); //Retrieve window events

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE); //DEBUG EXIT COMMAND

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm_mat4_identity(trans);
        glm_rotate(trans, glm_rad(glfwGetTime()*100), axis);
        //vec4 scale = {sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime()), 1.0f};
        //glm_scale(trans, scale);
        glUniformMatrix4fv(uniTrans, 1, GL_FALSE, (float*) trans);
        
        glfwGetFramebufferSize(window, &w, &h);
        glm_perspective(glm_rad(45.0f), ((float)w) /h, 1.0f, 10.0f, proj);
        glUniformMatrix4fv(projTrans, 1, GL_FALSE, (float*) proj);
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window); //Swap back and front buffers
    }

    glfwTerminate();
    printf("RCGE terminated.");
    return 0;
}