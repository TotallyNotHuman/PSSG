#ifndef STAR_H
#define STAR_H

typedef struct star {
    /*double mass; // mass of star in M_sol
    double radius; // radius of star in R_sol
    double luminosity; // luminosity of star in L_sol
    unsigned short temp; // temperature of star in K*/ // TODO: do research on star statistic ranges
    char spectype; // spectral class of star
    unsigned short subdiv; // digit subdivision of star
    char* lumtype; // luminosity class of star
    double coords[3]; // coordinates of star wrt center
} star_t;

char* star_tostring(star_t* star);

#endif//STAR_H