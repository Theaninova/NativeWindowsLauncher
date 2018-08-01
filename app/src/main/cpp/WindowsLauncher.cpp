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
void init(Parent mParent) {
    parent = mParent;
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