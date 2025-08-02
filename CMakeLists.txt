cmake_minimum_required(VERSION 3.22)
project(mailfs)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES
  src/*.cpp
)
list(FILTER SRC_FILES EXCLUDE REGEX ".*Test.*\\.cpp$")

add_executable(mailfs
  ${SRC_FILES}
)

target_include_directories(mailfs
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GUMBO REQUIRED gumbo)

target_include_directories(mailfs PRIVATE ${GUMBO_INCLUDE_DIRS})
target_link_libraries(mailfs PRIVATE ${GUMBO_LIBRARIES} ${GUMBO_LDFLAGS})
target_compile_options(mailfs PRIVATE ${GUMBO_CFLAGS_OTHER})


option(BUILD_TESTS "Build Catch2 tests" OFF)

if (BUILD_TESTS)
  find_package(Catch2 3 REQUIRED)

  add_executable(test_utils
    src/TestUtils.cpp
  )

  target_include_directories(test_utils
    PRIVATE
      ${CMAKE_SOURCE_DIR}/src
  )

  target_link_libraries(test_utils
    PRIVATE
      Catch2::Catch2WithMain
  )

  include(CTest)
  enable_testing()

  add_test(NAME test_utils COMMAND test_utils)

endif()
