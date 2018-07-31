//
// Created by wulkanat on 01/08/2018.
//

#include <math.h>
#include <vector>

#ifndef NATIVEWINDOWSLAUNCHER_WINDOWSLAUNCHER_H
#define NATIVEWINDOWSLAUNCHER_WINDOWSLAUNCHER_H

#endif //NATIVEWINDOWSLAUNCHER_WINDOWSLAUNCHER_H

const float enterDuration = 0.62; //0.6
//val enterRowZoomDifference = 2.0f
//val enterRowZoomOffset = 0.01
const int relativeEnterRowZoomOffsetsSize = 7;
const float relativeEnterRowZoomOffsets[relativeEnterRowZoomOffsetsSize] = {0.01f, //0.01
                                               0.03f, 0.01f, //0.03, 0.01
                                               0.03f, 0.01f, //0.03, 0.01
                                               0.03f, 0.01f}; //0.03, 0.01

//0.021f, 0.01f)
const float initalZoom = 0.815f; //0.185, Measured
const float fadeInEnd = 0.05f;
const float fadeInStart = 0.185f; //0.185, Measured

const double fadeInNum1 = 0.0;
const double fadeInNum2 = 0.4; //0.3
const double fadeInNum3 = 7.2; //7.2
const double fadeInLoc[] = { 0.68, 0.1 }; //0.68, 0.1


const double overscrollNum1 = 0.0;
const double overscrollNum2 = 1.0;
const double overscrollNum3 = 0.0;
const double overscrollLoc[] = { 0.71, 0.25 };

const double exitDuration = 0.36;
const float targetZoom = 1.5f;
const float fadeOutEnd = 0.5f;
const float fadeOutStart = 0.15f;

const float appTileOffset = 2.0f;

const double fadeOutNum1 = 0.0;
const double fadeOutNum2 = 1.1;
const double fadeOutNum3 = 1.5;
const double fadeOutLoc[] = { 0.43, 0.29 };

const int indsSize = 6;
const short inds[indsSize] = { 0, 1, 2, 0, 2, 3 };

const double longTapDuraion = 0.75;

const float editModeZoom = -0.1f;
const float editModeSelectedZoom = -0.05f;
const float editModeAlpha = 0.8f;
const float editModeSelectedAlpha = 1.0f;

//TODO: Implement interpolator
/*var fadeInInterpolator = AccExpInterpolator(fadeInNum1, fadeInNum2, fadeInNum3, fadeInLoc)
var fadeOutInterpolator = AccExpInterpolator(fadeOutNum1, fadeOutNum2, fadeOutNum3, fadeOutLoc)
var overscrollInterpolator = AccExpInterpolator(overscrollNum1, overscrollNum2, overscrollNum3, overscrollLoc)*/

struct Tile {

};

std::vector<Tile> tiles;

const int gridWidth = 6;
const float leftSideMargin = 0.0104167f * 2.0f; //0.01041 6 Period  Measured
const float rightSideMargin = 0.0118056f * 2.0f;//0.01180 5 Period  Measured
const float tilesMargin = 0.0097222f * 2.0f;    //0.0097  2 Period  Measured
const float topMargin = tilesMargin;
float statusBarHeightPercentage = 0.0f;
//float statusBarHeight = 0.0f;
//TODO: setter or equivalent for statusBarHeight
/*set (value) {
        field = value
        overscrollDist = 0.2090278f * 2 - topMargin - value
}*/
float navBarHeightPercentage = 0.0f;
float navBarHeight = 0.0f;
float overscrollDist = 0.2090278f * 2.0f - topMargin; //0,20902 / Period
const double overscrollDuration = 0.5;
float todoOverscrollDist = 0.0f;
double overscrollElapsed = 0.0;

float gridOverscrollHeight = 0.0f;
//float gridHeight = 0.0f;
//TODO: setter or equivalent for gridHeight
/*set (value) {
        field = value
        gridOverscrollHeight = (value - (glGrid[3] - glGrid[2] - statusBarHeight - navBarHeight)) * -1
}*/
int gridHeightSpan = 0;

float scrollDist = 0.0f;

float tileSizeCache = 0.0f;
float tileXPosChache[gridWidth];
float tileAndMarginCache = 0.0f;

float glGrid[4];

int startTileIndex = 0;
float rowsOnScreen = 0.0f;
double animProgress = 0.0;
double enterTemporalOffsets[relativeEnterRowZoomOffsetsSize];

bool exiting = false;
bool entering = false;

float tapTolerance = 0.0005f;
float tapPosition[2];
bool tapInitiated = false;
double timeSinceTap = 0.0;

float exitStartPos = 0.0f;
double exitAnimTime = 0.0;
int exitTapTileLoc[2];

bool appDrawer = false;
bool editMode = false;
int editModeSelectedTile = 0;