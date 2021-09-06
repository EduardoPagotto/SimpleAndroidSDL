cmake_minimum_required(VERSION 3.6)

project(GAME)
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
#set(OVR_SET_TO_USE OFF) # futuro usado para esterioscopica

#SimpleAndroidSDL/android/build/android/SDL2/intermediates/ndkBuild/debug/obj/local/armeabi-v7a
string(TOLOWER ${CMAKE_BUILD_TYPE} ANDROID_BUILD_DIR)
set(DISTRIBUTION_DIR ${CMAKE_SOURCE_DIR}/build/SDL2/intermediates/ndkBuild)
set(SDL_LOCATION ${CMAKE_SOURCE_DIR}/external/SDL2)

add_library( SDL2 SHARED IMPORTED )
#add_library( SDL2_image SHARED IMPORTED )
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2.so)
#set_target_properties(SDL2_image PROPERTIES IMPORTED_LOCATION ${DISTRIBUTION_DIR}/${ANDROID_BUILD_DIR}/obj/local/${ANDROID_ABI}/libSDL2_image.so)

# SDL sources are in a subfolder named "SDL"
#add_subdirectory(external) ##Compilado fora do CMake 

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src)
add_subdirectory(external)