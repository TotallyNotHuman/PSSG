#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "star.h"

// star "visual"izer function
char* star_tostring(star_t* star) {
    char* starstr = malloc(200 * sizeof(char));
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
    sprintf(starstr, "Star class: %s %s%s\nCoordinates: (%.2f, %.2f, %.2f)\nMass: %.2f M☉\nRadius: %.2f R☉\nLuminosity: %.2f L☉\nTemperature: %d K\n", star->specclass, specstr, lumstr, star->coords[0], star->coords[1], star->coords[2], star->mass, star->radius, star->luminosity, star->temp);
    return starstr;
}