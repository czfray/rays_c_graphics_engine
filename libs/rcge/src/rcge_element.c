#include <rcge/rcge_element.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct rcge_element_CDT
{
    void** components;
    rcge_element_start_callback start_cb;
    rcge_element_status_callback enable_cb;
    rcge_element_update_callback update_cb;
    rcge_element_delete_callback delete_cb;
    bool enabled;
};

rcge_element rcge_element_create(unsigned int comp_no, rcge_element_start_callback start_cb, rcge_element_status_callback enable_cb, rcge_element_update_callback update_cb, rcge_element_delete_callback delete_cb)
{
    //TODO: Malloc validation blah blah
    rcge_element element = malloc(sizeof(*element));
    element->components = malloc(comp_no * sizeof(void*));
    element->start_cb = start_cb;
    element->update_cb = update_cb;
    element->enable_cb = enable_cb;
    element->delete_cb = delete_cb;
    element->enabled = false;

    //printf("[RCGE Element] Element created.\n");
    return element;
}

void rcge_element_attach(rcge_element element, unsigned int index, void* comp)
{
    //TODO: CHECK IF OUT OF RANGE
    if (element == NULL) {printf("[RCGE Element] Element component attach failed: element does not exist.\n"); return;}
    (element->components)[index] = comp;
    //printf("[RCGE Element] Element attached component at index %d.\n", index);
}

void rcge_element_start(rcge_element element)
{
    if (element == NULL) {printf("[RCGE Element] Element start failed: element does not exist.\n"); return;}
    rcge_element_start_callback start_cb = element->start_cb;
    if (start_cb != NULL) start_cb(element);
    rcge_element_enable(element, true);
}

void rcge_element_enable(rcge_element element, bool enable)
{
    if (enable == element->enabled) return;
    if (element == NULL) {printf("[RCGE Element] Element status set failed: element does not exist.\n"); return;}
    element->enabled = enable;
    rcge_element_status_callback status_cb = element->enable_cb;
    if (status_cb != NULL) status_cb(element, enable);
}

bool rcge_element_status(rcge_element element)
{
    if (element == NULL) {printf("[RCGE Element] Element status get failed: element does not exist.\n"); return false;}
    return element->enabled;
}

void rcge_element_update(rcge_element element, double delta_time)
{
    if (element == NULL) {printf("[RCGE Element] Element update failed: element does not exist.\n"); return;}
    if (!element->enabled) return;
    rcge_element_update_callback update_cb = element->update_cb;
    if (update_cb != NULL) update_cb(element, delta_time);
}

void* rcge_element_comp_get(rcge_element element, unsigned int index)
{
    //TODO: SEE IF OUT OF RANGE
    if (element == NULL) {printf("[RCGE Element] Element component get failed: element does not exist.\n"); return NULL;}
    return (element->components)[index];
}

void rcge_element_delete(rcge_element element)
{
    if (element == NULL) {printf("[RCGE Element] Element delete failed: element does not exist.\n"); return;}
    rcge_element_delete_callback delete_cb = element->delete_cb;
    if (delete_cb != NULL) delete_cb(element);

    free(element->components);
    free(element);
    //printf("[RCGE Element] Element deleted.\n");
}

struct rcge_element_manager_CDT
{
    rcge_element* elements;
    unsigned int buffer_size;
    unsigned int max_count;
    unsigned int count;
};

rcge_element_manager rcge_element_manager_create(unsigned int buffer_size)
{
    //TODO: MALLOC CHECKS AND SHIT
    rcge_element_manager manager = malloc(sizeof(*manager));
    manager->elements = malloc(buffer_size * sizeof(rcge_element));
    manager->buffer_size = buffer_size;
    manager->count = 0;
    manager->max_count = buffer_size;

    printf("[RCGE Element Manager] Element manager created.\n");
    return manager;
}

unsigned int rcge_element_manager_attach(rcge_element_manager manager, rcge_element element)
{
    if (manager == NULL) {printf("[RCGE Element Manager] Element manager element attach failed: element manager does not exist.\n"); return 999999;}
    unsigned int count = manager->count;
    unsigned int max_count = manager->max_count;
    if (count + 1 > max_count)
    {
        unsigned int new_max_count = max_count + manager->buffer_size;
        manager->elements = realloc(manager->elements, new_max_count * sizeof(rcge_element)); //TODO CHECK REALLOC FAIL
        manager->max_count = new_max_count;
        printf("[RCGE Element Manager] Element manager elements max count increased to %d.\n", new_max_count);
    }
    (manager->elements)[count] = element;
    manager->count = count + 1;
    return count;
}

rcge_element rcge_element_manager_element_get(rcge_element_manager manager, unsigned int index)
{
    if (manager == NULL) {printf("[RCGE Element Manager] Element manager element get failed: element manager does not exist.\n"); return NULL;}
    //TODO check if out of range
    return (manager->elements)[index];
}

void rcge_element_manager_update(rcge_element_manager manager, double delta_time)
{
    if (manager == NULL) {printf("[RCGE Element Manager] Element manager update failed: element manager does not exist.\n"); return;}
    for (int i = 0; i < manager->count; i++) {rcge_element_update((manager->elements)[i], delta_time);}
}

void rcge_element_manager_delete(rcge_element_manager manager)
{
    if (manager == NULL) {printf("[RCGE Element Manager] Element manager delete failed: element manager does not exist.\n"); return;}
    for (int i = 0; i < manager->count; i++) {rcge_element_delete((manager->elements)[i]);}
    free(manager->elements);
    free(manager);
    printf("[RCGE Element Manager] Element manager deleted.\n");
}