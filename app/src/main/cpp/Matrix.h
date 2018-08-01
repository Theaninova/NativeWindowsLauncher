/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//JAVA CODE PORTED TO C++

#pragma once

#ifndef NATIVEWINDOWSLAUNCHER_MATRIX_H
#define NATIVEWINDOWSLAUNCHER_MATRIX_H

#endif //NATIVEWINDOWSLAUNCHER_MATRIX_H

void orthoM(float * m, int mOffset,
            float left, float right, float bottom, float top,
            float near, float far);
void setLookAtM(float * rm, int rmOffset,
                float eyeX, float eyeY, float eyeZ,
                float centerX, float centerY, float centerZ, float upX, float upY,
                float upZ);
void translateM(
        float * m, int mOffset,
        float x, float y, float z);
float length(float x, float y, float z);
void multiplyMM(float* r, const float* lhs, const float* rhs);