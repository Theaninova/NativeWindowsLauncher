//
// Created by wulkanat on 31/07/2018.
//

#include "GLRender.h"
#include <jni.h>

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1surface_1created
        (JNIEnv * env, jclass cls) {
    on_surface_created();
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1surface_1changed
        (JNIEnv * env, jclass cls, jint width, jint height) {
    on_surface_changed();
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1draw_1frame
        (JNIEnv * env, jclass cls) {
    on_draw_frame();
}

float mtrxProjection[16];
float mtrxView[16];
float mtrxProjectionAndView[16];

float dxTouch = 0.0f;
float dyTouch = 0.0f;

float xTouchPos = 0.0f;
float yTouchPos = 0.0f;

//glGrid units per second per second
float xVelocityTouch = 0.0f;
float yVelocityTouch = 0.0f;
bool fingerDown = false;

float glGrid[] = { -1.0f, 1.0f, 1.0f, -1.0f };

int COORDS_PER_VERTEX = 3;
int vertexStride = COORDS_PER_VERTEX * 4;
short inds[] ={ 0, 1, 2, 0, 2, 3 };

float mScreenWidth = 1080.0f;
float mScreenHeight = 1920.0f;
float mAspectRatio = 16.0f / 9.0f;

long mLastTime = 0;
int mProgram;

//var windowsLauncher = WindowsLauncher(this)

void on_surface_created() {
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void on_surface_changed() {

}

void on_draw_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}