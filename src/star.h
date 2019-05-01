#ifndef STAR_H
#define STAR_H

// type definition
typedef struct star {
    double mass; // mass of star in M_sol
    double radius; // radius of star in R_sol
    double luminosity; // luminosity of star in L_sol
    unsigned short temp; // temperature of star in K
    char* specclass; // spectral class of star
    char* lumclass; // luminosity class of star
    double coords[3]; // coordinates of star wrt center
    double age; // age of the star in Gyr
    double lifespan; // calculated main sequence lifespan of the star in Gyr
    unsigned char flags; // flags added during aging pass
} star_t;
/* aging pass flags:
 * 0x0: remains in main sequence
 * 0x1: becomes giant
 * 0x2: becomes super/hypergiant
 */

// star "visual"izer function
char* star_tostring(star_t* star);

#endif//STAR_H