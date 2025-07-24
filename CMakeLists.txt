cmake_minimum_required(VERSION 3.10)
project(MiniGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Collect sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

# Build as a static library (or shared if you want)
add_library(MiniGL STATIC ${SOURCES})

# Include headers for anyone linking MiniGL
target_include_directories(MiniGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link dependencies PUBLIC so consumers get them
find_package(glfw3 REQUIRED)
target_link_libraries(MiniGL PUBLIC glfw)

if(UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(MiniGL PUBLIC OpenGL::GL dl m pthread)
endif()
