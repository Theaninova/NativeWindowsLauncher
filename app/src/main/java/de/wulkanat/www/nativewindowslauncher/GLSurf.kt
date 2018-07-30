package de.wulkanat.www.nativewindowslauncher

import android.content.Context
import android.graphics.PixelFormat
import android.opengl.GLSurfaceView

class GLSurf(context: Context, statusBarHeightPixels: Int) : GLSurfaceView(context) {
    val mRenderer = GLRenderer(context, statusBarHeightPixels)

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
}