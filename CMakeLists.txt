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
message(STATUS "Started CMake for ${KONTO_EDITOR} v${PROJECT_VERSION}...\n")

configure_file(assets/config/editor.ini editor.ini COPYONLY)
configure_file(assets/textures/texture.jpg assets/textures/texture.jpg COPYONLY)

configure_file(src/shaders/flat.glsl assets/shaders/flat.glsl COPYONLY)
configure_file(src/shaders/basic.glsl assets/shaders/basic.glsl COPYONLY)
configure_file(src/shaders/2D/quad.glsl assets/shaders/2D/quad.glsl COPYONLY)
configure_file(src/shaders/2D/line.glsl assets/shaders/2D/line.glsl COPYONLY)
configure_file(src/shaders/2D/circle.glsl assets/shaders/2D/circle.glsl COPYONLY)

add_library(
    ${KONTO_BEANS}
    src/konto/konto.cc
    src/konto/core/uuid.cc
    src/konto/core/event.cc
    src/konto/core/scene.cc
    src/konto/core/camera.cc
    src/konto/serialization/scene.cc
    src/konto/serialization/components.cc
    src/konto/serialization/serialization.cc
    include/konto.h
    include/konto/core/uuid.h
    include/konto/core/scene.h
    include/konto/core/input.h
    include/konto/core/event.h
    include/konto/core/entity.h
    include/konto/core/camera.h
    include/konto/core/timestep.h
    include/konto/components/common.h
    include/konto/components/physics.h
    include/konto/components/renderer2d.h
    include/konto/serialization/scene.h
    include/konto/serialization/components.h
    include/konto/serialization/serialization.h
)

target_include_directories(${KONTO_BEANS} PUBLIC deps)
target_include_directories(${KONTO_BEANS} PUBLIC include)

add_executable(
    ${KONTO_EDITOR}
    src/editor/editor.h
    src/editor/editor.cc
    src/editor/context.h
    src/editor/window.h
    src/editor/window.cc
    src/editor/application.h
    src/editor/application.cc
    src/editor/menus/main.h
    src/editor/menus/main.cc
    src/editor/menus/dialogs.h
    src/editor/menus/dialogs.cc
    src/editor/panels/scene.h
    src/editor/panels/scene.cc
    src/editor/panels/viewport.h
    src/editor/panels/viewport.cc
    src/editor/panels/inspector.h
    src/editor/panels/inspector.cc
    src/editor/panels/simulation.h
    src/editor/panels/simulation.cc
)

target_include_directories(${KONTO_EDITOR} PUBLIC src)
target_include_directories(${KONTO_EDITOR} PUBLIC deps)
target_include_directories(${KONTO_EDITOR} PUBLIC include)

set(KONTOMIRE_BUILD_TEST
    OFF
    CACHE BOOL "" FORCE)
set(KONTOMIRE_BUILD_PLAYGROUND
    OFF
    CACHE BOOL "" FORCE)
set(FLATBUFFERS_INSTALL
    OFF
    CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_FLATC
    OFF
    CACHE BOOL "" FORCE)
set(FLATBUFFERS_BUILD_FLATHASH
    OFF
    CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED
    OFF
    CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS
    OFF
    CACHE BOOL "" FORCE)

add_subdirectory(deps/entt)
add_subdirectory(deps/glfw)
add_subdirectory(deps/imgui)
add_subdirectory(deps/box2d)
add_subdirectory(deps/kontomire)
add_subdirectory(deps/flatbuffers)
add_subdirectory(deps/nativefiledialog)

target_link_libraries(${KONTO_BEANS} box2d)
target_link_libraries(${KONTO_BEANS} kontomire)
target_link_libraries(${KONTO_BEANS} EnTT::EnTT)
target_link_libraries(${KONTO_BEANS} flatbuffers)

target_link_libraries(${KONTO_EDITOR} nfd)
target_link_libraries(${KONTO_EDITOR} glfw)
target_link_libraries(${KONTO_EDITOR} imgui)
target_link_libraries(${KONTO_EDITOR} ${KONTO_BEANS})
