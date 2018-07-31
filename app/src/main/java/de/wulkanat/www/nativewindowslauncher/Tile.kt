package de.wulkanat.www.nativewindowslauncher

import android.opengl.GLES20
import java.nio.FloatBuffer
import java.nio.ShortBuffer

class Tile(var posX: Int, var posY: Int, var spanX: Int, var spanY: Int) {
    var vertBuffer: FloatBuffer? = null
    var drawListBuffer: ShortBuffer? = null
    var colorBuffer: FloatArray? = null

    var renderVertBuffer: FloatBuffer? = null
    var renderDrawListBuffer: ShortBuffer? = null
    var renderColorBuffer: FloatArray? = null

    var currentZoom = 0.0f
}