#ifndef RCGE_WINDOW_H
#define RCGE_WINDOW_H
#include <stdbool.h>

typedef struct rcge_window_CDT* rcge_window;
typedef void (*rcge_start_callback)(rcge_window);
typedef void (*rcge_update_callback)(rcge_window, double);
typedef void (*rcge_resize_callback)(rcge_window, int, int);

rcge_window rcge_window_create(int width, int height, const char* title, bool resizable);
void rcge_window_run(rcge_window window, rcge_start_callback start_cb, rcge_update_callback update_cb, rcge_resize_callback resize_cb);
float rcge_window_ratio(rcge_window window);
void rcge_window_stop(rcge_window window);

void* rcge_window_raw_pointer(rcge_window window);

#endif