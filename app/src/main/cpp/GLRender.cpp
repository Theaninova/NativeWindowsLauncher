//
// Created by wulkanat on 31/07/2018.
//

#include "GLRender.h"
#include <jni.h>
#include <string>

static GLenum sp_SolidColor = 0;

const static GLchar * vs_SolidColor =
                "uniform mat4 uMVPMatrix; "
                "attribute vec4 vPosition; "
                "void main() { "
                "    gl_Position = uMVPMatrix * vPosition; "
                "}";
const static GLint vs_SolidColorSize = sizeof(vs_SolidColor);

const static GLchar * fs_SolidColor =
                "precision mediump float;"
                "uniform vec4 uColor;"
                "void main() {"
                "  gl_FragColor = uColor;" //"  gl_FragColor = vec4(1,0,0,1);" +
                "}";
const static GLint fs_SolidColorSize = sizeof(fs_SolidColor);


static GLint loadShader(GLenum type, const GLchar ** shaderCode, const GLint * shaderCodeSize) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, shaderCode, shaderCodeSize);
    glCompileShader(shader);

    return shader;
}

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

void onPause() {

}

void onResume() {
    mLastTime = std::chrono::high_resolution_clock::now();
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

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_onPause
        (JNIEnv * env, jclass cls) {
    onPause();
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_onResume
        (JNIEnv * env, jclass cls) {
    onResume();
}

void drawTile(Tile * tile, float m[]) {
    GLuint mPositionHandle = (GLuint) glGetAttribLocation(sp_SolidColor, "vPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, vertexStride, tile->renderVertBuffer);

    GLint colorHandle = glGetUniformLocation(sp_SolidColor, "uColor");
    glUniform4fv(colorHandle, 1, tile->renderColorBuffer);

    GLint mtrxhandle = glGetUniformLocation(sp_SolidColor, "uMVPMatrix");
    glUniformMatrix4fv(mtrxhandle, 1, GL_FALSE, m);
    glDrawElements(GL_TRIANGLES, indsSize, GL_UNSIGNED_SHORT, tile->renderDrawListBuffer);
    glDisableVertexAttribArray(mPositionHandle);
}

void on_surface_created() {

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void on_surface_changed() {

}

void on_draw_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}