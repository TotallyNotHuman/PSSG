#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_sf_lambert.h>
#include "constants.h"
#define PI 3.14159265358979323846 // pi macro since math.h doesn't include it

/* miscellaneous functions */

// random double between min and max, assuming the RNG is already seeded
double randbl(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

/* quaternion maths functions */

// multiply quaternions
double* quat_mult(double* p, double* q) {
    double* r = malloc(4 * sizeof(double));
    r[0] = ((p[0] * q[0]) - (p[1] * q[1]) - (p[2] * q[2]) - (p[3] * q[3]));
    r[1] = ((p[0] * q[1]) + (p[1] * q[0]) - (p[2] * q[3]) + (p[3] * q[2]));
    r[2] = ((p[0] * q[2]) + (p[1] * q[3]) + (p[2] * q[0]) - (p[3] * q[1]));
    r[3] = ((p[0] * q[3]) - (p[1] * q[2]) + (p[2] * q[1]) + (p[3] * q[0]));
    return r;
}


// normalize quaternion
void quat_norm(double* q) {
    double mag = sqrt(pow(q[0], 2) + pow(q[1], 2) + pow(q[2], 2) + pow(q[3], 2));
    q[0] /= mag;
    q[1] /= mag;
    q[2] /= mag;
    q[3] /= mag;
}

// quaternion to 3-Cartesian coordinates
double* quat2cart(double* quat) {
    quat_norm(quat);
    double qconj[4] = {quat[0], (-1 * quat[1]), (-1 * quat[2]), (-1 * quat[3])};
    double uvect[4] = {0, 1, 0, 0};
    double* r1 = quat_mult(quat, uvect);
    double* r2 = quat_mult(r1, qconj);
    double* cart = malloc(3 * sizeof(double));
    cart[0] = r2[1];
    cart[1] = r2[2];
    cart[2] = r2[3];
    free(r1);
    free(r2);
    return cart;
}

/* stellar computation functions */

// compute mass from selection factor
double sfac2mass(double s) {
    return (s > t) ? a2 / pow((b2 - s), (10.0 / 13.0)) : ((a * s) + b) / gsl_sf_lambert_Wm1((c * s) + d);
}

// compute luminosity from mass
double mass2lum(double m) {
    if (m > 55.0) {
        return 32000.0 * m;
    } else if ((m < 55.0) && (m > 20.0)) {
        return pow(m, 3.5);
    } else if ((m < 20.0) && (m > 2.0)) {
        return 1.4 * pow(m, 3.5);
    } else if ((m < 2.0) && (m > 0.43)) {
        return pow(m, 4);
    } else if (m < 0.43) {
        return 0.23 * pow(m, 2.3);
    }
    return 0.0;
}
