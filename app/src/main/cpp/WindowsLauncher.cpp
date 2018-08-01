//
// Created by wulkanat on 01/08/2018.
//

#include "WindowsLauncher.h"


AccExpInterpolator fadeInInterpolator = AccExpInterpolator(fadeInNum1, fadeInNum2, fadeInNum3, fadeInLoc);
AccExpInterpolator fadeOutInterpolator = AccExpInterpolator(fadeOutNum1, fadeOutNum2, fadeOutNum3, fadeOutLoc);
AccExpInterpolator overscrollInterpolator = AccExpInterpolator(overscrollNum1, overscrollNum2, overscrollNum3, overscrollLoc);

/*
 * CALL THIS FIRST
 */

void addTile(Tile tile) {
    if (tile.posY + tile.spanY > gridHeightSpan) {
        gridHeightSpan = tile.posY + tile.spanY;
        gridHeight = (float) gridHeightSpan * tileAndMarginCache;
    }
    tiles.push_back(tile);
}

Tile initTile(int x, int y, int sx, int sy) {
    Tile out;

    out.posX = x;
    out.posY = y;
    out.spanX = sx;
    out.spanY = sy;

    return out;
}

void windows_launcher_init(Parent mParent) {
    parent = mParent;

    addTile(initTile(0, 0, 1, 1));
    addTile(initTile(1, 0, 1, 1));
    addTile(initTile(0, 1, 1, 1));
    addTile(initTile(1, 1, 1, 1));
    addTile(initTile(2, 0, 2, 2));
    addTile(initTile(4, 0, 2, 2));
    addTile(initTile(0, 2, 2, 2));
    addTile(initTile(2, 2, 4, 2));
    addTile(initTile(0, 4, 2, 2));
    addTile(initTile(2, 4, 1, 1));
    addTile(initTile(3, 4, 1, 1));
    addTile(initTile(2, 5, 1, 1));
    addTile(initTile(3, 5, 1, 1));
    addTile(initTile(4, 4, 2, 2));
    addTile(initTile(0, 6, 4, 2));
    addTile(initTile(4, 6, 2, 2));
    addTile(initTile(0, 8, 2, 2));
    addTile(initTile(2, 8, 2, 2));
    addTile(initTile(4, 8, 1, 1));
    addTile(initTile(5, 8, 1, 1));
    addTile(initTile(4, 9, 1, 1));
    addTile(initTile(5, 9, 1, 1));
    addTile(initTile(0, 10, 2, 2));
    addTile(initTile(2, 10, 4, 2));
    addTile(initTile(0, 12, 1, 1));
    addTile(initTile(1, 12, 1, 1));
    addTile(initTile(2, 12, 2, 2));
    addTile(initTile(4, 12, 2, 2));
    addTile(initTile(0, 13, 2, 2));
    addTile(initTile(0, 15, 1, 1));
    addTile(initTile(1, 15, 1, 1));
    addTile(initTile(2, 14, 2, 2));
    addTile(initTile(4, 14, 1, 1));
    addTile(initTile(5, 14, 1, 1));
    addTile(initTile(4, 15, 1, 1));
    addTile(initTile(5, 15, 1, 1));
    addTile(initTile(0, 16, 2, 2));
    addTile(initTile(2, 16, 4, 2));
}

/*
 * DO NOT OPTIMIZE MEMORY USAGE. FUNCTION WILL RUN SIMULTANEOUSLY IN MULTIPLE THREADS.
 */
