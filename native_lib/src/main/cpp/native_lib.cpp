#include <jni.h>
#include <string>
#include <android/log.h>
#include "java_hook.h"


extern "C" {
    void newAdd() {
        __android_log_print(6, "sharknade", "newAdd executed !!");
    }

    JNIEXPORT jstring JNICALL
    Java_com_sharknade_native_1lib_NativeLib_stringFromJNI(
            JNIEnv* env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
    //    dumpArtAddress();
        myhook(env, reinterpret_cast<void *>(newAdd), "com/sharknade/apks/hook/Shark", "eat", "()V", 0);
        return env->NewStringUTF(hello.c_str());
    }

}
