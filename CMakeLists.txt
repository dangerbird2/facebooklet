cmake_minimum_required(VERSION 2.8)
project(facebooklet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SLS_GENERATE_DOCS TRUE
    CACHE BOOL "generate documentation with doxygen")

set(SLS_BUILD_TESTS TRUE
    CACHE BOOL "build tests using googletest")
set(FACE_SRC
    src/FaceBooklet.cc
    src/FBProfile.cc
    src/Database.cc
    src/NodeData.cc
    src/Date.cc)

set(FACE_HDR
    src/face.h
    src/FaceBooklet.h
    src/FBProfile.h
    src/interfaces.h
    src/NodeData.h
    src/utils.h)

set(FACE_EXEC_SRC src/main.cc)

file(COPY ${FACE_HDR}
    DESTINATION ${CMAKE_BINARY_DIR}/include/facebooklet)


set(FACE_TEST_SRC
    tests/test_run.cc
    tests/profile_test.cc
    tests/db_test.cc
    tests/data_test.cc
    tests/engine_tests.cc)

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


include_directories(

    ${CMAKE_SOURCE_DIR}/include)

add_library(facebooklet ${FACE_SRC})

if(SLS_BUILD_TESTS)
    # build googletest & test suite
    add_subdirectory(extern/googlemock)
    include_directories(
        ${CMAKE_SOURCE_DIR}/extern/googlemock/include
        ${CMAKE_SOURCE_DIR}/extern/gtest/include)

    add_executable(facebooklet_tests ${FACE_TEST_SRC})
    target_link_libraries(facebooklet_tests
        facebooklet
        gtest
        gtest_main
        gmock
        gmock_main)
endif(SLS_BUILD_TESTS)


add_executable(facebooklet_exec ${FACE_EXEC_SRC})
target_link_libraries(facebooklet_exec
    facebooklet)