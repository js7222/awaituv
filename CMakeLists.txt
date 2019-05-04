cmake_minimum_required (VERSION 2.6)
project (awaituv)

if (MSVC)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -await /std:c++lastest")
link_libraries (libuv libcurl)
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fcoroutines-ts -std=c++14 -stdlib=libc++ -nodefaultlibs ")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++ -lc++abi -lm -lc -lgcc_s -lgcc")
find_package(Threads)
link_libraries(${CMAKE_THREAD_LIBS_INIT})

find_package(Boost 1.58.0 COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-DBOOST_THREAD_VERSION=4)

#include_directories("/usr/local/include/c++/v1")
find_package (CURL REQUIRED)
link_libraries (${CURL_LIBRARIES})
link_libraries (libuv.a)
endif ()

include_directories (inc)
add_subdirectory (samples)
