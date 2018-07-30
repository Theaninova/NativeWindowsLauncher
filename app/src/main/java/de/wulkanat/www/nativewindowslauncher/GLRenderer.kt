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

    init {
        mLastTime = System.currentTimeMillis()
    }

    fun onPause() {

    }

    fun onResume() {
        mLastTime = System.currentTimeMillis()
    }

    override fun onDrawFrame(p0: GL10?) {
        val now = System.currentTimeMillis()
        if (now == mLastTime) return
        val elapsed = now - mLastTime

        windowsLauncher.update(elapsed.toDouble() / 1000)

        render(mtrxProjectionAndView)

        mLastTime = now
    }

    private fun render(m: FloatArray) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT or GLES20.GL_DEPTH_BUFFER_BIT)

        for (tile in windowsLauncher.tiles) {
            drawTile(tile, m)
        }

        /*drawTile(arrayOf(intArrayOf(0, 0), intArrayOf(1, 1)), 1.0f, 1.0f, m)
        drawTile(arrayOf(intArrayOf(1, 0), intArrayOf(1, 1)), 1.0f, 1.0f, m)
        drawTile(arrayOf(intArrayOf(0, 1), intArrayOf(1, 1)), 1.0f, 1.0f, m)
        drawTile(arrayOf(intArrayOf(1, 1), intArrayOf(1, 1)), 1.0f, 1.0f, m)
        drawTile(arrayOf(intArrayOf(2, 0), intArrayOf(2, 2)), 1.0f, 1.0f, m)
        drawTile(arrayOf(intArrayOf(4, 0), intArrayOf(2, 2)), 1.0f, 1.0f, m)
        drawTile(arrayOf(intArrayOf(0, 2), intArrayOf(2, 2)), 1.0f, 1.0f, m)
        drawTile(arrayOf(intArrayOf(2, 2), intArrayOf(4, 2)), 1.0f, 1.0f, m)*/
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        mScreenWidth = width.toFloat()
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
        Matrix.multiplyMM(mtrxProjectionAndView, 0, mtrxProjection, 0, mtrxView, 0)
    }

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        //setupTriangle()

        GLES20.glClearColor(0f, 0f, 1f, 1f)

        val vertexShader = RiGraphicTools.loadShader(GLES20.GL_VERTEX_SHADER, RiGraphicTools.vs_SolidColor)
        val fragmentShader = RiGraphicTools.loadShader(GLES20.GL_FRAGMENT_SHADER, RiGraphicTools.fs_SolidColor)

        RiGraphicTools.sp_SolidColor = GLES20.glCreateProgram()
        GLES20.glAttachShader(RiGraphicTools.sp_SolidColor, vertexShader)
        GLES20.glAttachShader(RiGraphicTools.sp_SolidColor, fragmentShader)
        GLES20.glLinkProgram(RiGraphicTools.sp_SolidColor)

        GLES20.glUseProgram(RiGraphicTools.sp_SolidColor)
    }

    fun drawTile(tile: Tile, m: FloatArray) {
        val mPositionHandle = GLES20.glGetAttribLocation(RiGraphicTools.sp_SolidColor, "vPosition")
        GLES20.glEnableVertexAttribArray(mPositionHandle)
        GLES20.glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GLES20.GL_FLOAT, false, vertexStride, tile.renderVertBuffer)

        val mtrxhandle = GLES20.glGetUniformLocation(RiGraphicTools.sp_SolidColor, "uMVPMatrix")
        GLES20.glUniformMatrix4fv(mtrxhandle, 1, false, m, 0)
        GLES20.glDrawElements(GLES20.GL_TRIANGLES, inds.size, GLES20.GL_UNSIGNED_SHORT, tile.renderDrawListBuffer)
        GLES20.glDisableVertexAttribArray(mPositionHandle)
    }

    /*fun drawTile(tile: Array<IntArray>, zoom: Float, alpha: Float, m: FloatArray) {
        val yOffset = 0.0f
        val yPos = (glGrid[2] + windowsLauncher.topMargin + tile[0][1] * windowsLauncher.tileAndMarginCache + yOffset + windowsLauncher.statusBarHeight) * zoom
        val xPos = windowsLauncher.tileXPosChache[tile[0][0]] * zoom
        val xSize = (windowsLauncher.tileSizeCache + (tile[1][0] - 1) * windowsLauncher.tileAndMarginCache) * zoom
        val ySize = (windowsLauncher.tileSizeCache + (tile[1][1] - 1) * windowsLauncher.tileAndMarginCache) * zoom

        val zPos = 1 - 1 / zoom
        if (zoom < 0)
            zPos -(1 - zoom)

        val verts = floatArrayOf(
                xPos        , yPos        , zPos,
                xPos + xSize, yPos        , zPos,
                xPos + xSize, yPos + ySize, zPos,
                xPos        , yPos + ySize, zPos
        )

        val bb = ByteBuffer.allocateDirect(verts.size * 4)
        bb.order(ByteOrder.nativeOrder())
        val vertBuffer = bb.asFloatBuffer()
        vertBuffer.put(verts)
        vertBuffer.position(0)

        val dlb = ByteBuffer.allocateDirect(inds.size * 2)
        dlb.order(ByteOrder.nativeOrder())
        val drawListBuffer = dlb.asShortBuffer()
        drawListBuffer.put(inds)
        drawListBuffer.position(0)

        val mPositionHandle = GLES20.glGetAttribLocation(RiGraphicTools.sp_SolidColor, "vPosition")
        GLES20.glEnableVertexAttribArray(mPositionHandle)
        GLES20.glVertexAttribPointer(mPositionHandle, 3, GLES20.GL_FLOAT, false,0, vertBuffer)

        val mtrxhandle = GLES20.glGetUniformLocation(RiGraphicTools.sp_SolidColor, "uMVPMatrix")
        GLES20.glUniformMatrix4fv(mtrxhandle, 1, false, m, 0)
        GLES20.glDrawElements(GLES20.GL_TRIANGLES, inds.size, GLES20.GL_UNSIGNED_SHORT, drawListBuffer)
        GLES20.glDisableVertexAttribArray(mPositionHandle)
    }*/
}