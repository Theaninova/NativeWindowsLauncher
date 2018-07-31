//
// Created by wulkanat on 01/08/2018.
//

#include <math.h>

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