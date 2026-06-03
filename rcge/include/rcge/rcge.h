#ifndef RCGE_H
#define RCGE_H

/**
 * @mainpage Ray's C Graphics Engine (RCGE)
 * @brief An OpenGL-based graphic engine written in plain C. Aims to be as simple and as customisable as possible.
 *
 * @section guidetoc RCGE Usage Guide\n
 * @ref guide01
 * 
 * @section doctoc Detailed Documentation\n
 * - @ref init \n
 * - @ref windows \n
 * - @ref shaders \n
 * - @ref textures \n
 * - @ref transforms \n
 * - @ref meshes \n
 * - @ref elements \n
 * - @ref cameras \n
 * - @ref io \n
 * - @ref datatypes \n
 * 
 * @section info Creation Info\n
 * @author Chan Ray
 * @version 0.1.0
 * @date 2026-05-10
 * 
 * Proudly hand written from scratch, without AI! Vibe coding is for noobs dude.
**/

/**
 * @file rcge.h
 * @brief RCGE API main header.
 * @note Only #include this in your code to use the engine. Including other RCGE headers is unnecessary.
**/

#include <rcge/rcge_init.h>
#include <rcge/rcge_io.h>
#include <rcge/rcge_datatype.h>
#include <rcge/rcge_window.h>
#include <rcge/rcge_shader.h>
#include <rcge/rcge_texture.h>
#include <rcge/rcge_transform.h>
#include <rcge/rcge_mesh.h>
#include <rcge/rcge_camera.h>
#include <rcge/rcge_element.h>
#include <rcge/rcge_singlemesh_element.h>

/** 
 * @page guide01 01 Getting Started
 * @brief This section describe how to start using RCGE.
**/

#endif