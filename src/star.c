#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "star.h"

// star "visual"izer function
char* star_tostring(star_t* star) {
    char* starstr = malloc(200);
    char *specstr, *lumstr;
    // generate spectral name
    switch (star->specclass[0]) {
        case 'O':
            specstr = "Blue";
            break;
        case 'B':
            specstr = "Blue-white";
            break;
        case 'A':
            specstr = "White";
            break;
        case 'F':
            specstr = "Yellow-white";
            break;
        case 'G':
            specstr = "Yellow";
            break;
        case 'K':
            specstr = "Orange";
            break;
        case 'M':
            specstr = "Red";
            break;
    }
    // generate main-sequence/dwarf nomenclature
    if (star->specclass[0] == 'M') {
        lumstr = " Dwarf";
    } else {
        lumstr = " Main Sequence";
    }

    // generate lumstr for (super/hyper)giants
    if (strcmp(star->lumclass, "III") == 0) {
        lumstr = " Giant";
    } else if (strcmp(star->lumclass, "Ib") == 0) {
        lumstr = " Supergiant";
    } else if (strcmp(star->lumclass, "Iab") == 0) {
        lumstr = " Supergiant";
    } else if (strcmp(star->lumclass, "Ia") == 0) {
        lumstr = " Supergiant";
    } else if (strcmp(star->lumclass, "Ia+") == 0) {
        lumstr = " Hypergiant";
    }
    sprintf(starstr, "Star class: %s %s %s%s\nCoordinates: (%.2f, %.2f, %.2f)\nMass: %.3g M☉\nRadius: %.3g R☉\nLuminosity: %.3g L☉\nTemperature: %d K\nAge: %.3g Gyr\n", star->specclass, star->lumclass, specstr, lumstr, star->coords[0], star->coords[1], star->coords[2], star->mass, star->radius, star->luminosity, star->temp, star->age);
    return starstr;
}