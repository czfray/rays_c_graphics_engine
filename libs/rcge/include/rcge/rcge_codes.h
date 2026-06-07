#ifndef RCGE_CODES_H
#define RCGE_CODES_H

/** 
 * @file rcge_codes.h
 * @brief Return codes for RCGE.
 * 
 * @defgroup codes Special Return Codes 
 * 
 * This module allows special return codes, like error codes. 
 * 
 * i.e. Magic numbers are defined here.
**/

#include <math.h>

/**
 * @ingroup codes
 * Error code (Integer)
**/
#define RCGE_INT_ERROR INT_MIN

/**
 * @ingroup codes
 * Error code (Unsigned integer)
**/
#define RCGE_UINT_ERROR (unsigned int) -1

/**
 * @ingroup codes
 * Error code (Double)
**/
#define RCGE_DOUBLE_ERROR ((double) NAN)

/**
 * @ingroup codes
 * Error code (Float)
**/
#define RCGE_FLOAT_ERROR NAN

#endif