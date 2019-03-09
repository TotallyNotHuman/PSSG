#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_sf_lambert.h>
#define PI 3.14159265358979323846 // pi macro since math.h doesn't include it

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

// compute mass from selection factor
double sfac2mass(double s) {
    if (s > 0.719) {
        // mass > 1 case
        return 0.378843 / pow((1.00234 - s), (10.0 / 13.0));
    } else {
        // mass < 1 case
        return ((-7.46001 * s) - 0.686172) / gsl_sf_lambert_Wm1((-0.0175644 * s) - 0.00161558);
    }
}

// compute luminosity from mass
double mass2lum(double m) {
    if (m > 55.0) {
        return 32000.0 * m;
    } else if ((m < 20.0) && (m > 2.0)) {
        return 1.4 * pow(m, 3.5);
    } else if ((m < 2.0) && (m > 0.43)) {
        return pow(m, 4);
    } else if (m < 0.43) {
        return 0.23 * pow(m, 2.3);
    }
    return 0.0;
}