#ifndef PSSG_CONST
#define PSSG_CONST

/* This is the PSSG constants file.
 * These constants determine star radii/luminosities.
 * Changing those values may cause unexpected or undefined behavior.
 */

/* bv2* constants */

// bv2rad constants
static const double ba1 = -5.793;
static const double bb1 = 0.6729;

// bv2lum constants
static const double ba2 = -26.63;
static const double bb2 = 3.083;

// common constants
static const double bc = 7360.9;
static const double bd = 0.6411;

/* lum2mass constants */

// branch 1: mass < 0.43
static const double la1 = 0.3302;
static const double lb1 = 1.8946;
static const double lc1 = 0.4347;

// branch 2: 0.43 < mass < 2
static const double la2 = 16.0;
static const double lb2 = 1.0;
static const double lc2 = 0.25;

// branch 3: 2 < mass < 20
static const double la3 = 50087.9;
static const double lb3 = 0.9038;
static const double lc3 = 0.2857;

// branch 4: 20 < mass < 55
static const double la4 = 1233870.0;
static const double lb4 = 1.0;
static const double lc4 = 0.2857;

// branch 5: mass > 55
static const double la5 = 32000.0;


#endif