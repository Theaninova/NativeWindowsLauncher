package de.wulkanat.www.nativewindowslauncher

import android.content.Context
import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLRenderNative(mContext: Context, statusBarHeight: Int, navBarHeight: Int) : GLSurfaceView.Renderer {
    var mScreenWidth = 0
    var mScreenHeight = 0

    var fingerDown = false

    var xTouchPos = 0.0f
    var yTouchPos = 0.0f

    var xVelocityTouch = 0.0f
    var yVelocityTouch = 0.0f

    var dxTouch = 0.0f
    var dyTouch = 0.0f

    var glGrid = FloatArray(4);

    init {
        System.loadLibrary("GLRender")

        init(statusBarHeight, navBarHeight)
    }

    override fun onDrawFrame(p0: GL10?) {
        on_draw_frame(xTouchPos, yTouchPos, xVelocityTouch, yVelocityTouch, dxTouch, dyTouch, fingerDown)
    }

    override fun onSurfaceChanged(p0: GL10?, width: Int, height: Int) {
        mScreenWidth = width
        mScreenHeight = height

        glGrid = on_surface_changed(width, height)
    }

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        on_surface_created()
    }

    external fun on_surface_created()

    external fun on_surface_changed(width: Int, height: Int): FloatArray

    external fun on_draw_frame(mxTouchPos: Float, myTouchPos: Float, mxVelocityTouch: Float, myVelocityTouch: Float, mdxTouch: Float, mdyTouch: Float, mfingerDown: Boolean)

    external fun init(mStatusBarHeightPixels: Int, mNavBarHeightPixels: Int)

    external fun onPause()

    external fun onResume()
}