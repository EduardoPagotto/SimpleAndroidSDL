cmake_minimum_required(VERSION 3.6)

project(MY_APP)

find_library(SDL2 SDL2)

set (LibsFirstTest  -lGLESv1_CM
                    -lGLESv2 
                    -llog
                    SDL2)
                    
add_library(main SHARED first.cpp)
target_link_libraries(main ${LibsFirstTest})
