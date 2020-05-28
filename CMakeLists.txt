cmake_minimum_required(VERSION 3.6)

project(GAME)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
#set(OVR_SET_TO_USE OFF) # futuro usado para esterioscopica
add_definitions(-DANDROID_APP_PLATFORM=android-16)
add_definitions(-DANDROID_STL=c++_static)

# armeabi-v7a requires cpufeatures library
# include(AndroidNdkModules)
# android_ndk_import_module_cpufeatures()
# set(CPUFEATURES_LIBRARIES cpufeatures)
##add_definitions(-DGLM_ENABLE_EXPERIMENTAL) #teste GL posterior
#add_definitions(-DUSE_WEBP=OFF)

# SDL sources are in a subfolder named "SDL"
add_subdirectory(external)

# Compilation of companion libraries
#add_subdirectory(SDL2_image)
#add_subdirectory(SDL2_mixer)
#add_subdirectory(SDL2_ttf)

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src)
