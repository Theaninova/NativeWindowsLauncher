package de.wulkanat.www.nativewindowslauncher

import java.nio.ByteBuffer
import java.nio.ByteOrder

/*
CODE IS DEPRECATED

TO BE DELETED. USE C++ Version. Performance is 10-20 times better.
 */

/*class WindowsLauncher(val parent: GLRenderer) {
    companion object {
        val enterDuration = 0.62 //0.6
        //val enterRowZoomDifference = 2.0f
        //val enterRowZoomOffset = 0.01
        val relativeEnterRowZoomOffsets = floatArrayOf(0.01f, //0.01
                0.03f, 0.01f, //0.03, 0.01
                0.03f, 0.01f, //0.03, 0.01
                0.03f, 0.01f) //0.03, 0.01
                //0.021f, 0.01f)
        val initalZoom = 0.815f //0.185, Measured
        val fadeInEnd = 0.05f
        val fadeInStart = 0.185f //0.185, Measured

        val fadeInNum1 = 0.0
        val fadeInNum2 = 0.4 //0.3
        val fadeInNum3 = 7.2 //7.2
        val fadeInLoc = doubleArrayOf(0.68, 0.1) //0.68, 0.1


        val overscrollNum1 = 0.0
        val overscrollNum2 = 1.0
        val overscrollNum3 = 0.0
        val overscrollLoc = doubleArrayOf(0.71, 0.25)

        val exitDuration = 0.36
        val targetZoom = 1.5f
        val fadeOutEnd = 0.5f
        val fadeOutStart = 0.15f

        val appTileOffset = 2.0f
        val fadeOutNum1 = 0.0
        val fadeOutNum2 = 1.1
        val fadeOutNum3 = 1.5
        val fadeOutLoc = doubleArrayOf(0.43, 0.29)

        val inds = shortArrayOf(0, 1, 2, 0, 2, 3)

        val longTapDuraion = 0.75

        val editModeZoom = -0.1f
        val editModeSelectedZoom = -0.05f
        val editModeAlpha = 0.8f
        val editModeSelectedAlpha = 1.0f
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
    var navBarHeightPercentage: Float = 0.0f
    var navBarHeight: Float = 0.0f
    var overscrollDist: Float = 0.2090278f * 2 - topMargin //0,20902 / Period
    val overscrollDuration = 0.5 //0.25
    var todoOverscrollDist = 0.0f
    var overscrollElapsed = 0.0

    var gridOverscrollHeight = 0.0f
    var gridHeight = 0.0f
    set (value) {
        field = value
        gridOverscrollHeight = (value - (glGrid[3] - glGrid[2] - statusBarHeight - navBarHeight)) * -1
    }
    var gridHeightSpan = 0

    var scrollDist = 0.0f

    var tileSizeCache = 0.0f
    var tileXPosChache = FloatArray(gridWidth)
    var tileAndMarginCache = 0.0f

    var glGrid: FloatArray = FloatArray(4)

    var startTileIndex = 0
    var rowsOnScreen = 0.0f
    var animProgress = 0.0
    var enterTemporalOffsets = DoubleArray(relativeEnterRowZoomOffsets.size)
    var fadeInInterpolators = ArrayList<AccExpInterpolator>()

    var exiting = false
    var entering = false

    val tapTolerance = 0.0005f
    var tapPosition  = FloatArray(2)
    var tapInitiated = false
    var timeSinceTap = 0.0

    var exitStartPos = 0.0f
    var exitAnimTime = 0.0
    var exitTapTileLoc = IntArray(2)

    var appDrawer = false
    var editMode = false
    var editModeSelectedTile = 0

    init {
        addTile(Tile(0, 0, 1, 1))
        addTile(Tile(1, 0, 1, 1))
        addTile(Tile(0, 1, 1, 1))
        addTile(Tile(1, 1, 1, 1))
        addTile(Tile(2, 0, 2, 2))
        addTile(Tile(4, 0, 2, 2))
        addTile(Tile(0, 2, 2, 2))
        addTile(Tile(2, 2, 4, 2))
        addTile(Tile(0, 4, 2, 2))
        addTile(Tile(2, 4, 1, 1))
        addTile(Tile(3, 4, 1, 1))
        addTile(Tile(2, 5, 1, 1))
        addTile(Tile(3, 5, 1, 1))
        addTile(Tile(4, 4, 2, 2))
        addTile(Tile(0, 6, 4, 2))
        addTile(Tile(4, 6, 2, 2))
        addTile(Tile(0, 8, 2, 2))
        addTile(Tile(2, 8, 2, 2))
        addTile(Tile(4, 8, 1, 1))
        addTile(Tile(5, 8, 1, 1))
        addTile(Tile(4, 9, 1, 1))
        addTile(Tile(5, 9, 1, 1))
        addTile(Tile(0, 10, 2, 2))
        addTile(Tile(2, 10, 4, 2))
        addTile(Tile(0, 12, 1, 1))
        addTile(Tile(1, 12, 1, 1))
        addTile(Tile(2, 12, 2, 2))
        addTile(Tile(4, 12, 2, 2))
        addTile(Tile(0, 13, 2, 2))
        addTile(Tile(0, 15, 1, 1))
        addTile(Tile(1, 15, 1, 1))
        addTile(Tile(2, 14, 2, 2))
        addTile(Tile(4, 14, 1, 1))
        addTile(Tile(5, 14, 1, 1))
        addTile(Tile(4, 15, 1, 1))
        addTile(Tile(5, 15, 1, 1))
        addTile(Tile(0, 16, 2, 2))
        addTile(Tile(2, 16, 4, 2))
    }

    fun addTile(tile: Tile) {
        if (tile.posY + tile.spanY > gridHeightSpan) {
            gridHeightSpan = tile.posY + tile.spanY
            gridHeight = gridHeightSpan.toFloat() * tileAndMarginCache
        }
        tiles.add(tile)
    }

    fun initEnterAnimation() {
        animProgress = enterDuration
        entering = true
        exiting = false
        scrollDist = 0.0f

        enterTemporalOffsets = doubleArrayOf(0.0, enterDuration, enterDuration, enterDuration, enterDuration, enterDuration, enterDuration)

        fadeInInterpolators.clear()
        for (i in 0..(relativeEnterRowZoomOffsets.size - 1)) {

        }

        rowsOnScreen = Math.abs(glGrid[3] - glGrid[2]) / tileAndMarginCache
        startTileIndex = (((Math.abs(glGrid[3] - glGrid[2]) - statusBarHeight - topMargin + scrollDist)) / tileAndMarginCache).toInt()
    }

    fun initExitAnimation(location: IntArray) {
        animProgress = exitDuration
        entering = false
        exiting = true

        exitTapTileLoc = location

        rowsOnScreen = Math.abs(glGrid[3] - glGrid[2]) / tileAndMarginCache

        val x = (exitStartPos + location[1].toFloat() + appTileOffset) - rowsOnScreen
        if (x > 0) {
            rowsOnScreen += 2 * x
        }

        exitAnimTime = (exitDuration / 2) / rowsOnScreen
        exitStartPos = scrollDist / tileAndMarginCache
    }

    fun performNewEnterAnimation(progress: Double) {
        val zoomCache = FloatArray(enterTemporalOffsets.size)
        val alphaCache = FloatArray(enterTemporalOffsets.size)

        for (i in 0..(enterTemporalOffsets.size - 1)) {
            if (progress <= enterDuration - enterTemporalOffsets[i])
                zoomCache[i] = 1f - (fadeInInterpolator.getMulti(progress, enterDuration - enterTemporalOffsets[i]).toFloat() * (1f - initalZoom))

            if (i + 1 < enterTemporalOffsets.size && enterTemporalOffsets[i + 1] == enterDuration &&
                    zoomCache[i] >= initalZoom + relativeEnterRowZoomOffsets[i]/*(i.toFloat() + 1.0f) * enterRowZoomOffset*/) {
                enterTemporalOffsets[i + 1] = enterDuration - progress
            }

            alphaCache[i] = (zoomCache[i] - (1f - fadeInStart)) / ((1f - fadeInEnd) - (1f - fadeInStart))
            if (zoomCache[i] > 1f - fadeInEnd) {
                alphaCache[i] = 1f
            } else if (zoomCache[i] < 1f - fadeInStart) {
                alphaCache[i] = 0f
            }
        }

        for (tile in tiles.indices) {
            var tileOffset = (startTileIndex) - (tiles[tile].posY + tiles[tile].spanY)
            if (tileOffset < 0)
                tileOffset = 0
            else if (tileOffset >= enterTemporalOffsets.size)
                tileOffset = enterTemporalOffsets.size - 1

            calculateTile(tile, zoomCache[tileOffset], floatArrayOf(0.24313f, 0.396078f, 1.0f, alphaCache[tileOffset]))
        }
    }

    fun performExitAnimation(progress: Double) {
        for (tile in tiles.indices) {
            if (tiles[tile].posY >= exitStartPos) {
                var tileTime = 2 * (exitDuration - progress - (tiles[tile].posY.toFloat() - exitStartPos) * exitAnimTime)

                if (tiles[tile].posX == exitTapTileLoc[0] && tiles[tile].posY == exitTapTileLoc[1]) {
                    tileTime -= appTileOffset * exitAnimTime;
                }

                var newZoom = 1f
                if (tileTime > 0.0)
                    newZoom = 1f + fadeOutInterpolator.getMulti(tileTime, exitDuration).toFloat() * (targetZoom - 1f)

                var alpha = 1f - (newZoom - (1f + fadeOutStart)) / ((fadeOutEnd + 1f) - (fadeOutStart + 1f))
                if (newZoom > 1f + fadeOutEnd) {
                    alpha = 0f
                } else if (newZoom < 1 + fadeOutStart) {
                    alpha = 1f
                }

                calculateTile(tile, newZoom, floatArrayOf(0.24313f, 0.396078f, 1.0f, alpha))
            }
        }
    }

    fun update(elapsed: Double) {
        handleTouch(elapsed)

        if (animProgress <= 0.0) {
            if (exiting) {
                initEnterAnimation()
                performNewEnterAnimation(animProgress)
            } else {
                for (tile in tiles.indices) {
                    calculateTile(tile, 1.0f, floatArrayOf(0.24313f, 0.396078f, 1.0f, 1.0f))
                }
            }
        } else {
            if (entering) {
                performNewEnterAnimation(animProgress)
            } else if (exiting) {
                performExitAnimation(animProgress)
            }

            animProgress -= elapsed
        }

        if (tapInitiated) {
            timeSinceTap += elapsed
        } else {
            timeSinceTap = 0.0
        }

        for (tile in tiles) {
            //Swap buffers in tiles
            tile.renderDrawListBuffer = tile.drawListBuffer
            tile.renderVertBuffer = tile.vertBuffer
            tile.renderColorBuffer = tile.colorBuffer
        }
    }

    fun tileTouched(tile: Tile): Boolean {
        val t = floatArrayOf(
                tileXPosChache[tile.posX],
                glGrid[2] + topMargin + tile.posY.toFloat() * tileAndMarginCache + scrollDist + statusBarHeight,
                tileSizeCache + (tile.spanX - 1).toFloat() * tileAndMarginCache,
                tileSizeCache + (tile.spanY - 1).toFloat() * tileAndMarginCache
        )

        return parent.xTouchPos > t[0] &&
               parent.xTouchPos < t[0] + t[2] &&
               -parent.yTouchPos > t[1] &&
               -parent.yTouchPos < t[1] + t[3]
    }

    fun onTapEvent(longTap: Boolean) {
        for (tile in tiles.indices) {
            if (tileTouched(tiles[tile])) {
                if (longTap) {
                    editMode = true
                    editModeSelectedTile = tile
                } else {
                    if (editMode)
                        editModeSelectedTile = tile
                    else
                        initExitAnimation(intArrayOf(tiles[tile].posX, tiles[tile].posY))
                }

                break
            }
        }
    }

    fun handleTouch(elapsed: Double) {
        if (Math.abs(parent.xTouchPos - tapPosition[0]) <= tapTolerance && Math.abs(parent.yTouchPos - tapPosition[1]) <= tapTolerance) {
            if (parent.fingerDown) {
                tapInitiated = true
                if (timeSinceTap > longTapDuraion)
                    onTapEvent(true)
            } else if (tapInitiated) {
                onTapEvent(false)
                tapInitiated = false
            }
        } else {
            tapInitiated = false
            tapPosition[0] = parent.xTouchPos
            tapPosition[1] = parent.yTouchPos
        }

        if ((scrollDist >= overscrollDist) || (scrollDist <= gridOverscrollHeight - overscrollDist)) {
            parent.yVelocityTouch = 0.0f
            parent.dyTouch = 0.0f
        } else if (scrollDist > 0) {
            scroll(elapsed, 6.0f)
            if (parent.fingerDown) {
                todoOverscrollDist = scrollDist
                overscrollElapsed = overscrollDuration
            }
        } else if (scrollDist < gridOverscrollHeight) {
            scroll(elapsed, 6.0f)
            if (parent.fingerDown) {
                todoOverscrollDist = scrollDist - gridOverscrollHeight
                overscrollElapsed = overscrollDuration
            }
        } else {
            scroll(elapsed, 1.0f)
        }

        if (!parent.fingerDown) {
            if (scrollDist > 0.0f && parent.yVelocityTouch > -1.0) {
                overscrollEffect(true, elapsed)
            } else if (scrollDist < gridOverscrollHeight && parent.yVelocityTouch < 1.0) {
                overscrollEffect(false, elapsed)
            } else {
                if (scrollDist > 0 || scrollDist < gridOverscrollHeight)
                    parent.yVelocityTouch -= elapsed.toFloat() * (parent.yVelocityTouch / 0.04f)
                else
                    parent.yVelocityTouch -= elapsed.toFloat() * (parent.yVelocityTouch / 0.4f)

                if (scrollDist > gridOverscrollHeight / 2)
                    todoOverscrollDist = scrollDist
                else
                    todoOverscrollDist = scrollDist - gridOverscrollHeight
                overscrollElapsed = overscrollDuration
            }
        }
    }

    fun scroll(elapsed: Double, divideBy: Float) {
        if (parent.fingerDown) {
            scrollDist -= parent.dyTouch / divideBy
        } else {
            scrollDist -= (parent.yVelocityTouch / divideBy) * elapsed.toFloat()
        }
    }

    fun overscrollEffect(top: Boolean, elapsed: Double) {
        if (top)
            scrollDist = todoOverscrollDist * overscrollInterpolator.getMulti(overscrollElapsed, overscrollDuration).toFloat()
        else
            scrollDist = gridOverscrollHeight + (todoOverscrollDist * overscrollInterpolator.getMulti(overscrollElapsed, overscrollDuration).toFloat())

        if (overscrollElapsed <= 0) {
            todoOverscrollDist = 0.0f
            if (top)
                scrollDist = 0.0f
            else
                scrollDist = gridOverscrollHeight
            parent.yVelocityTouch = 0.0f
        } else {
            overscrollElapsed -= elapsed
        }
    }

    fun calculateTile(tile: Int, origZoom: Float, color: FloatArray) {
        tiles[tile].colorBuffer = color

        var additionalZoom = 0.0f
        if (editMode) {
            additionalZoom = editModeZoom
            tiles[tile].colorBuffer!![3] = editModeAlpha
            if (tile == editModeSelectedTile) {
                additionalZoom = editModeSelectedZoom
                tiles[tile].colorBuffer!![3] = editModeSelectedAlpha
            }
        }

        val zoom = origZoom + additionalZoom

        val yPos = (glGrid[2] + topMargin + tiles[tile].posY.toFloat() * tileAndMarginCache + scrollDist + statusBarHeight) * zoom
        val xPos = tileXPosChache[tiles[tile].posX] * zoom
        val xSize = (tileSizeCache + (tiles[tile].spanX - 1).toFloat() * tileAndMarginCache) * zoom
        val ySize = (tileSizeCache + (tiles[tile].spanY - 1).toFloat() * tileAndMarginCache) * zoom

        var zPos = 0.5f + ((1f / zoom) / 2f)
        if (zoom < 1f)
            zPos = 0.5f - ((1f - zoom) / 2f)

        val verts = floatArrayOf(
                xPos        , yPos        , zPos,
                xPos + xSize, yPos        , zPos,
                xPos + xSize, yPos + ySize, zPos,
                xPos        , yPos + ySize, zPos
        )

        val bb = ByteBuffer.allocateDirect(verts.size * 4)
        bb.order(ByteOrder.nativeOrder())
        tiles[tile].vertBuffer = bb.asFloatBuffer()
        tiles[tile].vertBuffer!!.put(verts)
        tiles[tile].vertBuffer!!.position(0)

        val dlb = ByteBuffer.allocateDirect(inds.size * 2)
        dlb.order(ByteOrder.nativeOrder())
        tiles[tile].drawListBuffer = dlb.asShortBuffer()
        tiles[tile].drawListBuffer!!.put(inds)
        tiles[tile].drawListBuffer!!.position(0)
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
        navBarHeight = (glGrid[3] - glGrid[2]) * navBarHeightPercentage

        gridHeight = gridHeightSpan.toFloat() * tileAndMarginCache
    }
}*/