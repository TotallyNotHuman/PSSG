#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "star.h"

char* star_tostring(star_t* star) {
    char* starstr = malloc(100 * sizeof(char));
    unsigned char uselum = 1;
    char *specstr, *lumstr;
    switch (star->spectype) {
        case 'W':
            specstr = "Wolf-Rayet star";
            uselum = 0;
            break;
        case 'O':
            specstr = "blue";
            break;
        case 'N':
            specstr = "Neutron star";
            uselum = 0;
            break;
        case 'P':
            specstr = "Pulsar";
            uselum = 0;
            break;
        case 'B':
            specstr = "blue";
            break;
        case 'D':
            specstr = "White dwarf";
            uselum = 0;
            break;
        case 'A':
            specstr = "white";
            break;
        case 'F':
            specstr = "yellow";
            break;
        case 'G':
            specstr = "yellow";
            break;
        case 'K':
            specstr = "orange";
            break;
        case 'M':
            specstr = "red";
            break;
    }
    if (uselum) {
        if (strcmp(star->lumtype, "Ia") == 0) {
            lumstr = " supergiant";
        } else if (strcmp(star->lumtype, "Ib") == 0) {
            lumstr = " supergiant";
        } else if (strcmp(star->lumtype, "II") == 0) {
            lumstr = " giant";
        } else if (strcmp(star->lumtype, "III") == 0) {
            lumstr = " giant";
        } else if (strcmp(star->lumtype, "IV") == 0) {
            lumstr = " subgiant";
        } else if (strcmp(star->lumtype, "V") == 0) {
            if ((star->spectype == 'M') || (star->spectype == 'K') || (star->spectype == 'G')) {
                lumstr = " dwarf";
            } else {
                lumstr = " main-sequence";
            }
        }
    }
    if (uselum) {
        sprintf(starstr, "Star class: %c%d%s (%s%s)\nCoordinates: (%.2f, %.2f, %.2f)\n",
                    star->spectype, star->subdiv, star->lumtype, specstr, lumstr,
                    star->coords[0], star->coords[1], star->coords[2]);
    } else {
        sprintf(starstr, "Star class: %s)\nCoordinates: (%.2f, %.2f, %.2f)\n",
                    specstr, star->coords[0], star->coords[1], star->coords[2]);
    }
    return starstr;
}