void calculateTile(int tile, float origZoom, float color[4]) {
    memcpy(tiles[tile].colorBuffer, color, tiles[tile].colorBufferSize);

    float additionalZoom = 0.0f;
    if (editMode) {
        additionalZoom = editModeZoom;
        tiles[tile].colorBuffer[3] = editModeAlpha;
        if (tile == editModeSelectedTile) {
            additionalZoom = editModeSelectedZoom;
            tiles[tile].colorBuffer[3] = editModeSelectedAlpha;
        }
    }

    float zoom = origZoom + additionalZoom;

    float yPos = (*parent.glGrid[2] + topMargin + (float) tiles[tile].posY * tileAndMarginCache + scrollDist + statusBarHeight) * zoom;
    float xPos = tileXPosChache[tiles[tile].posX] * zoom;
    float xSize = (tileSizeCache + (float) (tiles[tile].spanX - 1) * tileAndMarginCache) * zoom;
    float ySize = (tileSizeCache + (float) (tiles[tile].spanY - 1) * tileAndMarginCache) * zoom;

    float zPos = 0.5f + ((1.0f / zoom) / 2.0f);
    if (zoom < 1.0f)
        zPos = 0.5f - ((1.0f - zoom) / 2.0f);

    float verticies[] = {
            xPos, yPos, zPos,
            xPos + xSize, yPos, zPos,
            xPos + xSize, yPos + ySize, zPos,
            xPos, yPos + ySize, zPos
    };

    memcpy(tiles[tile].vertBuffer, verticies, tiles[tile].vertBufferSize);

    memcpy(tiles[tile].drawListBuffer, *parent.inds, tiles[tile].drawListBufferSize);
}

void initEnterAnimation() {
    animProgress = enterDuration;
    entering = true;
    exiting = false;
    scrollDist = 0.0f;

    enterTemporalOffsets[0] = 0.0f;
    for (int i = 1; i < relativeEnterRowZoomOffsetsSize; i++) {
        enterTemporalOffsets[1] = enterDuration;
    }

    rowsOnScreen = abs(*parent.glGrid[3] - *parent.glGrid[2]) / tileAndMarginCache;
    startTileIndex = (int) (((abs(*parent.glGrid[3] - *parent.glGrid[2]) - statusBarHeight - topMargin + scrollDist)) / tileAndMarginCache);
}

void initExitAnimation(int location[2]) {
    animProgress = exitDuration;
    entering = false;
    exiting = true;

    memcpy(exitTapTileLoc, location, 2);

    rowsOnScreen = abs(*parent.glGrid[3] - *parent.glGrid[2]) / tileAndMarginCache;

    float x = (exitStartPos + (float) location[1] + appTileOffset) - rowsOnScreen;
    if (x > 0) {
        rowsOnScreen += 2.0f * x;
    }

    exitAnimTime = (exitDuration / 2) / rowsOnScreen;
    exitStartPos = scrollDist / tileAndMarginCache;
}

void performNewEnterAnimation(double progress) {
    float zoomCache[relativeEnterRowZoomOffsetsSize];
    float alphaCache [relativeEnterRowZoomOffsetsSize];

    for (int i = 0; i < relativeEnterRowZoomOffsetsSize; i++) {
        if (progress <= enterDuration - enterTemporalOffsets[i])
            zoomCache[i] = 1.0f - ((float) fadeInInterpolator.getMulti(progress, enterDuration - enterTemporalOffsets[i]) * (1.0f - initalZoom));

        if (i + 1 < relativeEnterRowZoomOffsetsSize && enterTemporalOffsets[i + 1] == enterDuration &&
            zoomCache[i] >= initalZoom + relativeEnterRowZoomOffsets[i]/*(i.toFloat() + 1.0f) * enterRowZoomOffset*/) {
            enterTemporalOffsets[i + 1] = enterDuration - progress;
        }

        alphaCache[i] = (zoomCache[i] - (1.0f - fadeInStart)) / ((1.0f - fadeInEnd) - (1.0f - fadeInStart));
        if (zoomCache[i] > 1.0f - fadeInEnd) {
            alphaCache[i] = 1.0f;
        } else if (zoomCache[i] < 1.0f - fadeInStart) {
            alphaCache[i] = 0.0f;
        }
    }

    for (int i = 0; i < tiles.size(); i++) {
        int tileOffset = (startTileIndex) - (tiles[i].posY + tiles[i].spanY);
        if (tileOffset < 0)
            tileOffset = 0;
        else if (tileOffset >= relativeEnterRowZoomOffsetsSize)
            tileOffset = relativeEnterRowZoomOffsetsSize - 1;

        float color[] = { 0.24313f, 0.396078f, 1.0f, alphaCache[tileOffset] };

        calculateTile(i, zoomCache[tileOffset], color);
    }
}

