# SimpleAndroidSDL
SDL, glm and Opengl native in Android devices using C/C++

## Deps
Ubuntu:
```bash
# Android depends:
sudo apt install openjdk-11-jdk-headless
sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386 lib32z1 libbz2-1.0:i386
```

AndroidStudio:<i>https://developer.android.com/studio/index.html?hl=pt-br</i>
```bash
tar xvf android-studio-ide-191.5900203-linux.tar.gz
sudo mv android-studio /opt/
cd /opt/android-studio/bin

# add to projetct licences  and NDK 21.1.6352462
# project tested with compileSdkVersion 26
./studio
```


Project separate in 3 part's with ABI armeabi-v7a
1. SDL2 in C:<p>
    - Compiled with NDK tools default (impossible to link using CMake in armeabi-v7a)<p>
      see: [./android/SDL2/build.gradle](android/SDL2/build.gradle)

2. Game Lib in C++:<p>
    - Compiled with GCC and CMake (yes we can!!)<p>
    see: [./android/app/build.gradle](android/app/build.gradle)

3. App in Android Java:<p>
    - Compiled with unsafe options to use API my app and SDL<p>
    see: [./android/build.gradle](android/build.gradle)

Obs: I using VScode insted AndroidStudio(even in top machines: lazyest)

## Download
- AndroidStudio
- NDK
- SDL2 source code (links bellow)
- GLM soruce code (https://github.com/g-truc/glm/releases)

## Ubuntu 21.04 packages install
```bash
apt install default-jdk
apt install android-tools-adb
apt install mercurial

# No more necessary
# apt install gradle
```

Edit file <i>[./android/local.properties](./android/local.properties)</i> and set location of SDK and NDK
```file
sdk.dir=/home/user/Android/Sdk
ndk.dir=/home/user/Android/Sdk/ndk/21.1.6352462
```

### Download all SDL2 libs 
<i>In my machine:</i> ~/Downloads:
- https://www.libsdl.org/release/SDL2-2.0.14.tar.gz
- https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
- https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz
- https://www.libsdl.org/projects/SDL_net/release/SDL2_net-2.0.1.tar.gz
- https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz

### Setup environment to project with SDL2
```bash
# create a android lib dir
mkdir ~/androidlib
cd ./androidlib

# Copy all SDL2 libs from Downloads directory to: ~/androidlib
cp ~/Downloads/SDL2*.tar.gz .
cp ~/Downloads/glm-0.9.9.8.tar.gz .

# Extract all libs (SDL2 and GLM)
tar xvf SDL2-2.0.14.tar.gz
tar xvf SDL2_image-2.0.5.tar.gz
tar xvf SDL2_mixer-2.0.4.tar.gz
tar xvf SDL2_net-2.0.1.tar.gz
tar xvf SDL2_ttf-2.0.15.tar.gz
tar xvf glm-0.9.9.8.tar.gz

# create link's
ln -s SDL2-2.0.14 SDL2
ln -s SDL2_image-2.0.5 SDL2_image
ln -s SDL2_mixer-2.0.4 SDL2_mixer
ln -s SDL2_net-2.0.1 SDL2_net
ln -s SDL2_ttf-2.0.15 SDL2_ttf
ln -s glm-0.9.9.8 glm

# Go to the project directory
cd ~/Projects/SimpleAndroidSDL

# Link libs dirs to project
ln -s ~/androidlib/SDL2 ./external/SDL2/SDL2
ln -s ~/androidlib/SDL2_image ./external/SDL2/SDL2_image
ln -s ~/androidlib/SDL2_net ./external/SDL2/SDL2_net
ln -s ~/androidlib/SDL2_ttf ./external/SDL2/SDL2_ttf
ln -s ~/androidlib/SDL2_mixer ./external/SDL2/SDL2_mixer
ln -s ~/androidlib/glm ./external/glm

# or use the scripr bellow
# ./tools-util/link_SDL2_into_project.sh

```

### VSCode utils extensions (if using vscode)
```bash
code --install-extension abhiagr.logcat
code --install-extension adelphes.android-dev-ext
code --install-extension ms-vscode.cpptools
code --install-extension naco-siren.gradle-language
code --install-extension richardwillis.vscode-gradle
code --install-extension twxs.cmake
code --install-extension vinicioslc.adb-interface-vscode
```
listed with:
```bash
code --list-extensions | xargs -L 1 echo code --install-extension
```

### Error vscode 
case: <i>"Visual Studio Code is unable to watch for file changes in this large workspace" <p>(error ENOSPC)</i><p>
```bash
cat /proc/sys/fs/inotify/max_user_watches
8192
```
edit /etc/sysctl.conf and add to change default value
```file
fs.inotify.max_user_watches=524288
```
Apply new value and test
```bash
sudo sysctl -p
cat /proc/sys/fs/inotify/max_user_watches
524288
```
<p>

### Build and Deploy in to Cell
It will build and install the .apk on any connected Android device

1. Enable cell phone developer and connect udb cable

    >seting->system->develop options->usb debug enable

2. Enable ADB
    ```bash
    # enable adb
    sudo adb start-server

    # reinicia servidor 
    # sudo adb kill-server

    # show devices connected
    adb devices

    List of devices attached
    0039710819      device
    ```

3. Build
    ```bash
    # go to project compiler directory (~/Projects/SimpleAndroidSDL/android)
    cd ./android

    # show tasks 
    ./gradlew tasks

    # show projects
    ./gradlew projects

    # builds
    ./gradlew :SDL2:build
    ./gradlew :app:build
    ./gradlew :app:android build
    ```

4. Deploy Cell
    ```bash
    # or build all project
    ./gradlew build

    # install debug app
    ./gradlew installDebug

    # or install release
    ./gradlew installRelease
    ```

5. Build and Deploy in Simulator AVD
    ```bash
    # go to android SDK directory
    cd ~/Android/Sdk/tools

    # lista devices configurados
    ./emulator -list-avds
    $Pixel_2_API_27

    # enable AVD
    ./emulator -avd Pixel_2_API_27
    ```

### Clean Project by directory:
```bash
cd android

#in cell phone ou AVD
./gradlew uninstallDebug
# or
./gradlew uninstallReleae

# in project directorys
rm .gradle
rm .distribution
rm ./app/.cxx
```


### Olds Makefiles removed
path: ./SimpleAndroidSDL/app/jni/Android.mk
```file
include $(call all-subdir-makefiles)
```

path: ./SimpleAndroidSDL/app/jni/Application.mk
```file
APP_STL := c++_shared
APP_ABI := armeabi-v7a arm64-v8a x86 x86_64
# Min runtime API level
APP_PLATFORM=android-16
```

path: ./SimpleAndroidSDL/app/jni/src/Android.mk
```file
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := main
SDL_PATH := ../SDL
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
# Add your application source files here...
LOCAL_SRC_FILES := first.cpp
LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)
```

reference:
- https://wiki.libsdl.org/Android
- https://hg.libsdl.org/SDL/file/default/docs/README-android.md
