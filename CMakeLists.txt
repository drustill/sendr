cmake_minimum_required(VERSION 3.10)
project(mailfs)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES
  src/*.cpp
)
list(FILTER SRC_FILES EXCLUDE REGEX ".*TestDotEnv\\.cpp$")

add_executable(mailfs
  ${SRC_FILES}
)

target_include_directories(mailfs
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
find_package(Catch2 CONFIG REQUIRED)

add_executable(DotEnvTests
  src/DotEnv.cpp
  src/TestDotEnv.cpp
)

target_include_directories(DotEnvTests
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(DotEnvTests
  PRIVATE
    Catch2::Catch2WithMain
)

include(CTest)
enable_testing()
add_test(NAME DotEnvTests COMMAND DotEnvTests)
