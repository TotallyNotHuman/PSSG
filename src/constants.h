#ifndef PSSG_CONST
#define PSSG_CONST

/* This is the PSSG constants file.
 * These constants determine the bounds and composition of generated star masses.
 * Changing those values improperly may cause unexpected or undefined behavior.
 */

// transition point
static const double t = 0.718163;

// first piece (ax+b)/W_-1(cx+d), 0 <= x <= t
static const double a = -7.47084;
static const double b = -0.686173;
static const double c = -0.0175896;
static const double d = -0.00161555;

// second piece a2/(b2-s)^(10/13), t <= x <= 1
static const double a2 = 0.378422;
static const double b2 = 1.00089;

#endif