cmake_minimum_required(VERSION 2.8)
project(animal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SLS_GENERATE_DOCS TRUE
    CACHE BOOL "generate documentation with doxygen")

set(FACE_SRC
    src/FaceBooklet.cc
    src/FBProfile.cc
    src/Database.cc)

set(FACE_TEST_SRC
    tests/test_run.cc
    tests/interface_tests.cc)

# find doxygen and generate docs
find_package(Doxygen)
if (DOXYGEN_FOUND AND SLS_GENERATE_DOCS)
    configure_file(
        ${CMAKE_SOURCE_DIR}/doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen")
endif(DOXYGEN_FOUND AND SLS_GENERATE_DOCS)

add_subdirectory(extern/googletest)
include_directories(
    ${CMAKE_SOURCE_DIR}/extern/googletest/include
    ${CMAKE_SOURCE_DIR}/include)

add_library(facebooklet ${FACE_SRC})

add_executable(facebooklet_tests ${FACE_TEST_SRC})
target_link_libraries(facebooklet_tests
    facebooklet
    gtest
    gtest_main)