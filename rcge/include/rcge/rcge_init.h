#ifndef RCGE_INIT_H
#define RCGE_INIT_H
#include <stdbool.h>

/** 
 * @file rcge_init.h
 * @brief Engine initialisation and termination.
 * 
 * @defgroup init Initialiser
 * @brief Engine initialisation and termination.
 * 
 * This module handles the initialisation and termination of RCGE.
 * @note @ref rcge_init and @ref rcge_terminate must be called at the start and end of program respectively.
**/

/**
 * @ingroup init
 * @brief Initialises RCGE.
 * 
 * Must be called at the start of `main()`.
**/
bool rcge_init(void);

/**
 * @ingroup init
 * @brief Terminates RCGE.
 * 
 * Must be called at the end of `main()`.
**/
void rcge_terminate(void);

/**
 * @ingroup init
 * @brief Retrieves status of RCGE.
 * @return true if RCGE is initialised, false otherwise.
**/
bool rcge_status(void );

#endif