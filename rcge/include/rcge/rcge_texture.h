#ifndef RCGE_TEXTURE_H
#define RCGE_TEXTURE_H

/** 
 * @file rcge_texture.h
 * @brief Image texture management.
 * 
 * @defgroup textures Textures
 * @brief Image texture management.
 * 
 * This module allows the creation and usage of image textures.
 * Image textures can be rendered on meshes.
**/

/**
 * @ingroup textures
 * Datatype representing an image texture.
**/
typedef struct rcge_texture_CDT* rcge_texture;

/**
 * @ingroup textures
 * @enum rcge_texture_wrap_type
 * @brief Type of texture wrapping methods.
**/
typedef enum 
{
    TEX_REPEAT, ///< Repeats the texture.
    TEX_MIRRORED_REPEAT, ///< Repeats the texture but mirrors the image with each repeat.
    TEX_CLAMP_TO_EDGE, ///< Stretched edge pattern.
    TEX_CLAMP_TO_BORDER ///< Blank color outside border.
} rcge_texture_wrap_type;

/**
 * @ingroup textures
 * @enum rcge_texture_filter_type
 * @brief Type of texture filter methods.
**/
typedef enum 
{
    TEX_LINEAR, ///< Blocky texture and can see individual pixels.
    TEX_NEAREST ///< Smooth texture and individual pixels are blurred.
} rcge_texture_filter_type;

/**
 * @ingroup textures
 * @brief Creates an image texture from an image file.
 * @param[in] path Relative path of the image file to be used for creating the texture.
 * @param[in] wrap The wrapping method to use for the texture. See @ref rcge_texture_wrap_type for what can be put here.
 * @param[in] filter The filter method to use for the texture. See @ref rcge_texture_filter_type for what can be put here.
 * @return The texture created, NULL if failed.
 * @note Image file is read from the bottom **RIGHT** pixel to the upper **LEFT** pixel.
**/
rcge_texture rcge_texture_create(char* path, rcge_texture_wrap_type wrap, rcge_texture_filter_type filter);

/**
 * @ingroup textures
 * @brief Set the texture to be the active one.
 * @param[in] texture The texture to be used.
**/
void rcge_texture_use(rcge_texture texture);

/**
 * @ingroup textures
 * @brief Deletes the image texture.
 * Texture deletion must be called at the end of the program. This prevents memory leaks.
 * @param[in] texture The texture to be deleted.
**/
void rcge_texture_delete(rcge_texture texture);

#endif