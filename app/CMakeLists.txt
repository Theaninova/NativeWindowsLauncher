# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories( src/main/cpp/ )

add_library( GLRender
             SHARED
             src/main/cpp/GLRender.cpp )

add_library( AccExpInterpolator
             SHARED
             src/main/cpp/AccExpInterpolator.cpp )

add_library( WindowsLauncher
             SHARED
             src/main/cpp/WindowsLauncher.cpp )

add_library( Matrix
             SHARED
             src/main/cpp/Matrix.cpp )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries(GLRender
                        EGL
                        GLESv2
                        WindowsLauncher
                        Matrix)
target_link_libraries(WindowsLauncher
                        AccExpInterpolator)