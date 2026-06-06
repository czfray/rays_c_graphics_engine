cmake_minimum_required(VERSION 3.15)
project(rcgeapp LANGUAGES C)
set(SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

#make app
set(EXE_NAME app)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
add_executable(${EXE_NAME} ${SRC_FILES})

target_include_directories(${EXE_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/cglm/include
)

target_link_libraries(${EXE_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/lib/librcge.a
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
)

target_compile_options(${EXE_NAME} PRIVATE -O2)
target_link_options(${EXE_NAME} PRIVATE -mwindows)

add_custom_command(
    TARGET ${EXE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
        $<TARGET_FILE_DIR:${EXE_NAME}>
)

add_custom_command(
    TARGET ${EXE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:${EXE_NAME}>/textures
)

add_custom_command(
    TARGET ${EXE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${EXE_NAME}>/shaders
)

#make app_debug
set(DEBUG_EXE_NAME app_debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${DEBUG_EXE_NAME} ${SRC_FILES})

target_include_directories(${DEBUG_EXE_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/cglm/include
)

target_link_libraries(${DEBUG_EXE_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rcge/lib/librcge.a
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
)

#cmake -G "MinGW Makefiles" ..