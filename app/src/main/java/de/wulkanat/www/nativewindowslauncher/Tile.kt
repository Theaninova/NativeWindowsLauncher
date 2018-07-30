package de.wulkanat.www.nativewindowslauncher

import java.nio.ByteBuffer
import java.nio.FloatBuffer
import java.nio.ShortBuffer

class Tile(var posX: Int, var posY: Int, var spanX: Int, var spanY: Int) {
    var vertBuffer: FloatBuffer? = null
    var drawListBuffer: ShortBuffer? = null

    var renderVertBuffer: FloatBuffer? = null
    var renderDrawListBuffer: ShortBuffer? = null
}