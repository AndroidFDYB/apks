#ifndef MY_JAVA_H
#define MY_JAVA_H
#include "ida.h"
#include "jni.h"

void huifu(__int64 , int)
void save(__int64,int)
void myhook(JNIEnv*,void*,const char* , const char* , const char* , int);
#endif