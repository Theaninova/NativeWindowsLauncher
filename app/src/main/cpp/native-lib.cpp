#include <jni.h>
#include <string>
#include <math.h>

extern "C" JNIEXPORT jdouble
JNICALL
Java_de_wulkanat_www_nativewindowslauncher_WindowsLauncher_calcACache(JNIEnv *env, jobject, jdouble a, jdouble b, jdouble x2, jdouble y2) {
     return ((a + b) / pow(x2, 2) - (2 * y2) / pow(x2, 3));
}

extern "C" JNIEXPORT jdouble
JNICALL
Java_de_wulkanat_www_nativewindowslauncher_WindowsLauncher_calcBCache(JNIEnv *env, jobject, jdouble a, jdouble b, jdouble x2, jdouble y2) {
    return (((-2 * a) - b) / x2 + ((3 * y2) / pow(x2, 2)));
}