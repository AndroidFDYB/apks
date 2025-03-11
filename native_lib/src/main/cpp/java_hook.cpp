#include <jni.h>
#include <string>
#include <filesystem>
#include "ida.h"
#include "elf.h"
#include "android/log.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "sys/mman.h"
#include "findsym.h"

int flag=0;
_QWORD nativ[10];
long jump[10];
int *startr;
long old1[10];
long old2[10];
void baocun(__int64 a,int n){


    old1[n]=*((long *)a + 5);
    old2[n]=*(_QWORD *)(a + 4);

    *((long *)a + 5)= jump[n];
//    *(_QWORD *)(a + 4)=0x1d8ee408000101;
    *(_QWORD *)(a + 4)= nativ[n]|0x80100;
}

void huifu(__int64 a,int n){

    *((long *)a + 5)=old1[n];
    *(_QWORD *)(a + 4)=old2[n];

}


void dumpArtAddress() {
    if(flag==0) {
        char line[1024];
        // 6287
        int *end;
        int n = 1;
        /**
         sailfish:/ # cat /proc/6287/maps | grep libart.so
            712b000000-712b12d000 r--p 00000000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so
            712b12d000-712b5b9000 --xp 0012d000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so
            712b5b9000-712b5bc000 rw-p 005b9000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so
            712b5bc000-712b5cd000 r--p 005bc000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so


        6dc5800000-6dc594a000 r--p 00000000 fd:00 196                            /apex/com.android.art/lib64/libart.so
        6dc5a00000-6dc5fd7000 r-xp 00200000 fd:00 196                            /apex/com.android.art/lib64/libart.so
        6dc6000000-6dc6013000 r--p 00800000 fd:00 196                            /apex/com.android.art/lib64/libart.so
        6dc6212000-6dc6216000 rw-p 00812000 fd:00 196                            /apex/com.android.art/lib64/libart.so
        6dc5800000-6dc594a000：
        这是一个只读区域，可能是存储只读数据（如常量、字符串等）。
        它的大小为 0x14a000 字节（约 1.3 MB）。
        6dc5a00000-6dc5fd7000：
        这是一个可读可执行区域，通常是代码段（.text）。
        它的大小为 0xf7000 字节（约 1 MB）。
        它的起始地址与前一个区域之间有一个间隔，这是因为内核需要为代码段分配一个独立的地址空间，以确保代码的隔离性和安全性。
        6dc6000000-6dc6013000：
        这是一个只读区域，可能是存储只读数据。
        它的大小为 0x13000 字节（约 76 KB）。
        6dc6212000-6dc6216000：
        这是一个可读写区域，可能是动态分配的数据区或 BSS 段。
        它的大小为 0x4000 字节（16 KB）。
        它的起始地址与前一个区域之间有一个较大的间隔，这是因为内核需要将动态数据区分配到一个独立的页面中，以避免与其他区域冲突。
         */
        FILE *fp = fopen("/proc/self/maps", "r");
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, "libart.so")) {
                __android_log_print(6, "r0ysue", "%s", line);
                if (n == 1) {
                    startr = reinterpret_cast<int *>(strtoul(strtok(line, "-"), NULL, 16));
                    end = reinterpret_cast<int *>(strtoul(strtok(NULL, " "), NULL, 16));


                } else {
                    strtok(line, "-");
                    end = reinterpret_cast<int *>(strtoul(strtok(NULL, " "), NULL, 16));
                }
                n++;


            }


        }
        flag++;
        __android_log_print(6, "sharknade", "start %lx, end 0x%lx", startr);

    }
    int so=findsym("/apex/com.android.art/lib64/libart.so","art_quick_generic_jni_trampoline");

    __android_log_print(6, "sharknade", "art_quick_generic_jni_trampoline offset %d", so);
}

void myhook(JNIEnv* env,void* func,const char* classname,const char* methodname,const char* shoty,int ns){

    JNINativeMethod getMethods[] = {
            {methodname, shoty,(void*)func}
    };
    if(flag==0) {
        char line[1024];
        // 6287
        int *end;
        int n = 1;
        /**
         sailfish:/ # cat /proc/6287/maps | grep libart.so
            712b000000-712b12d000 r--p 00000000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so
            712b12d000-712b5b9000 --xp 0012d000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so
            712b5b9000-712b5bc000 rw-p 005b9000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so
            712b5bc000-712b5cd000 r--p 005bc000 fd:00 341                            /apex/com.android.runtime/lib64/libart.so

         */
        FILE *fp = fopen("/proc/self/maps", "r");
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, "libart.so")) {
                __android_log_print(6, "r0ysue", "%s", line);
                if (n == 1) {
                    startr = reinterpret_cast<int *>(strtoul(strtok(line, "-"), NULL, 16));
                    end = reinterpret_cast<int *>(strtoul(strtok(NULL, " "), NULL, 16));


                } else {
                    strtok(line, "-");
                    end = reinterpret_cast<int *>(strtoul(strtok(NULL, " "), NULL, 16));
                }
                n++;


            }


        }
        flag++;

    }

//    int so=findsym("/system/lib64/libart.so","art_quick_generic_jni_trampoline");
    int so=findsym("/apex/com.android.art/lib64/libart.so","art_quick_generic_jni_trampoline");
    __android_log_print(6, "r0ysue", "offset %lx , result : ", so); //2221b0
    __android_log_print(6, "r0ysue", "start %lx , result : ", reinterpret_cast<long>((char *) startr +so)); //2221b0
    __android_log_print(6, "r0ysue", "start %lx , result : ", reinterpret_cast<long>(0xa00000l-0x94a000l)); //2221b0

    jclass a=env->FindClass(classname);
    jmethodID b=env->GetMethodID(a,methodname, shoty);
    __int64 a1= reinterpret_cast<long long int>(b);
    nativ[ns]=*(_QWORD *)(a1 + 4);
    jump[ns]=*((long *)a1 + 5);
    *(_QWORD *)(a1 + 4)= *(_QWORD *)(a1 + 4)^0x80100 ;

    // 6dc5a00000  + 2236848 =
    //     2221b0
    // 6dc5c
    // 6dc594a000
    //      B5000
    // 6dc5800000
    //    2236848

    //6dc5800000-6dc594a000 ----> 6dc5800000  +
    //                               2221b0 = 6dc5a221b0
    //
    // 6dc5a00000
    // 6dc594a000 = b6000
    //6dc5a00000-6dc5fd7000
    //6dc6000000-6dc6013000
    //6dc6212000-6dc6216000 :  2221b0 = 6dc60221b0
//    *((long *)a1 + 5)= reinterpret_cast<long>((char *) startr +so - 0x25000);
    *((long *)a1 + 5)= reinterpret_cast<long>((char *) startr +so - 0xb6000);
    *(_QWORD *)(a1 + 32)= reinterpret_cast<uint64>(func);
//    env->RegisterNatives(a,getMethods,1);




}