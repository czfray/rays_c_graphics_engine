cmake_minimum_required(VERSION 3.15)
project(rcgeapp LANGUAGES C)
set(SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

#make app
set(EXE_NAME app)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(${EXE_NAME} ${SRC_FILES})

target_include_directories(${EXE_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/include
)

target_link_libraries(${EXE_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/bin/librcge.a
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
)

target_compile_options(${EXE_NAME} PRIVATE -O2)
target_link_options(${EXE_NAME} PRIVATE -mwindows)

add_custom_target(copy_build_files ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/build

    COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/build

    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${EXE_NAME}>
        ${CMAKE_CURRENT_SOURCE_DIR}/build

    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/icon.png
        ${CMAKE_CURRENT_SOURCE_DIR}/build/icon.png

    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
        ${CMAKE_CURRENT_SOURCE_DIR}/build

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/textures
        ${CMAKE_CURRENT_SOURCE_DIR}/build/textures
        
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_SOURCE_DIR}/build/shaders
)

add_dependencies(copy_build_files ${EXE_NAME})

#make app_debug
set(DEBUG_EXE_NAME app_debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${DEBUG_EXE_NAME} ${SRC_FILES})

target_include_directories(${DEBUG_EXE_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/include
)

target_link_libraries(${DEBUG_EXE_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/bin/librcge.a
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
)

#cmake -G "MinGW Makefiles" ..