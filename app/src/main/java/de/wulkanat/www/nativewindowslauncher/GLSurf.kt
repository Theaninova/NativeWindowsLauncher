package de.wulkanat.www.nativewindowslauncher

import android.content.Context
import android.graphics.PixelFormat
import android.opengl.GLSurfaceView
import android.view.MotionEvent
import android.view.VelocityTracker


class GLSurf(context: Context, statusBarHeightPixels: Int, navBarHeightPixels: Int) : GLSurfaceView(context) {
    val mRenderer = GLRenderer(context, statusBarHeightPixels, navBarHeightPixels)
    var previousX = 0.0f
    var previousY = 0.0f

    var velocityTracker: VelocityTracker? = null

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
        if (velocityTracker == null)
            velocityTracker = VelocityTracker.obtain()

        when (e!!.action) {
            MotionEvent.ACTION_DOWN -> {
                velocityTracker!!.clear()

                mRenderer.fingerDown = true

                velocityTracker!!.addMovement(e)
            }

            MotionEvent.ACTION_MOVE -> {
                velocityTracker!!.addMovement(e)

                mRenderer.dxTouch = (e.x - previousX) / mRenderer.mScreenWidth * 2
                mRenderer.dyTouch = ((e.y - previousY)  / mRenderer.mScreenHeight) * (mRenderer.glGrid[2] - mRenderer.glGrid[3])

                velocityTracker!!.computeCurrentVelocity(1000)

                mRenderer.xVelocityTouch = (velocityTracker!!.xVelocity / mRenderer.mScreenWidth) * 2
                mRenderer.yVelocityTouch = (velocityTracker!!.yVelocity / mRenderer.mScreenWidth) * (mRenderer.glGrid[2] - mRenderer.glGrid[3])
            }

            MotionEvent.ACTION_UP -> {
                mRenderer.fingerDown = false

                //PX per second
                velocityTracker!!.computeCurrentVelocity(1000)

                mRenderer.xVelocityTouch = (velocityTracker!!.xVelocity / mRenderer.mScreenWidth) * 2
                mRenderer.yVelocityTouch = (velocityTracker!!.yVelocity / mRenderer.mScreenHeight) * (mRenderer.glGrid[2] - mRenderer.glGrid[3])

                mRenderer.dyTouch = 0.0f
                mRenderer.dxTouch = 0.0f
            }
        }

        previousX = e.x
        previousY = e.y

        return true
    }
}