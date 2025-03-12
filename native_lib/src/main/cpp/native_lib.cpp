#include <jni.h>
#include <string>
#include "native_add.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_sharknade_native_1lib_NativeLib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_sharknade_native_1lib_NativeLib_sum(JNIEnv *env, jobject thiz, jint a, jint b) {
    int sum = add(a,b);
    char * result = new char [100];
    sprintf(result,"%d + %d = %d \n",a,b, sum);
    return env->NewStringUTF(const_cast<const char*>(result));
}