# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

project("native_lib")

# 创建一个add的共享库
set(LIB_ADD add)
message("================================")
message(${LIB_ADD})
add_library(${LIB_ADD} SHARED native_add.cpp)
# 新增输出目录配置
set_target_properties(${LIB_ADD} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "D:/sharknade/android_workspace/apks/so"  # 指定绝对路径
#        ARCHIVE_OUTPUT_DIRECTORY "d:/sharknade/frida/libs"   # 静态库目录（可选）
)

target_link_libraries(${LIB_ADD})

add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        native_lib.cpp)

# 新增输出目录配置
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "D:/sharknade/android_workspace/apks/so"  # 指定绝对路径
        #        ARCHIVE_OUTPUT_DIRECTORY "d:/sharknade/frida/libs"   # 静态库目录（可选）
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        android
        log
        ${LIB_ADD}
)


