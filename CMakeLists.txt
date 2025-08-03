cmake_minimum_required(VERSION 3.10)
project(MiniGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Collect sources
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Build as a static library
add_library(MiniGL STATIC ${LIB_SOURCES})
target_include_directories(MiniGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(APP_SOURCES src/main.cpp)

# Build as an Executable
add_executable(MiniGLApp ${APP_SOURCES})
target_link_libraries(MiniGLApp PRIVATE MiniGL)
