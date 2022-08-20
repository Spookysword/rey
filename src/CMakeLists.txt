set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
add_executable(sample main.cpp)
IF (WIN32)
        target_link_options(sample PRIVATE -mwindows)
ENDIF (WIN32)
target_link_options(sample PRIVATE -static-libstdc++)
target_link_options(sample PRIVATE -static-libgcc)
#target_link_options(sample PRIVATE -static)
target_include_directories(sample
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>)
target_link_libraries(sample PUBLIC rey)
