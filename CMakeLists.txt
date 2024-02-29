cmake_minimum_required(VERSION 3.14)
set(CXX_STANDARD 17)
project(my-project)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)
#add_subdirectory(libraries/googletest)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

option(MATCH_TESTS "build tests (or no)" ON)

if (MATCH_TESTS)
        add_library(example_google_tests ${all_SRCS})
        set_target_properties(example_google_tests PROPERTIES LINKER_LANGUAGE CXX)
        enable_testing()
        add_subdirectory(tests)
endif()


add_executable(app ${all_SRCS})
set_target_properties(app PROPERTIES LINKER_LANGUAGE CXX)   