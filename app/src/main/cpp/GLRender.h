//
// Created by wulkanat on 31/07/2018.
//
#pragma once

#include <GLES2/gl2.h>
#include <chrono>
#include "WindowsLauncher.h"

#ifndef NATIVEWINDOWSLAUNCHER_GLRENDER_H
#define NATIVEWINDOWSLAUNCHER_GLRENDER_H

#endif //NATIVEWINDOWSLAUNCHER_GLRENDER_H

float mtrxProjection[16];
float mtrxView[16];
float mtrxProjectionAndView[16];

float dxTouch = 0.0f;
float dyTouch = 0.0f;

float xTouchPos = 0.0f;
float yTouchPos = 0.0f;

//glGrid units per second per second
float xVelocityTouch = 0.0f;
float yVelocityTouch = 0.0f;
bool fingerDown = false;

float glGrid[] = { -1.0f, 1.0f, 1.0f, -1.0f };

int COORDS_PER_VERTEX = 3;
int vertexStride = COORDS_PER_VERTEX * 4;
const int indsSize = 6;
short inds[indsSize] ={ 0, 1, 2, 0, 2, 3 };

float mScreenWidth = 1080.0f;
float mScreenHeight = 1920.0f;
float mAspectRatio = 16.0f / 9.0f;

int statusBarHeightPixels;
int navBarHeightPixels;

std::chrono::high_resolution_clock::time_point mLastTime;
int mProgram;

void on_surface_created();
void on_surface_changed(int width, int height);
void on_draw_frame();