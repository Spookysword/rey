cmake_minimum_required(VERSION 3.8)
project(rey VERSION 1.0.0)

if(BUILD_TESTING)
    message("rey ----- Testing Enabled -----")
    add_subdirectory(tests)
else()
    message("rey ----- Testing Disabled -----")
endif(BUILD_TESTING)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

include(GNUInstallDirs)

find_package(Threads REQUIRED)
if(WIN32)
  find_package(OpenGL REQUIRED)
endif(WIN32)

message("rey ------- Setting up dependencies -------")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
message("rey ----- chipmunk -----")
add_subdirectory(extern/chipmunk)

message("rey ----- glad -----")
add_subdirectory(extern/glad)

message("rey ----- glfw -----")
add_subdirectory(extern/glfw)

message("rey ----- freetype -----")
add_subdirectory(extern/freetype)

message("rey ----- oal-soft -----")
add_subdirectory(extern/openal-soft)

message("rey ------- Done setting up dependencies -------")
add_subdirectory(src)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
