//
// Created by wulkanat on 01/08/2018.
//

#include <math.h>
#include "AccExpInterpolator.h"

AccExpInterpolator::AccExpInterpolator(double a, double b, double c, double pos[]) {
    prec_a = ((a + b) / pow(pos[0], 2.0) - (2.0 * pos[1]) / pow(pos[0], 3.0));
    prec_b = ((-2.0 * a) - b) / pos[0] + ((3.0 * pos[1]) / pow(pos[0], 2.0));

    prec_c = ((c + b) / pow((1.0 - pos[0]), 2.0) - (2.0 * (1.0 - pos[1])) / pow((1.0 - pos[0]), 3.0));
    prec_d = ((-2.0 * c) - b) / (1.0 - pos[0]) + ((3.0 * (1.0 - pos[1])) / pow((1.0 - pos[0]), 2.0));

    this_pos[0] = pos[0];
    this_pos[1] = pos[1];

    this_a = a;
    this_c = c;
}

double AccExpInterpolator::getMulti(double value, double maxValue) {
    double myValue = value / maxValue;

    if (myValue < this_pos[0]) {
        return prec_a * pow(myValue, 3.0) + prec_b * pow(myValue, 2.0) + this_a * myValue;
    } else {
        return (prec_c * pow(1.0 - myValue, 3.0) + prec_d * pow(1.0 - myValue, 2.0) + this_c * (1.0 - myValue)) * -1.0 + 1.0;
    }
}