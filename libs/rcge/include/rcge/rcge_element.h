#ifndef RCGE_ELEMENT_H
#define RCGE_ELEMENT_H

/** 
 * @file rcge_element.h
 * @brief Elements (RCGE object) management.
 * 
 * @defgroup elements Elements and Element Managers
 * 
 * @subsection elements_obj Elements
 * An element groups multiple components (like meshes or sound sources) together, allowing a more organised way to manage objects that work together.
 * 
 * e.g. If 6 meshes makes up a player model, you can make a "player" element, attach 6 meshes to the element, and manage them together.
 * Originally, you have to call @ref rcge_mesh_draw for every element per frame. It makes the code very messy. 
 * 
 * If you manage them under one element, you can group the draws in one update callback and simply call 1 function @ref rcge_element_update per frame, making the code way cleaner.
 * 
 * By adding component deletion calls in the deletion callback of an element, components can be automatically deleted when their parent element are deleted as well.
 *
 * @subsection elements_manager Element Manager
 * If you have created a lot of elements, it becomes tedious to call @ref rcge_element_update for all element every frame. You do not want 100 lines of the same code right?
 *  
 * An element manager groups elements together, so that you do not have to update every element one by one per frame. 
 * Instead, after you create an element, you could simply attach the element to a manager, and simply call a single function @ref rcge_element_manager_update per frame to update all elements. 
 * This also allows the automatic deletion of elements in the manager when the manager itself is deleted.
 *
**/

#include <stdbool.h>

/**
 * @ingroup elements
 * Datatype representing an element
**/
typedef struct rcge_element_CDT* rcge_element;

/**
 * @ingroup elements
 * @brief Function pointer representing callbacks executed when an element is first enabled.
 * @param element The element that just first got enabled.
**/
typedef void (*rcge_element_start_callback)(rcge_element);

/**
 * @ingroup elements
 * @brief Function pointer representing callbacks executed when an element is enabled or disabled.
 * @param element The element that just got enabled/disabled.
 * @param status The status of the element (enabled or disabled).
**/
typedef void (*rcge_element_status_callback)(rcge_element, bool);

/**
 * @ingroup elements
 * @brief Function pointer representing callbacks executed when an element is updated per frame.
 * @param element The element that is updating.
 * @param delta_time The time passed from the last frame update.
**/
typedef void (*rcge_element_update_callback)(rcge_element, double);

/**
 * @ingroup elements
 * @brief Function pointer representing callbacks executed when an element is deleted.
 * @param element The element that is deleted.
**/
typedef void (*rcge_element_delete_callback)(rcge_element);

/**
 * @ingroup elements
 * @brief Creates an element.
 * @param[in] comp_no Number of components the element to be created has.
 * @param[in] start_cb The function to be called when the element to be created is first enabled. See @ref rcge_element_start_callback.
 * @param[in] enable_cb The function to be called when the element to be created is enabled or disabled. See @ref rcge_element_status_callback.
 * @param[in] update_cb The function to be called when the element to be created is updated per frame. See @ref rcge_element_update_callback.
 * @param[in] delete_cb The function to be called when the element to be created is deleted. See @ref rcge_element_delete_callback.
 * @return The element created, NULL if failed.
**/
rcge_element rcge_element_create(unsigned int comp_no, rcge_element_start_callback start_cb, rcge_element_status_callback enable_cb, rcge_element_update_callback update_cb, rcge_element_delete_callback delete_cb);

/**
 * @ingroup elements
 * @brief Attaches a component to an element.
 * @note Two components cannot share the same index. 
 * @param[in] element The element to be attached.
 * @param[in] index The index to assign to for the component to attach. It must be a non-negative int smaller than the total number of components the element has.
 * @param[in] comp The component to attach.
**/
void rcge_element_attach(rcge_element element, unsigned int index, void* comp);

/**
 * @ingroup elements
 * @brief Enable an element for the first time after it's initialisation.
 * @note Only call once after attaching all components have been attached to the element with @ref rcge_element_attach.
 * @param[in] element The element to enable.
**/
void rcge_element_start(rcge_element element);

/**
 * @ingroup elements
 * @brief Updates an element. Call this per frame.
 * @note If you created this element with a element manager, you do not have to call update. The element manager updates the element for you per frame.
 * @param[in] element The element to update.
 * @param[in] delta_time Time passed from the last frame.
**/
void rcge_element_update(rcge_element element, double delta_time);

/**
 * @ingroup elements
 * @brief Enable or disable an element. When an element is disabled, it cannot be updated even if @ref rcge_element_update is called.
 * @param[in] element The element to enable or disable.
 * @param[in] enable Whether you want to enable or disable the element.
**/
void rcge_element_enable(rcge_element element, bool enable);

/**
 * @ingroup elements
 * @brief Get the status of the element (enabled or disabled).
 * @param[in] element The element to access.
**/
bool rcge_element_status(rcge_element element);

/**
 * @ingroup elements
 * @brief Get a component from the element with the component's index.
 * @param[in] element The element to access.
 * @param[in] index The component index.
 * @return The component of index specified in the element, NULL if failed.
**/
void* rcge_element_comp_get(rcge_element element, unsigned int index);

/**
 * @ingroup elements
 * @brief Deletes an element.
 * 
 * Element deletion must be done before the program terminates. Prevent memory leaks.
 * 
 * @note - This function calls the element's delete callbacks. Please delete the components in the callback, so if the element is deleted, it's components are automatically deleted as well.
 * @note - If you created an object with a element manager, you do not have to call this. The element manager deletes the element for you when the program terminates.
 * @param[in] element The element to access.
**/
void rcge_element_delete(rcge_element element);

/**
 * @ingroup elements
 * Datatype representing an element manager. 
**/
typedef struct rcge_element_manager_CDT* rcge_element_manager;

/**
 * @ingroup elements
 * @brief Creates an element manager.
 * 
 * An element manager would increase in size as there are more elements attached to it. Each time the manager expands, it would increase by the buffer size you have set.
 * 
 * @param[in] buffer_size The buffer size you want for the element manager.
 * @return The element manager created, NULL if failed.
**/
rcge_element_manager rcge_element_manager_create(unsigned int buffer_size);

/**
 * @ingroup elements
 * @brief Attach an element to a specified element manager,
 * @param[in] manager The element manager to be attached.
 * @param[in] element The element to attach.
 * @return The index of the element in the manager, @ref RCGE_UINT_ERROR if failed.
**/
unsigned int rcge_element_manager_attach(rcge_element_manager manager, rcge_element element);

/**
 * @ingroup elements
 * @brief Get an element with it's index from a specified element manager.
 * @param[in] manager The element manager to access.
 * @param[in] index The index of the element to be accessed.
 * @return The target element, NULL if failed.
**/
rcge_element rcge_element_manager_element_get(rcge_element_manager manager, unsigned int index);

/**
 * @ingroup elements
 * @brief Update all the elements in an element manager.
 * @param[in] manager The element manager to update.
 * @param[in] delta_time Time passed from the last frame update.
**/
void rcge_element_manager_update(rcge_element_manager manager, double delta_time);

/**
 * @ingroup elements
 * @brief Deletes the element manager. Does element deletion for all elements in it as well.
 * 
 * Element manager deletion must be done before the program terminates. Prevents memory leaks.
 * 
 * @param[in] manager The element manager to delete.
**/
void rcge_element_manager_delete(rcge_element_manager manager);

#endif