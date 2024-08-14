cmake_minimum_required(VERSION 3.7...3.29)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(linopt VERSION 0.1
               DESCRIPTION "Matrix manipulation library"
               LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  option(PACKAGE_TESTS "build the tests" ON)
else()
  option(PACKAGE_TESTS "don't build the tests" OFF)
endif()

SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(PACKAGE_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  SET(CMAKE_CXX_FLAGS "-Wall")
  SET(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(BUILD_MODE Debug)

  enable_testing()

  function (find_and_add_test)
    cmake_parse_arguments(${prefix}
      "${options}"
      "${oneValueArgs}"
      "${multiValueArgs}"
      "${ARGN}")
    list(GET ARGN 0 test_name)
    list(REMOVE_AT ARGN 0)
    list(GET ARGN 0 test_file)
    list(REMOVE_AT ARGN 0)

    add_executable(
      "${test_name}"
      "tests/${test_file}"
    )


    foreach(loopVar ${ARGN})
      get_filename_component(baredir ${loopVar} DIRECTORY)
      target_include_directories("${test_name}" PUBLIC ${baredir})
      message("added include dir ${baredir} to target ${test_name}")
      target_sources("${test_name}" PUBLIC ${loopVar})
      message("added source file ${loopVar} to target ${test_name}")
    endforeach()

    target_link_libraries(
      "${test_name}"
      GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests("${test_name}")
  endfunction()

  # Define tests here, include the test_name, full relative pathname from
  # the root dir to the test file including the .cpp extension,
  # then all the cpp files used needed for the test.
  # The header files in the same directories as the specified cpp files
  # are automatically linked.
  find_and_add_test(disk_matrix_1_unittest
    src/disk/matrix/disk_matrix_1_unittest.cpp
    src/disk/matrix/DiskMatrix.cpp
  )
  find_and_add_test(matrix_1_unittest
    src/inmemory/matrix/matrix_1_unittest.cpp
    src/inmemory/matrix/Matrix.cpp
  )
endif()


SET(Boost_USE_STATIC_LIBS ON)           # link statically
#ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)  # or, link dynamically

find_package(Boost 1.69.0 COMPONENTS log log_setup REQUIRED)


add_library(server STATIC src/server/Server.cpp)
target_link_libraries(server PUBLIC Boost::log_setup Boost::log)

add_executable(start src/start.cpp)
target_link_libraries(start PRIVATE server)
target_include_directories(start PUBLIC src/server)


