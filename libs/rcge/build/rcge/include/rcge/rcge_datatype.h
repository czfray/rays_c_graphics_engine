#ifndef RCGE_DATATYPE_H
#define RCGE_DATATYPE_H

/** 
 * @file rcge_datatype.h
 * @brief Datatype enums for RCGE.
 * 
 * @defgroup datatypes Datatypes
 * 
 * This module allows datatypes to be inputted in parameters for RCGE functions.
**/

/**
 * @ingroup datatypes
 * @brief Datatypes for RCGE
**/
typedef enum {
    DATATYPE_BYTE, ///< Byte
    DATATYPE_UNSIGNED_BYTE, ///< Unsigned Byte
    DATATYPE_SHORT, ///< Short
    DATATYPE_UNSIGNED_SHORT, ///< Unsigned Short 
    DATATYPE_INT, ///< Integer
    DATATYPE_UNSIGNED_INT, ///< Unsigned Integer 
    DATATYPE_FLOAT, ///< Float
    DATATYPE_DOUBLE, ///< Double
} rcge_datatype;

/**
 * @internal
 * @warning This is an RCGE Internal Function.
 * @endinternal
 */
unsigned int rcge_datatype_to_gl(rcge_datatype datatype);

/**
 * @internal
 * @warning This is an RCGE Internal Function.
 * @endinternal
 */
unsigned int rcge_datatype_size(rcge_datatype datatype);

#endif