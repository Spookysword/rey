add_library(test_main OBJECT tests.cpp)
include_directories(.)

# Gets all of the .cpp files and gets the name of the test and adds it to the TESTS list
# EX: test_main.cpp -> TESTS += test_main

file(GLOB CPP_TEST_SOURCES "tests/*.cpp")
set(TESTS)
foreach(TS IN LISTS CPP_TEST_SOURCES)
    cmake_path(GET TS STEM LAST_ONLY TSTMP)
    set(TESTS ${TESTS} ${TSTMP})
endforeach()

# Creates a test for each test in the TESTS list
foreach(TST IN LISTS TESTS)
    add_executable(test_${TST} tests/${TST}.cpp $<TARGET_OBJECTS:test_main>)
    target_link_libraries(test_${TST} PUBLIC rey)
    add_test(test_${TST} test_${TST})
endforeach()