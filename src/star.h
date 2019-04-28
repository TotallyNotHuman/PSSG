#ifndef STAR_H
#define STAR_H

// type definition
typedef struct star {
    double mass; // mass of star in M_sol
    double radius; // radius of star in R_sol
    double luminosity; // luminosity of star in L_sol
    unsigned short temp; // temperature of star in K
    char* specclass; // spectral class of star
    double coords[3]; // coordinates of star wrt center
} star_t;

// star "visual"izer function
char* star_tostring(star_t* star);

#endif//STAR_H