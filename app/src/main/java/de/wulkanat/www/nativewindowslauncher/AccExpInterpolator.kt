package de.wulkanat.www.nativewindowslauncher

import java.lang.Math.pow

class AccExpInterpolator(private val a: Double, private val b: Double, private val c: Double, private val pos: DoubleArray) {
    private val prec_a = ((a + b) / pow(pos[0], 2.0) - (2.0 * pos[1]) / pow(pos[0], 3.0))
    private val prec_b = ((-2.0 * a) - b) / pos[0] + ((3.0 * pos[1]) / pow(pos[0], 2.0))

    private val prec_c = ((c + b) / pow((1.0 - pos[0]), 2.0) - (2.0 * (1.0 - pos[1])) / pow((1.0 - pos[0]), 3.0))
    private val prec_d = ((-2.0 * c) - b) / (1.0 - pos[0]) + ((3.0 * (1.0 - pos[1])) / pow((1.0 - pos[0]), 2.0))

    fun getMulti(value: Double, maxValue: Double): Double {
        val myValue = value / maxValue

        if (myValue < pos[0]) {
            return prec_a * pow(myValue, 3.0) + prec_b * pow(myValue, 2.0) + a * myValue
        } else {
            return (prec_c * pow(1.0 - myValue, 3.0) + prec_d * pow(1.0 - myValue, 2.0) + c * (1 - myValue)) * -1 + 1
        }
    }
}