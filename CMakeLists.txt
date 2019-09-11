cmake_minimum_required(VERSION 3.1)

project(usbdemo VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # TODO: don't mix warning options with "/EHsc"
    set(warnings "/W4 /WX /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

set(CMAKE_TOOLCHAIN_FILE "C:/Users/pavol/Sources/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_subdirectory(libs)

add_subdirectory(src)

