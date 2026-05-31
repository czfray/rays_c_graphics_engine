#ifndef RCGE_ELEMENT_H
#define RCGE_ELEMENT_H
#include <stdbool.h>

typedef struct rcge_element_CDT* rcge_element;
typedef void (*rcge_element_start_callback)(rcge_element);
typedef void (*rcge_element_status_callback)(rcge_element, bool);
typedef void (*rcge_element_update_callback)(rcge_element, double);
typedef void (*rcge_element_delete_callback)(rcge_element);

rcge_element rcge_element_create(unsigned int comp_no, rcge_element_start_callback start_cb, rcge_element_status_callback enable_cb, rcge_element_update_callback update_cb, rcge_element_delete_callback delete_cb);
void rcge_element_attach(rcge_element element, unsigned int index, void* comp);
void rcge_element_start(rcge_element element);
void rcge_element_update(rcge_element element, double delta_time);
void rcge_element_enable(rcge_element element, bool enable);
bool rcge_element_status(rcge_element element);
void* rcge_element_comp_get(rcge_element element, unsigned int index);
void rcge_element_delete(rcge_element element);

typedef struct rcge_element_manager_CDT* rcge_element_manager;
rcge_element_manager rcge_element_manager_create(unsigned int buffer_size);
unsigned int rcge_element_manager_attach(rcge_element_manager manager, rcge_element element);
rcge_element rcge_element_manager_element_get(rcge_element_manager manager, unsigned int index);
void rcge_element_manager_update(rcge_element_manager manager, double delta_time);
void rcge_element_manager_delete(rcge_element_manager manager);

#endif