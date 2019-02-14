#include <math.h>
#include <stdlib.h>
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