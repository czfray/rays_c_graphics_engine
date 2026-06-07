#ifndef RCGE_H
#define RCGE_H

/**
 * @mainpage Ray's C Graphics Engine (RCGE)
 * 
 * An OpenGL-based graphic engine written in plain C. Aims to be as simple and as customisable as possible.
 *
 * @section guidetoc RCGE Usage Guide
 * 
 * **In Progress...**
 * 
 * @section doctoc Detailed Documentation
 * **Modules** \n
 * @ref master \n
 * @ref shaders \n
 * @ref textures \n
 * @ref transforms \n
 * @ref elements \n
 * @ref cameras \n
 * @ref io \n
 * @ref datatypes \n
 * @ref codes \n
 * \n
 * **Pre-built Shaders** \n
 * @ref def_shaders \n
 * \n
 * **Pre-built Element Components** \n
 * @ref meshes \n
 * @ref cameras \n
 * \n
 * **Pre-built Elements** \n
 * @ref singlemesh \n
 * \n
 * 
 * @section info Creation Info
 * **Author**: Chan Ray \n
 * **Version**: 0.1.0 \n
 * **Version Release Date**: 2026-06-08 \n
 * **Project Start Date**: 2026-05-10\n
 * <a href="https://github.com/czfray/rays_c_graphics_engine">**Source Code Link**</a>
 * 
 * Proudly hand written from scratch, without AI! Vibe coding is for noobs.
**/

/**
 * @file rcge.h
 * @brief RCGE API main header.
 * @note Only #include this in your code to use the engine. Including other RCGE headers is unnecessary.
**/

#include <rcge/rcge_master.h>
#include <rcge/rcge_codes.h>
#include <rcge/rcge_io.h>
#include <rcge/rcge_datatype.h>
#include <rcge/rcge_shader.h>
#include <rcge/rcge_texture.h>
#include <rcge/rcge_transform.h>
#include <rcge/rcge_mesh.h>
#include <rcge/rcge_camera.h>
#include <rcge/rcge_element.h>
#include <rcge/rcge_default_shaders.h>
#include <rcge/rcge_singlemesh_element.h>

/*
 * @page guide01 01 Getting Started
 * @brief This section describe how to start using RCGE.
*/

#endif