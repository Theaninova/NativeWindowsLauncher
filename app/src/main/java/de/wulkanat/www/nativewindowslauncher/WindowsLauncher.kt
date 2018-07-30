package de.wulkanat.www.nativewindowslauncher

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

    var tiles = ArrayList<Tile>()

    var gridWidth: Int = 6
    var leftSideMargin: Float = 0.0104167f * 2//0.01041 6 Period
    var rightSideMargin: Float = 0.0118056f * 2//0.01180 5 Period
    var tilesMargin: Float = 0.0097222f * 2//0.0097 2 Period
    var topMargin: Float = tilesMargin
    var statusBarHeightPercentage: Float = 0.0f
    var statusBarHeight: Float = 0.0f

    var tileSizeCache = 0.0f
    var tileXPosChache = FloatArray(gridWidth)
    var tileAndMarginCache = 0.0f

    var glGrid: FloatArray = FloatArray(4)

    //Native functions for Calculating Animations
    external fun calcACache(a: Double, b: Double, x2: Double, y2: Double): Double
    external fun calcBCache(a: Double, b: Double, x2: Double, y2: Double): Double

    var A: Double = calcACache(fadeInNum1, fadeInNum2, fadeInLoc[0], fadeInLoc[1])

    // Used to load the 'native-lib' library on application startup.
    init {
        System.loadLibrary("native-lib")
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