# SimpleAndroidSDL
SDL and Opengl native in Android devices using C/C++

Project separate in 3 part's with ABI armeabi-v7a
1. SDL2 in C:<p>
    - Compiled with NDK tools default (impossible to link using CMake)<p>
      see: [./android/SDL2/build.gradle](android/SDL2/build.gradle)

2. Game Lib in C++:<p>
    - Compiled with GCC and CMake (yes we can!!)<p>
    see: [./android/SDL2/build.gradle](android/app/build.gradle)

3. App in Android Java:<p>
    - Compiled with unsafe options to use API my app and SDL<p>
    see: [./android/build.gradle](android/build.gradle)

Obs: I using VScode insted AndroidStudio(even in top machines: lazyest)

## Download
- AndroidStudio
- NDK
- SDL2 source code

## Ubuntu 20.10 packages install
```bash
apt install default-jdk
apt install android-tools-adb
apt install mercurial

# Not necessary
# apt install gradle
```

Edit file <i>[./android/local.properties](./android/local.properties)</i> and set location of SDK and NDK
```file
sdk.dir=/home/user/Android/Sdk
ndk.dir=/home/user/Android/Sdk/ndk/21.1.6352462
```

### Prepare environment to new machine
Download all SDL2 libs and copy into ~/androidlib/
```bash
# unzip all libs
tar xvf SDL2-2.0.12.tar.gz
tar xvf SDL2_image-2.0.5.tar.gz
tar xvf SDL2_mixer-2.0.4.tar.gz
tar xvf SDL2_net-2.0.1.tar.gz
tar xvf SDL2_ttf-2.0.15.tar.gz

# create link removing version like below
ln -s SDL2-2.0.12 SDL2
ln -s SDL2_image-2.0.5 SDL2_image
ln -s SDL2_mixer-2.0.4 SDL2_mixer
ln -s SDL2_net-2.0.1 SDL2_net
ln -s SDL2_ttf-2.0.15 SDL2_ttf
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

### Prepare environment project
```bash
ln -s ~/androidlib/SDL2 ./external/SDL2/SDL2
ln -s ~/androidlib/SDL2_image ./external/SDL2/SDL2_image
ln -s ~/androidlib/SDL2_net ./external/SDL2/SDL2_net
ln -s ~/androidlib/SDL2_ttf ./external/SDL2/SDL2_ttf
ln -s ~/androidlib/SDL2_mixer ./external/SDL2/SDL2_mixer

# or
./tools-util/link_SDL2_into_project.sh

# to remove if you wish
unlink ./external/SDL2/SDL2
unlink ./external/SDL2/SDL2_image
unlink ./external/SDL2/SDL2_net
unlink ./external/SDL2/SDL2_ttf
unlink ./external/SDL2/SDL2_mixer
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

### Build and Deploy in Cell
It will build and install your .apk on any connected Android device

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
    # go to project compiler directory
    cd android

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
