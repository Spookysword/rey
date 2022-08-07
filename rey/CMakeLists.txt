cmake_minimum_required(VERSION 3.8)

# https://cmake.org/cmake/help/latest/command/project.html
project(rey VERSION 1.0.0)

# set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo" CACHE STRING "" FORCE)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

include(GNUInstallDirs)

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(extern/chipmunk)
add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/freetype)
add_subdirectory(extern/openal-soft)
add_subdirectory(extern/libsndfile)
add_subdirectory(src)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
