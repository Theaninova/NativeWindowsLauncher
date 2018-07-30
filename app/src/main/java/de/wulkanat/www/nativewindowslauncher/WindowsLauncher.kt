package de.wulkanat.www.nativewindowslauncher

class WindowsLauncher() {
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