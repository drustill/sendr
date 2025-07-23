cmake_minimum_requried(VERSION 3.10)
project(mailfs)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_executable(mailfs)
target_link_libraries(mailfs ${CURL_LIBRARIES})
