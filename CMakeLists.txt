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

add_library(
    ${KONTO_BEANS}
    ${PROJECT_SOURCE_DIR}/include/konto.h
    ${PROJECT_SOURCE_DIR}/src/konto/konto.cc
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
