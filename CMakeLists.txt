cmake_minimum_required(VERSION 3.22)

project(MathPlotter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Dependency build options
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "Build dependency tests" FORCE)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "Build SFML audio module" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build SFML network module" FORCE)

set(ENABLE_OPENMP OFF CACHE BOOL "Enable muParser OpenMP support" FORCE)
set(ENABLE_SAMPLES OFF CACHE BOOL "Build muParser samples" FORCE)

set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Find an installed SFML" FORCE)
set(IMGUI_SFML_BUILD_EXAMPLES OFF CACHE BOOL "Build ImGui-SFML examples" FORCE)
set(IMGUI_SFML_BUILD_TESTING OFF CACHE BOOL "Build ImGui-SFML tests" FORCE)

# Dependencies
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    imgui_sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    muparser
    GIT_REPOSITORY https://github.com/beltoforion/muparser.git
    GIT_TAG v2.3.5
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(sfml)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR "${imgui_SOURCE_DIR}" CACHE PATH "Dear ImGui source directory" FORCE)

FetchContent_MakeAvailable(imgui_sfml)
FetchContent_MakeAvailable(muparser)

# Application
add_executable(
    mathplotter
    src/application.cpp
    src/cameraController.cpp
    src/functionRenderer.cpp
    src/gridRenderer.cpp
    src/main.cpp
    src/theme.cpp
    src/userInterface.cpp
)

target_include_directories(
    mathplotter
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(
    mathplotter
    PRIVATE
        SFML::Graphics
        ImGui-SFML::ImGui-SFML
        muparser
)

if(MSVC)
    target_compile_options(mathplotter PRIVATE /W4 /WX)
else()
    target_compile_options(
        mathplotter
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
    )
endif()