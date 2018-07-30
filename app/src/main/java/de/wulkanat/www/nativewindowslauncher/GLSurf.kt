package de.wulkanat.www.nativewindowslauncher

import android.content.Context
import android.graphics.PixelFormat
import android.opengl.GLSurfaceView
import android.view.MotionEvent
import android.R.attr.x
import android.R.attr.y



class GLSurf(context: Context, statusBarHeightPixels: Int) : GLSurfaceView(context) {
    val mRenderer = GLRenderer(context, statusBarHeightPixels)
    var previousX = 0.0f
    var previousY = 0.0f

    init {
        setEGLContextClientVersion(2)
        setRenderer(mRenderer)
        //setEGLConfigChooser(8, 8, 8, 8, 16, 0)
        //holder.setFormat(PixelFormat.TRANSLUCENT)
        renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY
    }

    override fun onPause() {
        super.onPause()
        mRenderer.onPause();
    }

    override fun onResume() {
        super.onResume()
        mRenderer.onResume();
    }

    override fun onTouchEvent(e: MotionEvent?): Boolean {
        when (e!!.action) {
            MotionEvent.ACTION_MOVE -> {

                mRenderer.dxTouch = e.x - previousX
                mRenderer.dyTouch = e.y - previousY
            }

            else -> {
                mRenderer.dxTouch = 0.0f
                mRenderer.dyTouch = 0.0f
            }
        }

        previousX = e.x
        previousY = e.y

        return true
    }
}