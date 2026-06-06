#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <rcge/rcge_texture.h>
#include <rcge/rcge_io.h>

#include <stdio.h>
#include <stdlib.h>

struct rcge_texture_CDT
{
    GLuint gl_texture;
};

GLenum gl_wrap_type(rcge_texture_wrap_type type)
{
    switch(type)
    {
        case TEX_CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
        case TEX_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
        case TEX_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
        case TEX_REPEAT : return GL_REPEAT;
    }
    return GL_REPEAT;
}

GLenum gl_filter_type(rcge_texture_filter_type type)
{
    return (type == TEX_LINEAR? GL_LINEAR: GL_NEAREST);
}

rcge_texture rcge_texture_create_file(char* path, rcge_texture_wrap_type wrap, rcge_texture_filter_type filter)
{
    int width, height, channel_no;
    unsigned char* image = rcge_io_read_image(path, &width, &height, &channel_no, 4);
    if (image == NULL) {printf("[RCGE Texture] Texture failed to load (%s): image load failed.\n", path); return NULL;}
    rcge_texture tex = rcge_texture_create(image, width, height, wrap, filter);
    rcge_io_free_image(image);
    return tex;
    
}

rcge_texture rcge_texture_create(unsigned char* image, int width, int height, rcge_texture_wrap_type wrap, rcge_texture_filter_type filter)
{
    GLuint gl_texture;
    glGenTextures(1, &gl_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gl_texture);

    GLenum gl_wrap = gl_wrap_type(wrap);
    GLenum gl_filter = gl_filter_type(filter);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    //TODO: More checks could be done here?

    rcge_texture texture = malloc(sizeof(*texture)); //TODO: MALLOC CHECK?
    texture->gl_texture = gl_texture;
    printf("[RCGE Texture] Texture %d loaded. \n", gl_texture);
    return texture;
}

void rcge_texture_use(rcge_texture texture)
{
    if (texture == NULL) {printf("[RCGE Texture] Texture use failed: texture does not exist.\n"); return;}
    GLint gl_texture = texture->gl_texture;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gl_texture);
    //printf("[RCGE Texture] Texture %d now using.\n", gl_texture);
}

void rcge_texture_delete(rcge_texture texture)
{
    if (texture == NULL) {printf("[RCGE Texture] Texture delete failed: texture does not exist.\n"); return;}
    GLuint gl_texture = texture->gl_texture;
    glDeleteShader(gl_texture);
    free(texture);
    printf("[RCGE Texture] Texture %d deleted.\n", gl_texture);
}
