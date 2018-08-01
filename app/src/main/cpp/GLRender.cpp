//
// Created by wulkanat on 31/07/2018.
//

#include "GLRender.h"
#include <jni.h>

void init() {
    mLastTime = std::chrono::high_resolution_clock::now();

    Parent me;
    me.yVelocityTouch = &yVelocityTouch;
    me.xVelocityTouch = &xVelocityTouch;
    me.dyTouch = &dyTouch;
    me.dxTouch = &dxTouch;
    me.xTouchPos = &xTouchPos;
    me.yTouchPos = &yTouchPos;
    me.fingerDown = &fingerDown;

    me.glGrid = &glGrid;
    me.indsSize = &indsSize;
    me.inds = &inds;

    windows_launcher_init(me);
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_init
        (JNIEnv * env, jclass cls) {
    init();
}

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

void drawTile(Tile * tile, float m[]) {
    /*GLint mPositionHandle = glGetAttribLocation(RiGraphicTools.sp_SolidColor, "vPosition");
    GLES20.glEnableVertexAttribArray(mPositionHandle)
    GLES20.glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GLES20.GL_FLOAT, false, vertexStride, tile.renderVertBuffer)

    GLint colorHandle = glGetUniformLocation(RiGraphicTools.sp_SolidColor, "uColor")
    glUniform4fv(colorHandle, 1, (*tile).renderColorBuffer, 0);

    val mtrxhandle = GLES20.glGetUniformLocation(RiGraphicTools.sp_SolidColor, "uMVPMatrix")
    GLES20.glUniformMatrix4fv(mtrxhandle, 1, false, m, 0)
    GLES20.glDrawElements(GLES20.GL_TRIANGLES, inds.size, GLES20.GL_UNSIGNED_SHORT, tile.renderDrawListBuffer)
    GLES20.glDisableVertexAttribArray(mPositionHandle)*/
}

//var windowsLauncher = WindowsLauncher(this)

void on_surface_created() {

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void on_surface_changed() {

}

void on_draw_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}