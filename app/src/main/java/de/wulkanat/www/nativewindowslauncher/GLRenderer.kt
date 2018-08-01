package de.wulkanat.www.nativewindowslauncher

import android.content.Context
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.opengl.Matrix
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLRenderer(mContext: Context, val statusBarHeightPixels: Int, val navBarHeightPixels: Int) : GLSurfaceView.Renderer {
    private val mtrxProjection = FloatArray(16)
    private val mtrxView = FloatArray(16)
    private val mtrxProjectionAndView = FloatArray(16)

    var dxTouch: Float = 0.0f
    var dyTouch: Float = 0.0f

    var xTouchPos: Float = 0.0f
    var yTouchPos: Float = 0.0f

    //glGrid units per second per second
    var xVelocityTouch: Float = 0.0f
    var yVelocityTouch: Float = 0.0f
    var fingerDown = false

    var glGrid = floatArrayOf(-1.0f, 1.0f, 1.0f, -1.0f)

    val COORDS_PER_VERTEX = 3
    val vertexStride = COORDS_PER_VERTEX * 4
    val inds = shortArrayOf(0, 1, 2, 0, 2, 3)

    var mScreenWidth: Float = 1080f
    var mScreenHeight: Float = 1920f
    var mAspectRatio: Float = 16f / 9f

    var mLastTime: Long = 0
    var mProgram: Int? = null

    var windowsLauncher = WindowsLauncher(this)
    var nativeRenderer = GLRenderNative(statusBarHeightPixels, navBarHeightPixels)

    init {
        mLastTime = System.currentTimeMillis()
    }

    fun onPause() {

    }

    fun onResume() {
        mLastTime = System.currentTimeMillis()
        //windowsLauncher.initEnterAnimation()
    }

    override fun onDrawFrame(p0: GL10?) {
        /*val now = System.currentTimeMillis()
        if (now == mLastTime) return
        val elapsed = now - mLastTime

        windowsLauncher.update(elapsed.toDouble() / 1000)

        render(mtrxProjectionAndView)

        mLastTime = now*/
        nativeRenderer.on_draw_frame()
    }

    private fun render(m: FloatArray) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT or GLES20.GL_DEPTH_BUFFER_BIT)

        for (tile in windowsLauncher.tiles) {
            drawTile(tile, m)
        }
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        /*mScreenWidth = width.toFloat()
        mScreenHeight = height.toFloat()

        mAspectRatio = mScreenHeight / mScreenWidth

        glGrid[2] = -(((glGrid[1] - glGrid[0]) * mAspectRatio) / 2)
        glGrid[3] = -glGrid[2]

        windowsLauncher.glGrid = glGrid

        windowsLauncher.statusBarHeightPercentage = statusBarHeightPixels.toFloat() / mScreenHeight
        windowsLauncher.navBarHeightPercentage = navBarHeightPixels.toFloat() / mScreenHeight

        windowsLauncher.cacheTileValues()

        GLES20.glViewport(0, 0, mScreenWidth.toInt(), mScreenHeight.toInt())

        for(i in 0..15) {
            mtrxProjection[i] = 0f
            mtrxView[i] = 0f
            mtrxProjectionAndView[i] = 0f
        }

        Matrix.orthoM(mtrxProjection, 0, glGrid[0], glGrid[1], glGrid[3], glGrid[2], 1f, -1f)
        Matrix.setLookAtM(mtrxView, 0, 0f, 0f, 1f, 0f, 0f, 0f, 0f, 1f, 0f)
        Matrix.multiplyMM(mtrxProjectionAndView, 0, mtrxProjection, 0, mtrxView, 0)*/
        nativeRenderer.on_surface_changed(width, height)
    }

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        /*GLES20.glEnable(GLES20.GL_BLEND)
        GLES20.glBlendFunc(GLES20.GL_SRC_ALPHA, GLES20.GL_ONE_MINUS_SRC_ALPHA)

        GLES20.glClearColor(0f, 0f, 0f, 1f)

        val vertexShader = RiGraphicTools.loadShader(GLES20.GL_VERTEX_SHADER, RiGraphicTools.vs_SolidColor)
        val fragmentShader = RiGraphicTools.loadShader(GLES20.GL_FRAGMENT_SHADER, RiGraphicTools.fs_SolidColor)

        RiGraphicTools.sp_SolidColor = GLES20.glCreateProgram()
        GLES20.glAttachShader(RiGraphicTools.sp_SolidColor, vertexShader)
        GLES20.glAttachShader(RiGraphicTools.sp_SolidColor, fragmentShader)
        GLES20.glLinkProgram(RiGraphicTools.sp_SolidColor)

        GLES20.glUseProgram(RiGraphicTools.sp_SolidColor)*/
        nativeRenderer.on_surface_created()
    }

    fun drawTile(tile: Tile, m: FloatArray) {
        val mPositionHandle = GLES20.glGetAttribLocation(RiGraphicTools.sp_SolidColor, "vPosition")
        GLES20.glEnableVertexAttribArray(mPositionHandle)
        GLES20.glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GLES20.GL_FLOAT, false, vertexStride, tile.renderVertBuffer)

        val colorhandle = GLES20.glGetUniformLocation(RiGraphicTools.sp_SolidColor, "uColor")
        GLES20.glUniform4fv(colorhandle, 1, tile.renderColorBuffer, 0)

        val mtrxhandle = GLES20.glGetUniformLocation(RiGraphicTools.sp_SolidColor, "uMVPMatrix")
        GLES20.glUniformMatrix4fv(mtrxhandle, 1, false, m, 0)
        GLES20.glDrawElements(GLES20.GL_TRIANGLES, inds.size, GLES20.GL_UNSIGNED_SHORT, tile.renderDrawListBuffer)
        GLES20.glDisableVertexAttribArray(mPositionHandle)
    }
}