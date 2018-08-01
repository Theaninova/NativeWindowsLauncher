//
// Created by wulkanat on 01/08/2018.
//

#pragma once

#include <math.h>
#include <vector>
#include "AccExpInterpolator.h"

#ifndef NATIVEWINDOWSLAUNCHER_WINDOWSLAUNCHER_H
#define NATIVEWINDOWSLAUNCHER_WINDOWSLAUNCHER_H

#endif //NATIVEWINDOWSLAUNCHER_WINDOWSLAUNCHER_H

struct Tile {
    int posX;
    int posY;
    int spanX;
    int spanY;

    const static size_t vertBufferSize = 3 * 4;
    const static size_t drawListBufferSize = 6;
    const static size_t colorBufferSize = 4;
    float vertBuffer[vertBufferSize];
    short drawListBuffer[drawListBufferSize];
    float colorBuffer[colorBufferSize];

    float renderVertBuffer[vertBufferSize];
    short renderDrawListBuffer[drawListBufferSize];
    float renderColorBuffer[colorBufferSize];

    float currentZoom = 0.0f;
};

//Shared Variables
struct SharedValues {
    float yVelocityTouch = 0.0f;
    float xVelocityTouch = 0.0f;
    float dyTouch = 0.0f;
    float dxTouch = 0.0f;
    float xTouchPos = 0.0f;
    float yTouchPos = 0.0f;
    bool fingerDown = false;
    bool fingerMoved = false;

    float glGrid[4] = { -1.0f, 1.0f, -1.0f, 1.0f};
    const static int indsSize = 6;
    short inds[indsSize] ={ 0, 1, 2, 0, 2, 3 };

    float statusBarHeightPercentage = 0.0f;
    float navBarHeightPercentage = 0.0f;

    bool editMode = false;

    std::vector<Tile> tiles;
};

//Constansts ONLY
const double enterDuration = 0.62; //0.6
const int relativeEnterRowZoomOffsetsSize = 7;
const float relativeEnterRowZoomOffsets[relativeEnterRowZoomOffsetsSize] = {0.015f, //0.01
                                               0.03f, 0.015f, //0.03, 0.01
                                               0.03f, 0.015f, //0.03, 0.01
                                               0.03f, 0.015f}; //0.03, 0.01

//0.021f, 0.01f)
const float initalZoom = 0.815f; //0.185, Measured
const float fadeInEnd = 0.00f;
const float fadeInStart = 0.185f; //0.185, Measured

const double fadeInNum1 = 0.0;
const double fadeInNum2 = 0.4; //0.3
const double fadeInNum3 = 7.2; //7.2
double fadeInLoc[] = { 0.68, 0.1 }; //0.68, 0.1

const double overscrollNum1 = 0.0;
const double overscrollNum2 = 1.0;
const double overscrollNum3 = 0.0;
double overscrollLoc[] = { 0.71, 0.25 };

const double drawerOpenDuration = 1.0;
const double drawerOpenNum1 = 0.0;
const double drawerOpenNum2 = 0.4; //0.3
const double drawerOpenNum3 = 7.2; //7.2
double drawerOpenLoc[] = { 0.68, 0.1 }; //0.68, 0.1

const double exitDuration = 0.36;
const float targetZoom = 1.5f;
const float fadeOutEnd = 0.5f;
const float fadeOutStart = 0.15f;

const float appTileOffset = 2.0f;

const double fadeOutNum1 = 0.0;
const double fadeOutNum2 = 1.1;
const double fadeOutNum3 = 1.5;
double fadeOutLoc[] = { 0.43, 0.29 };

const double longTapDuraion = 0.75;

const float editModeZoom = -0.1f;
const float editModeSelectedZoom = -0.05f;
const float editModeAlpha = 0.8f;
const float editModeSelectedAlpha = 1.0f;

const int gridWidth = 6;
const float leftSideMargin = 0.0104167f * 2.0f; //0.01041 6 Period  Measured
const float rightSideMargin = 0.0118056f * 2.0f;//0.01180 5 Period  Measured
const float tilesMargin = 0.0097222f * 2.0f;    //0.0097  2 Period  Measured
const float topMargin = tilesMargin;

const double overscrollDuration = 0.5;

//Fuctions for external use

void windows_launcher_init(SharedValues * mParent);
void update(double elapsed);
void cacheTileValues();