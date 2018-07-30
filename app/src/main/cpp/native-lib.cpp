#include <jni.h>
#include <string>
#include <math.h>

extern "C" JNIEXPORT jdouble
JNICALL
Java_de_wulkanat_www_nativewindowslauncher_WindowsLauncher_calcACache(JNIEnv *env, jobject, jdouble a, jdouble b, jdouble x2, jdouble y2) {
     return ((a + b) / pow(x2, 2.0) - (2.0 * y2) / pow(x2, 3));
}

extern "C" JNIEXPORT jdouble
JNICALL
Java_de_wulkanat_www_nativewindowslauncher_WindowsLauncher_calcBCache(JNIEnv *env, jobject, jdouble a, jdouble b, jdouble x2, jdouble y2) {
    return (((-2.0 * a) - b) / x2 + ((3.0 * y2) / pow(x2, 2)));
}

extern "C" JNIEXPORT jdouble
JNICALL
Java_de_wulkanat_www_nativewindowslauncher_WindowsLauncher_expAccInterpolator(JNIEnv *env, jobject, jdouble precalc_a, jdouble precalc_b, jdouble initial_a, jdouble s) {
    return precalc_a * pow(s, 3) + precalc_b * pow(s, 2) + initial_a * s;
}