void performExitAnimation(double progress) {
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].posY >= exitStartPos) {
            double tileTime = 2.0 * (exitDuration - progress - (tiles[i].posY - exitStartPos) * exitAnimTime);

            if (tiles[i].posX == exitTapTileLoc[0] && tiles[i].posY == exitTapTileLoc[1]) {
                tileTime -= appTileOffset * exitAnimTime;
            }

            float newZoom = 1.0f;
            if (tileTime > 0.0)
                newZoom = 1.0f + (float) fadeOutInterpolator.getMulti(tileTime, exitDuration) * (targetZoom - 1.0f);

            float alpha = 1.0f - (newZoom - (1.0f + fadeOutStart)) / ((fadeOutEnd + 1.0f) - (fadeOutStart + 1.0f));
            if (newZoom > 1.0f + fadeOutEnd) {
                alpha = 0.0f;
            } else if (newZoom < 1 + fadeOutStart) {
                alpha = 1.0f;
            }

            float color[] = {0.24313f, 0.396078f, 1.0f, alpha};

            calculateTile(i, newZoom, color);
        }
    }
}

bool tileTouched(int tile) {
    float t[] = {
            tileXPosChache[tiles[tile].posX],
            *parent.glGrid[2] + topMargin + (float) tiles[tile].posY * tileAndMarginCache + scrollDist +
            statusBarHeight,
            tileSizeCache + (float) (tiles[tile].spanX - 1) * tileAndMarginCache,
            tileSizeCache + (float) (tiles[tile].spanY - 1) * tileAndMarginCache
    };

    return  *parent.xTouchPos > t[0] &&
            *parent.xTouchPos < t[0] + t[2] &&
           -*parent.yTouchPos > t[1] &&
           -*parent.yTouchPos < t[1] + t[3];
}

void onTapEvent(bool longTap) {
    for (int i = 0; i < tiles.size(); i++) {
        if (tileTouched(i)) {
            if (longTap) {
                editMode = true;
                editModeSelectedTile = i;
            } else {
                if (editMode)
                    editModeSelectedTile = i;
                else {
                    int exitAnimParams[] = {tiles[i].posX, tiles[i].posY};

                    initExitAnimation(exitAnimParams);
                }
            }

            break;
        }
    }
}

void scroll(double elapsed, float divideBy) {
    if (*parent.fingerDown) {
        scrollDist -= *parent.dyTouch / divideBy;
    } else {
        scrollDist -= (*parent.yVelocityTouch / divideBy) * (float) elapsed;
    }
}

void overscrollEffect(bool top, double elapsed) {
    if (top)
        scrollDist = todoOverscrollDist * (float) overscrollInterpolator.getMulti(overscrollElapsed, overscrollDuration);
    else
        scrollDist = gridOverscrollHeight + (todoOverscrollDist * (float) overscrollInterpolator.getMulti(overscrollElapsed, overscrollDuration));

    if (overscrollElapsed <= 0) {
        todoOverscrollDist = 0.0f;
        if (top)
            scrollDist = 0.0f;
        else
            scrollDist = gridOverscrollHeight;
        *parent.yVelocityTouch = 0.0f;
    } else {
        overscrollElapsed -= elapsed;
    }
}

