cmake_minimum_required(VERSION 3.15)
project(rays_c_graphics_engine LANGUAGES C)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c)
add_library(rcge ${SRC_FILES} ${GLAD_SRC})
target_include_directories(rcge 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/cglm/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/stbi/include
)
target_link_libraries(rcge 
    PRIVATE 
        opengl32 
        gdi32
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib/libglfw3.a
)

#cmake -G "MinGW Makefiles" ..