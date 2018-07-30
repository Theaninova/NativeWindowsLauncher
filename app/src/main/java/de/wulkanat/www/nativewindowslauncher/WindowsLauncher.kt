package de.wulkanat.www.nativewindowslauncher

import java.nio.ByteBuffer
import java.nio.ByteOrder

class WindowsLauncher() {
    companion object {
        val enterDuration = 0.5
        val enterRowZoomDifference = 0.075f
        val initalZoom = 0.6f
        val fadeInEnd = 0.05f
        val fadeInStart = 0.15f

        val fadeInNum1 = 0.0
        val fadeInNum2 = 0.6
        val fadeInNum3 = 7.5
        val fadeInLoc = doubleArrayOf(0.8, 0.2)


        val overscrollNum1 = 0.0
        val overscrollNum2 = 3.2
        val overscrollNum3 = 0.0
        val overscrollLoc = doubleArrayOf(0.5, 0.5)

        val exitDuration = 0.36
        val targetZoom = 3.0f
        val fadeOutDist = 0.5f
        val fadeOutStart = 0.15f

        val appTileOffset = 2.0f
        val fadeOutNum1 = 0.0
        val fadeOutNum2 = 1.1
        val fadeOutNum3 = 1.5
        val fadeOutLoc = doubleArrayOf(0.43, 0.29)
    }

    var fadeInInterpolator = AccExpInterpolator(fadeInNum1, fadeInNum2, fadeInNum3, fadeInLoc)
    var fadeOutInterpolator = AccExpInterpolator(fadeOutNum1, fadeOutNum2, fadeOutNum3, fadeOutLoc)
    var overscrollInterpolator = AccExpInterpolator(overscrollNum1, overscrollNum2, overscrollNum3, overscrollLoc)

    var tiles = ArrayList<Tile>()

    var gridWidth: Int = 6
    var leftSideMargin: Float = 0.0104167f * 2//0.01041 6 Period
    var rightSideMargin: Float = 0.0118056f * 2//0.01180 5 Period
    var tilesMargin: Float = 0.0097222f * 2//0.0097 2 Period
    var topMargin: Float = tilesMargin
    var statusBarHeightPercentage: Float = 0.0f
    var statusBarHeight: Float = 0.0f
    set (value) {
        field = value
        overscrollDist = 0.2090278f * 2 - topMargin - value
    }
    var overscrollDist: Float = 0.2090278f * 2 - topMargin //0,20902 / Period
    val overscrollDuration = 0.25
    var todoOverscrollDist = 0.0f
    var overscrollElapsed = 0.0

    var scrollDist = 0.0f

    var tileSizeCache = 0.0f
    var tileXPosChache = FloatArray(gridWidth)
    var tileAndMarginCache = 0.0f

    var glGrid: FloatArray = FloatArray(4)

    val inds = shortArrayOf(0, 1, 2, 0, 2, 3)

    //Native functions for Calculating Animations
    external fun calcACache(a: Double, b: Double, x2: Double, y2: Double): Double
    external fun calcBCache(a: Double, b: Double, x2: Double, y2: Double): Double
    external fun expAccInterpolator(precalc_a: Double, precalc_b: Double, initial_a: Double, s: Double): Double

    var in_precalc_a = 0.0
    var in_precalc_b = 0.0
    var in_precalc_c = 0.0
    var in_precalc_d = 0.0

    var overscroll_precalc_a = 0.0
    var overscroll_precalc_b = 0.0
    var overscroll_precalc_c = 0.0
    var overscroll_precalc_d = 0.0

