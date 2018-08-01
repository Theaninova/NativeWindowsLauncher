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

void init(int mStatusBarHeightPixels, int mNavBarHeightPixels) {
    mLastTime = std::chrono::high_resolution_clock::now();

    statusBarHeightPixels = mStatusBarHeightPixels;
    navBarHeightPixels = mNavBarHeightPixels;

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
        (JNIEnv * env, jclass cls, int mStatusBarHeightPixels, int mNavBarHeightPixels) {
    init(mStatusBarHeightPixels, mNavBarHeightPixels);
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1surface_1created
        (JNIEnv * env, jclass cls) {
    on_surface_created();
}

extern "C" JNIEXPORT void JNICALL Java_de_wulkanat_www_nativewindowslauncher_GLRenderNative_on_1surface_1changed
        (JNIEnv * env, jclass cls, jint width, jint height) {
    on_surface_changed(width, height);
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

void render(float m[]) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < tiles.size(); i++) {
        drawTile(&tiles[i], m);
    }
}

void on_surface_created() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLuint vertexShader = (GLuint) loadShader(GL_VERTEX_SHADER, &vs_SolidColor, &vs_SolidColorSize);
    GLuint fragmentShader = (GLuint) loadShader(GL_FRAGMENT_SHADER, &fs_SolidColor, &fs_SolidColorSize);

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

    glGrid[2] = -(((glGrid[1] - glGrid[0]) * mAspectRatio) / 2);
    glGrid[3] = -glGrid[2];

    statusBarHeightPercentage = statusBarHeightPixels / mScreenHeight;
    navBarHeightPercentage = navBarHeightPixels / mScreenHeight;

    cacheTileValues();

    glViewport(0, 0, (GLsizei) mScreenWidth, (GLsizei) mScreenHeight);

    for(int i = 0; i < 16; i++) {
        mtrxProjection[i] = 0.0f;
        mtrxView[i] = 0.0f;
        mtrxProjectionAndView[i] = 0.0f;
    }

    orthoM(mtrxProjection, 0, glGrid[0], glGrid[1], glGrid[3], glGrid[2], 1.0f, -1.0f);
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