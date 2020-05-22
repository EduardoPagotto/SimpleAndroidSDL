# SimpleAndroidSDL
SDL and Opengl native in Android devices using C/C++

### Download
- AndroidStudio
- NDK
- SDL2 source code

### Ubuntu 20.04 packages install
```bash
apt install default-jdk
apt install android-tools-adb
apt install mercurial
apt install gradle
```

### Edit file <i>local.properties</i> and set location of SDK and NDK
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

### Prepare environment project
```bash
ln -s ~/androidlib/SDL2 ./app/jni/SDL2
ln -s ~/androidlib/SDL2_image ./app/jni/SDL2_image
ln -s ~/androidlib/SDL2_net ./app/jni/SDL2_net
ln -s ~/androidlib/SDL2_ttf ./app/jni/SDL2_ttf
ln -s ~/androidlib/SDL2_mixer ./app/jni/SDL2_mixer
```

### Remove environment project (if necessary)
```bash
unlink ./app/jni/SDL2
unlink ./app/jni/SDL2_image
unlink ./app/jni/SDL2_mixer
unlink ./app/jni/SDL2_net
unlink ./app/jni/SDL2_ttf
```

### Optimal
```bash
# create links
link_SDL2_into_project.sh
```

### To Deploy in the project directory. It will build and install your .apk on any connected Android device

./gradlew installDebug

or

./gradlew installRelease

### to Clean
remover diretorios:
- .gradle/
- ./app/.externalNativeBuild/
- ./app/build/



reference:
- https://wiki.libsdl.org/Android
- https://hg.libsdl.org/SDL/file/default/docs/README-android.md
