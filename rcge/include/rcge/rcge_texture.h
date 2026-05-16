#ifndef RCGE_TEXTURE_H
#define RCGE_TEXTURE_H

typedef struct rcge_texture_CDT* rcge_texture;
typedef enum {TEX_REPEAT, TEX_MIRRORED_REPEAT, TEX_CLAMP_TO_EDGE, TEX_CLAMP_TO_BORDER} rcge_texture_wrap_type;
typedef enum {TEX_LINEAR, TEX_NEAREST} rcge_texture_filter_type;

rcge_texture rcge_texture_create(char* path, rcge_texture_wrap_type wrap, rcge_texture_filter_type filter);
void rcge_texture_use(rcge_texture texture);
void rcge_texture_delete(rcge_texture texture);

#endif