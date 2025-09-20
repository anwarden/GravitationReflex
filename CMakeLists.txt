cmake_minimum_required(VERSION 3.4)
set(CMAKE_OSX_ARCHITECTURES x86_64) #Apple Silicon
project(Tp4_Initial)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

find_package(Imagine REQUIRED COMPONENTS Graphics)


add_executable(Gravitation1 gravitation1.cpp)
target_link_libraries(Gravitation1 Imagine::Graphics)


add_library(Gravitation tools.cpp tools.h vector.cpp vector.h ball.cpp ball.h)
target_link_libraries(Gravitation Imagine::Graphics)

add_executable(Gravitation2 gravitation2.cpp)
target_link_libraries(Gravitation2 Gravitation)

add_executable(Duel duel.cpp)
target_link_libraries(Duel Gravitation)