    // Used to load the 'native-lib' library on application startup.
    init {
        System.loadLibrary("native-lib")

        in_precalc_a = calcACache(fadeInNum1, fadeInNum2, fadeInLoc[0], fadeInLoc[1])
        in_precalc_b = calcBCache(fadeInNum1, fadeInNum2, fadeInLoc[0], fadeInLoc[1])

        in_precalc_c = calcACache(fadeInNum3, fadeInNum2, 1 - fadeInLoc[0], 1 - fadeInLoc[1])
        in_precalc_d = calcBCache(fadeInNum3, fadeInNum2, 1 - fadeInLoc[0], 1 - fadeInLoc[1])

        overscroll_precalc_a = calcACache(overscrollNum1, overscrollNum2, overscrollLoc[0], overscrollLoc[1])
        overscroll_precalc_b = calcACache(overscrollNum1, overscrollNum2, overscrollLoc[0], overscrollLoc[1])

        overscroll_precalc_c = calcACache(overscrollNum3, overscrollNum2, 1 - overscrollLoc[0], 1 - overscrollLoc[1])
        overscroll_precalc_d = calcACache(overscrollNum3, overscrollNum2, 1 - overscrollLoc[0], 1 - overscrollLoc[1])

        tiles.add(Tile(0, 0, 1, 1))
        tiles.add(Tile(1, 0, 1, 1))
        tiles.add(Tile(0, 1, 1, 1))
        tiles.add(Tile(1, 1, 1, 1))
        tiles.add(Tile(2, 0, 2, 2))
        tiles.add(Tile(4, 0, 2, 2))
        tiles.add(Tile(0, 2, 2, 2))
        tiles.add(Tile(2, 2, 4, 2))
        tiles.add(Tile(0, 4, 2, 2))
        tiles.add(Tile(2, 4, 1, 1))
        tiles.add(Tile(3, 4, 1, 1))
        tiles.add(Tile(2, 5, 1, 1))
        tiles.add(Tile(3, 5, 1, 1))
        tiles.add(Tile(4, 4, 2, 2))
        tiles.add(Tile(0, 6, 4, 2))
        tiles.add(Tile(4, 6, 2, 2))
        tiles.add(Tile(0, 8, 2, 2))
        tiles.add(Tile(2, 8, 2, 2))
        tiles.add(Tile(4, 8, 1, 1))
        tiles.add(Tile(5, 8, 1, 1))
        tiles.add(Tile(4, 9, 1, 1))
        tiles.add(Tile(5, 9, 1, 1))
        tiles.add(Tile(0, 10, 2, 2))
        tiles.add(Tile(2, 10, 4, 2))

    }

    fun performEnterAnimation(progress: Double) {
        if (progress < fadeInLoc[0]) {
            expAccInterpolator(in_precalc_a, in_precalc_b, fadeInNum1, progress)
        } else {
            expAccInterpolator(in_precalc_c, in_precalc_d, fadeInNum3, progress)
        }
    }

    fun update(elapsed: Double, dxTouch: Float, dyTouch: Float) {
        if (scrollDist >= overscrollDist && dyTouch < 0) {

        } else if (scrollDist > 0.0f && dyTouch == 0.0f) {
            if (todoOverscrollDist == 0.0f) {
                todoOverscrollDist = scrollDist
                overscrollElapsed = overscrollDuration
            }

            scrollDist = todoOverscrollDist * overscrollInterpolator.getMulti(overscrollElapsed, overscrollDuration).toFloat()

            if (overscrollElapsed <= 0) {
                todoOverscrollDist = 0.0f
                scrollDist = 0.0f
            } else {
                overscrollElapsed -= elapsed
            }
        } else if (scrollDist > 0 && dyTouch < 0)
            scrollDist -= dyTouch / 6
        else
            scrollDist -= dyTouch

        for (tile in tiles) {
            //TODO: calc in seperate Thread
            calculateTile(tile, 1.0f)
        }

        //TODO: multithreading, check for GPU finished

        for (tile in tiles) {
            //Swap buffers in tiles
            tile.renderDrawListBuffer = tile.drawListBuffer
            tile.renderVertBuffer = tile.vertBuffer
        }
    }

    fun calculateTile(tile: Tile, zoom: Float) {
        val yPos = (glGrid[2] + topMargin + tile.posY.toFloat() * tileAndMarginCache + scrollDist + statusBarHeight) * zoom
        val xPos = tileXPosChache[tile.posX] * zoom
        val xSize = (tileSizeCache + (tile.spanX - 1).toFloat() * tileAndMarginCache) * zoom
        val ySize = (tileSizeCache + (tile.spanY - 1).toFloat() * tileAndMarginCache) * zoom

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
        tile.vertBuffer = bb.asFloatBuffer()
        tile.vertBuffer!!.put(verts)
        tile.vertBuffer!!.position(0)

        val dlb = ByteBuffer.allocateDirect(inds.size * 2)
        dlb.order(ByteOrder.nativeOrder())
        tile.drawListBuffer = dlb.asShortBuffer()
        tile.drawListBuffer!!.put(inds)
        tile.drawListBuffer!!.position(0)
    }

    fun cacheTileValues() {
        tileSizeCache = ((glGrid[1] - glGrid[0]) - leftSideMargin - rightSideMargin - (gridWidth - 1) * tilesMargin) / gridWidth

        tileAndMarginCache = tileSizeCache + tilesMargin

        tileXPosChache = FloatArray(gridWidth)

        var xPos = glGrid[0] + rightSideMargin
        for (i in 0..(gridWidth - 1)) {
            tileXPosChache[i] = xPos

            xPos += tileAndMarginCache
        }

        statusBarHeight = (glGrid[3] - glGrid[2]) * statusBarHeightPercentage
    }
}