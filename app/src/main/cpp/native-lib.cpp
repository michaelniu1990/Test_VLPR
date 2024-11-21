#include <jni.h>
#include <string>
#include "VLPR.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_test_1vlpr_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    VLPR vLPR;
    vLPR.process();
    return env->NewStringUTF(hello.c_str());
}