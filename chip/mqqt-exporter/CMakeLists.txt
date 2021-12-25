cmake_minimum_required(VERSION 3.18)
project(mqqt_exporter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE sourceFiles
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}")

list(APPEND CMAKE_MODULE_PATH ${BUILD_DIR})
list(APPEND CMAKE_PREFIX_PATH ${BUILD_DIR})

set(OUT_DIR "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/out/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}/bin)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/out/bin")

include(${BUILD_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup() #NO_OUTPUT_DIRS
 
add_executable(${PROJECT_NAME} ${sourceFiles})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include/")
conan_target_link_libraries(${PROJECT_NAME})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
