cmake_minimum_required(VERSION 3.10)

set(KONTO_BEANS "konto")
set(KONTO_EDITOR "konto-editor")

project(${KONTO_BEANS} VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        "Debug"
        CACHE
        STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wconversion")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

message(STATUS "Started CMake for ${KONTO_BEANS} v${PROJECT_VERSION}...\n")

configure_file(${PROJECT_SOURCE_DIR}/assets/config/editor.ini editor.ini COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/assets/textures/texture.jpg assets/textures/texture.jpg COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/assets/shaders/flat-color.glsl assets/shaders/flat-color.glsl COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/assets/shaders/basic-texture.glsl assets/shaders/basic-texture.glsl COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/assets/shaders/2D/quad.glsl assets/shaders/2D/quad.glsl COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/assets/shaders/2D/line.glsl assets/shaders/2D/line.glsl COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/assets/shaders/2D/circle.glsl assets/shaders/2D/circle.glsl COPYONLY)

add_library(
    ${KONTO_BEANS}
    ${PROJECT_SOURCE_DIR}/src/konto/konto.cc
    ${PROJECT_SOURCE_DIR}/src/konto/scene/scene.cc
    ${PROJECT_SOURCE_DIR}/include/konto.h
    ${PROJECT_SOURCE_DIR}/include/konto/scene/scene.h
)

target_include_directories(${KONTO_BEANS} PUBLIC ${PROJECT_SOURCE_DIR}/deps)
target_include_directories(${KONTO_BEANS} PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(
    ${KONTO_EDITOR}
    ${PROJECT_SOURCE_DIR}/src/editor/editor.cc
)

target_include_directories(${KONTO_EDITOR} PUBLIC ${PROJECT_SOURCE_DIR}/deps)
target_include_directories(${KONTO_EDITOR} PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(KONTOMIRE_BUILD_TEST
    OFF
    CACHE BOOL "" FORCE)
set(KONTOMIRE_BUILD_PLAYGROUND
    OFF
    CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/imgui)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/kontomire)

target_link_libraries(${KONTO_BEANS} kontomire)

target_link_libraries(${KONTO_EDITOR} glfw)
target_link_libraries(${KONTO_EDITOR} imgui)
target_link_libraries(${KONTO_EDITOR} ${KONTO_BEANS})
