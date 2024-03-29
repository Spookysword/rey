
file(GLOB_RECURSE REY_SOURCE_FILES "*.c" "*.cpp")

file(GLOB_RECURSE REY_HEADER_FILES "../include/*.h")

add_library(rey ${REY_SOURCE_FILES} ${REY_HEADER_FILES})

target_include_directories(rey
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../extern/chipmunk/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
if (WIN32)
  target_link_libraries(rey PUBLIC opengl32 chipmunk_static glfw glad freetype OpenAL)
else()
target_link_options(rey PUBLIC -Wl,-Bdynamic)
target_link_libraries(rey PUBLIC GL chipmunk_static glfw glad freetype OpenAL)

endif()

set_target_properties(rey PROPERTIES
	CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

if(MSVC)
  set_target_properties(rey PROPERTIES
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMPILE_PDB_NAME rey
  )

  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/rey.pdb"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    OPTIONAL
  )
endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${REY_SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include" PREFIX "include" FILES ${REY_HEADER_FILES})

install(
  TARGETS rey
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)