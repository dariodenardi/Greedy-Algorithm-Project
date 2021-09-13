cmake_minimum_required(VERSION 2.8.12)
project(Greedy)


######## Complier message
set(CMAKE_BUILD_TYPE Release)
message(STATUS "System: ${CMAKE_SYSTEM}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

######## Set output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build//bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

######## Set C++ 11 standard
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
if (COMPILER_SUPPORTS_CXX11)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()
else ()
    message(STATUS "Fatal Error: Your compiler doesn't support c++11, please install it!")
endif ()

######## find all the source files.
file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

######## Set executable file name, and add the source files for it.
add_executable(Greedy ${HEADER_FILES} ${SOURCE_FILES})

####### Create directory
set(CREATE_DIR_INSTANCES instances)

message(STATUS "Install directory: ${CREATE_DIR_INSTANCES}")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin/${CREATE_DIR_INSTANCES})
