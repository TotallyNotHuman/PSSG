#include <math.h>
#include <stdlib.h>
#include "constants.h"
#define PI 3.14159265358979323846 // pi macro since math.h doesn't include it

/* miscellaneous functions */

// spherical to 3-dimensional Cartesian coordinates
double* sphr2cart(double* sphr) {
    // assuming [rho, theta, phi]
    double* cart = malloc(3 * sizeof(double));
    cart[0] = sphr[0] * sin(sphr[1]) * cos(sphr[2]);
    cart[1] = sphr[0] * sin(sphr[1]) * sin(sphr[2]);
    cart[2] = sphr[0] * cos(sphr[1]);
    return cart;
}

// random double between min and max
double randbl(double min, double max) {
    // assume the RNG is already seeded
    double range = (max - min);
    double rng = RAND_MAX / range;
    return min + (rand() / rng);
}

/* generic stellar computation functions */

// generate temperature from B-V
unsigned short bv2temp(double bv) {
    return (unsigned short)(4600.0 * ((1 / ((0.92 * bv) + 1.7)) + (1 / ((0.92 * bv) + 0.62))));
}

// generate mass from luminosity
double lum2mass(double lum) {
    if (lum < la1) {
        return lb1 * pow(lum, lc1);
    } else if ((lum > la1) && (lum < la2)) {
        return lb2 * pow(lum, lc2);
    } else if ((lum > la2) && (lum < la3)) {
        return lb3 * pow(lum, lc3);
    } else if ((lum > la3) && (lum < la4)) {
        return lb4 * pow(lum, lc4);
    } else if (lum > la4) {
        return lum * la5;
    }
    return 0.0;
}

/* mainseq-specific functions */

// generate radius from B-V
double ms_bv2rad(double bv) {
    return pow(10, (ba1 + (bb1 * log(bc1 / (bv + bd1)))));
}

// generate luminosity from B-V
double ms_bv2lum(double bv) {
    return pow(10, (ba2 + (bb2 * log(bc1 / (bv + bd1)))));
}

/* giant-specific functions */

// generate radius from B-V
double gs_bv2rad(double bv) {
    return pow(10, (ba3 + (bb3 * log(bc2 / (bv + bd2)))));
}

// generate luminosity from B-V
double gs_bv2lum(double bv) {
    return pow(10, (ba4 + (bb4 * log(bc2 / (bv + bd2)))));
}

/* supergiant-specific functions */

// generate radius from B-V
double sg_bv2rad(double bv) {
    return (bv < 0.76) ? pow(10, (ba5 + (bb5 * log(bc3 / (bv + bd3))))) : pow(10, (ba6 + (bb6 * log(bc3 / (bv + bd3)))));
}

// generate luminosity from B-V
double sg_bv2lum(double bv) {
    return (bv < 0.76) ? pow(10, (ba7 + (bb7 * log(bc3 / (bv + bd3))))) : pow(10, (ba8 + (bb8 * log(bc3 / (bv + bd3)))));
}