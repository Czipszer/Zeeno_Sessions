cmake_minimum_required (VERSION 3.19)
project (HELLO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable (helloWorld main.cpp)

if(MSVC)
  target_compile_options(helloWorld PRIVATE /W4)
else()
  target_compile_options(helloWorld PRIVATE -Wall -Wextra -pedantic)
endif()