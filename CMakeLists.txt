cmake_minimum_required(VERSION 3.10)
project(mailfs)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
  src/*.cpp
)

add_executable(mailfs ${SOURCES})

find_package(Catch2 CONFIG REQUIRED)

add_executable(DotEnvTests
  src/DotEnv.cpp
  src/TestDotEnv.cpp
)

target_include_directories(mailfs
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(mailfs
  PRIVATE
  Catch2::Catch2
)

include(CTest)
add_test(NAME DotEnvTests COMMAND DotEnvTests)
