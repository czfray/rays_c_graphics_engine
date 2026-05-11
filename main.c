#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
 * gcc main.c glad\src\glad.c -Iglfw\include -Iglad\include -Lglfw\lib -lglfw3 -lopengl32 -lgdi32 -o rcge
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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Ray's C Graphics Engine", NULL, NULL);
    glfwMakeContextCurrent(window);

    //Initialise GLAD (Manages function pointers)
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("GLAD failed to initialise.");
        return -1;
    }

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

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float vertices[] =
    {
        -0.5, 0.5,
        0.5, -0.5,
        -0.5, -0.5
    };

    GLuint vbo;
    glGenBuffers(1, &vbo); //Make 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Set VBO active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Set VBO Data

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    GLint uniColor = glGetUniformLocation(shaderProgram, "testColor");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); //Retrieve window events

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE); //DEBUG EXIT COMMAND

        glUniform3f(uniColor, fabs(sin(glfwGetTime())), fabs(sin(2*glfwGetTime() + 3.14f/2)), fabs(sin(4*glfwGetTime() + 3.14f)));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); //Swap back and front buffers
    }

    glfwTerminate();
    printf("RCGE terminated.");
    return 0;
}