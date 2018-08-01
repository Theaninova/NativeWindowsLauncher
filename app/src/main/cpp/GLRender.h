//
// Created by wulkanat on 31/07/2018.
//
#pragma once

#include <GLES2/gl2.h>
#include <chrono>
#include <jni.h>
#include "WindowsLauncher.h"

#ifndef NATIVEWINDOWSLAUNCHER_GLRENDER_H
#define NATIVEWINDOWSLAUNCHER_GLRENDER_H

#endif //NATIVEWINDOWSLAUNCHER_GLRENDER_H

float mtrxProjection[16];
float mtrxView[16];
float mtrxProjectionAndView[16];

int COORDS_PER_VERTEX = 3;
int vertexStride = COORDS_PER_VERTEX * 4;

float mScreenWidth = 1080.0f;
float mScreenHeight = 1920.0f;
float mAspectRatio = 16.0f / 9.0f;

int statusBarHeightPixels;
int navBarHeightPixels;

std::chrono::high_resolution_clock::time_point mLastTime;
int mProgram;

SharedValues sharedValues;

void on_surface_created();
void on_surface_changed(int width, int height);
void on_draw_frame();