void handleTouch(double elapsed) {
    if (abs(*parent.xTouchPos - tapPosition[0]) <= tapTolerance && abs(*parent.yTouchPos - tapPosition[1]) <= tapTolerance) {
        if (parent.fingerDown) {
            tapInitiated = true;
            if (timeSinceTap > longTapDuraion)
                onTapEvent(true);
        } else if (tapInitiated) {
            onTapEvent(false);
            tapInitiated = false;
        }
    } else {
        tapInitiated = false;
        tapPosition[0] = *parent.xTouchPos;
        tapPosition[1] = *parent.yTouchPos;
    }

    if ((scrollDist >= overscrollDist) || (scrollDist <= gridOverscrollHeight - overscrollDist)) {
        *parent.yVelocityTouch = 0.0f;
        *parent.dyTouch = 0.0f;
    } else if (scrollDist > 0) {
        scroll(elapsed, 6.0f);
        if (parent.fingerDown) {
            todoOverscrollDist = scrollDist;
            overscrollElapsed = overscrollDuration;
        }
    } else if (scrollDist < gridOverscrollHeight) {
        scroll(elapsed, 6.0f);
        if (parent.fingerDown) {
            todoOverscrollDist = scrollDist - gridOverscrollHeight;
            overscrollElapsed = overscrollDuration;
        }
    } else {
        scroll(elapsed, 1.0f);
    }

    if (!parent.fingerDown) {
        if (scrollDist > 0.0f && *parent.yVelocityTouch > -1.0) {
            overscrollEffect(true, elapsed);
        } else if (scrollDist < gridOverscrollHeight && *parent.yVelocityTouch < 1.0) {
            overscrollEffect(false, elapsed);
        } else {
            if (scrollDist > 0 || scrollDist < gridOverscrollHeight)
                *parent.yVelocityTouch -= (float) elapsed * (*parent.yVelocityTouch / 0.04f);
            else
                *parent.yVelocityTouch -= (float) elapsed * (*parent.yVelocityTouch / 0.4f);

            if (scrollDist > gridOverscrollHeight / 2)
                todoOverscrollDist = scrollDist;
            else
                todoOverscrollDist = scrollDist - gridOverscrollHeight;
            overscrollElapsed = overscrollDuration;
        }
    }
}

void cacheTileValues() {
    tileSizeCache = ((*parent.glGrid[1] - *parent.glGrid[0]) - leftSideMargin - rightSideMargin - (gridWidth - 1) * tilesMargin) / gridWidth;

    tileAndMarginCache = tileSizeCache + tilesMargin;

    float xPos = *parent.glGrid[0] + rightSideMargin;
    for (int i = 0; i < gridWidth; i++) {
        tileXPosChache[i] = xPos;
        xPos += tileAndMarginCache;
    }

    statusBarHeight = (*parent.glGrid[3] - *parent.glGrid[2]) * statusBarHeightPercentage;

    overscrollDist = 0.2090278f * 2 - topMargin - statusBarHeight;

    navBarHeight = (*parent.glGrid[3] - *parent.glGrid[2]) * navBarHeightPercentage;

    gridHeight = (float) gridHeightSpan * tileAndMarginCache;
    gridOverscrollHeight = (gridHeight - (*parent.glGrid[3] - *parent.glGrid[2] - statusBarHeight - navBarHeight)) * -1.0f;
}

void update(double elapsed) {
    handleTouch(elapsed);

    if (animProgress <= 0.0) {
        if (exiting) {
            initEnterAnimation();
            performNewEnterAnimation(animProgress);
        } else {
            for (int i = 0; i < tiles.size(); i++) {
                //TODO: calc in seperate Thread
                float color[] = {0.24313f, 0.396078f, 1.0f, 1.0f};
                calculateTile(i, 1.0f, color);
            }
        }
    } else {
        if (entering) {
            performNewEnterAnimation(animProgress);
        } else if (exiting) {
            performExitAnimation(animProgress);
        }

        animProgress -= elapsed;
    }

    if (tapInitiated) {
        timeSinceTap += elapsed;
    } else {
        timeSinceTap = 0.0;
    }

    //TODO: multithreading, check for GPU finished

    for (int i = 0; i < tiles.size(); i++) {
        //Swap buffers in tiles
        memcpy(tiles[i].renderDrawListBuffer, tiles[i].drawListBuffer, tiles[i].drawListBufferSize);
        memcpy(tiles[i].renderVertBuffer, tiles[i].vertBuffer, tiles[i].vertBufferSize);
        memcpy(tiles[i].renderColorBuffer, tiles[i].colorBuffer, tiles[i].colorBufferSize);
    }
}