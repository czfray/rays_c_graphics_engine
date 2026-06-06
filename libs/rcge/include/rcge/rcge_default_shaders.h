#ifndef RCGE_DEFAULT_SHADERS_H
#define RCGE_DEFAULT_SHADERS_H
/**
 * @file rcge_default_shaders.h
 * @brief Default shaders.
 * 
 * @defgroup def_shaders Default Shaders
 * 
 * This module provide default shaders. Shaders creation can sometimes be tricky, so let RCGE do it for you.
**/

#include <rcge/rcge_shader.h>

/**
 * @ingroup def_shaders
 * Position attribute index of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_POSITION_ATTRIB 0

/**
 * @ingroup def_shaders
 * Texture coordinate attribute index of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_TEXCOORD_ATTRIB 1

/**
 * @ingroup def_shaders
 * Model matrix uniform index of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_MODEL_UNF 0

/**
 * @ingroup def_shaders
 * View matrix uniform index of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_VIEW_UNF 1

/**
 * @ingroup def_shaders
 * Projection matrix uniform index of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_PROJ_UNF 2

/**
 * @ingroup def_shaders
 * Mesh color uniform index of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_COLOR_UNF 3

/**
 * @ingroup def_shaders
 * Texture uniform index of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_TEXTURE_UNF 4

/**
 * @ingroup def_shaders
 * Color out buffer location of the default unlit shader.
**/
#define RCGE_DEF_UNLIT_SHADER_COLOROUT_LOC 0

/**
 * @ingroup def_shaders
 * @brief Creates the default unlit shader.
 * @return A newly created default unlit shader.
**/
rcge_shader rcge_default_unlit_shader_create(void);

#endif