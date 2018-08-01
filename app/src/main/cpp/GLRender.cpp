//
// Created by wulkanat on 31/07/2018.
//

#include "GLRender.h"
#include "Matrix.h"
#include <jni.h>
#include <string>

static GLenum sp_SolidColor = 0;

const static GLchar * vs_SolidColor =
                "uniform mat4 uMVPMatrix; "
                "attribute vec4 vPosition; "
                "void main() { "
                    "gl_Position = uMVPMatrix * vPosition; "
                "}";
//const static GLint vs_SolidColorSize = sizeof(vs_SolidColor) / sizeof(GLchar);

const static GLchar * fs_SolidColor =
                "precision mediump float; "
                "uniform vec4 uColor; "
                "void main() { "
                    "gl_FragColor = uColor; "
                "}";
//const static GLint fs_SolidColorSize = sizeof(fs_SolidColor) / sizeof(GLchar);


static GLint loadShader(GLenum type, const GLchar ** shaderCode) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, shaderCode, NULL);
    glCompileShader(shader);

    return shader;
}

void init(int mStatusBarHeightPixels, int mNavBarHeightPixels) {
    mLastTime = std::chrono::high_resolution_clock::now();

    statusBarHeightPixels = mStatusBarHeightPixels;
    navBarHeightPixels = mNavBarHeightPixels;



    windows_launcher_init(&sharedValues);
}

void onPause() {

}

void onResume() {
    mLastTime = std::chrono::high_resolution_clock::now();
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_init
        (JNIEnv * env, jclass cls, int mStatusBarHeightPixels, int mNavBarHeightPixels) {
    init(mStatusBarHeightPixels, mNavBarHeightPixels);
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1surface_1created
        (JNIEnv * env, jclass cls) {
    on_surface_created();
}

extern "C" JNIEXPORT jfloatArray JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1surface_1changed
        (JNIEnv * env, jclass cls, int width, int height) {
    on_surface_changed(width, height);

    jfloatArray result = env->NewFloatArray(4);
    jfloat array1[4];

    array1[0] = sharedValues.glGrid[0];
    array1[1] = sharedValues.glGrid[1];
    array1[2] = sharedValues.glGrid[2];
    array1[3] = sharedValues.glGrid[3];

    env->SetFloatArrayRegion(result, 0, 4, array1);

    return result;
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1draw_1frame
        (JNIEnv * env, jclass cls, float mxTouchPos, float myTouchPos, float mxVelocityTouch, float myVelocityTouch, float mdxTouch, float mdyTouch, bool mfingerDown, bool fingerMoved) {
    if (mfingerDown) {
        sharedValues.xTouchPos = mxTouchPos;
        sharedValues.yTouchPos = myTouchPos;
        sharedValues.xVelocityTouch = mxVelocityTouch;
        sharedValues.yVelocityTouch = myVelocityTouch;
        sharedValues.dxTouch = mdxTouch;
        sharedValues.dyTouch = mdyTouch;
    }
    sharedValues.fingerDown = mfingerDown;
    sharedValues.fingerMoved = fingerMoved;

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

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_onBackPressed
        (JNIEnv * env, jclass cls) {
    sharedValues.editMode = false;
}

void drawTile(Tile * tile, float m[]) {
    GLuint mPositionHandle = (GLuint) glGetAttribLocation(sp_SolidColor, "vPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, vertexStride, tile->renderVertBuffer);

    GLint colorHandle = glGetUniformLocation(sp_SolidColor, "uColor");
    glUniform4fv(colorHandle, 1, tile->renderColorBuffer);

    GLint mtrxhandle = glGetUniformLocation(sp_SolidColor, "uMVPMatrix");
    glUniformMatrix4fv(mtrxhandle, 1, GL_FALSE, m);
    glDrawElements(GL_TRIANGLES, sharedValues.indsSize, GL_UNSIGNED_SHORT, tile->renderDrawListBuffer);
    glDisableVertexAttribArray(mPositionHandle);
}

void render(float m[]) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < sharedValues.tiles.size(); i++) {
        drawTile(&sharedValues.tiles[i], m);
    }
}

void on_surface_created() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLuint vertexShader = (GLuint) loadShader(GL_VERTEX_SHADER, &vs_SolidColor);
    GLuint fragmentShader = (GLuint) loadShader(GL_FRAGMENT_SHADER, &fs_SolidColor);

    sp_SolidColor = glCreateProgram();
    glAttachShader(sp_SolidColor, vertexShader);
    glAttachShader(sp_SolidColor, fragmentShader);
    glLinkProgram(sp_SolidColor);

    glUseProgram(sp_SolidColor);
}

void on_surface_changed(int width, int height) {
    mScreenWidth = (float) width;
    mScreenHeight = (float) height;

    mAspectRatio = mScreenHeight / mScreenWidth;

    sharedValues.glGrid[2] = -1.0f * (((sharedValues.glGrid[1] - sharedValues.glGrid[0]) * mAspectRatio) / 2.0f);
    sharedValues.glGrid[3] = -1.0f * sharedValues.glGrid[2];

    sharedValues.statusBarHeightPercentage = statusBarHeightPixels / mScreenHeight;
    sharedValues.navBarHeightPercentage = navBarHeightPixels / mScreenHeight;

    cacheTileValues();

    glViewport(0, 0, (GLsizei) mScreenWidth, (GLsizei) mScreenHeight);

    for(int i = 0; i < 16; i++) {
        mtrxProjection[i] = 0.0f;
        mtrxView[i] = 0.0f;
        mtrxProjectionAndView[i] = 0.0f;
    }

    orthoM(mtrxProjection, 0, sharedValues.glGrid[0], sharedValues.glGrid[1], sharedValues.glGrid[3], sharedValues.glGrid[2], 1.0f, -1.0f);
    setLookAtM(mtrxView, 0, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    multiplyMM(mtrxProjectionAndView, mtrxProjection, mtrxView);
}

void on_draw_frame() {
    auto now = std::chrono::high_resolution_clock::now();
    if (now == mLastTime) return;

    std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastTime);

    update(elapsed.count() / 1000.0);

    render(mtrxProjectionAndView);

    mLastTime = now;
}