//
// Created by wulkanat on 01/08/2018.
//

#pragma once

#ifndef NATIVEWINDOWSLAUNCHER_ACCEXPINTERPOLATOR_H
#define NATIVEWINDOWSLAUNCHER_ACCEXPINTERPOLATOR_H

#endif //NATIVEWINDOWSLAUNCHER_ACCEXPINTERPOLATOR_H

class AccExpInterpolator {
public:
    AccExpInterpolator(double a, double b, double c, double pos[]);
    double getMulti(double value, double maxValue);

private:
    double this_pos[2];

    double this_a;
    double this_c;

    double prec_a;
    double prec_b;

    double prec_c;
    double prec_d;
};