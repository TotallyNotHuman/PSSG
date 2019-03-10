#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "star.h"
#include "version.h"
#include "util.c"

int main(void) {
    // seed PRNG
    srand(time(NULL));
    // instantiate buffers for fgets()
    char r[100];
    char s[100];
    // parameters
    unsigned short* param = malloc(2 * sizeof(unsigned short));
    // initiate FSM state
    unsigned char state = 0;
    /*
     * States:
     * 0 = radius of sector
     * 1 = number of stars
     * 2 = generation
     * 3 = display
     * 4 = cleanup
     */
    printf("Procedural Star System Generator, version %s\n", VERSION);
    for (;;) {
        switch (state) {
            case 0:
                printf("Input radius of sector [1-255 ly]: ");
                fgets(r, 100, stdin);
                unsigned long rad = strtoul(r, NULL, 10);
                if (rad <= 0 || rad > UCHAR_MAX) {
                    printf("Invalid input.\n");
                    memset(r, 0, sizeof(r));
                    break;
                }
                param[0] = (unsigned short) rad;
                state = 1;
                break;
            case 1:
                printf("Input number of stars in sector [1-65535]: ");
                fgets(s, 100, stdin);
                printf("\n");
                unsigned long num = strtoul(s, NULL, 10);
                if (num <= 0 || num > USHRT_MAX) {
                    printf("Invalid input.\n");
                    memset(s, 0, sizeof(s));
                    break;
                }
                param[1] = (unsigned short) num;
                state = 2;
                break;
            case 2:
                printf("Generating %hu stars in a spherical sector with %hu ly radius.\n", param[1], param[0]);
                star_t** stars = malloc(param[1] * sizeof(star_t*));
                for (unsigned short i = 0; i < param[1]; i++) {
                    stars[i] = malloc(sizeof(star_t));
                }
                unsigned short j = 0;
                while (j < param[1]) {
                    // generate coordinates and store them as cartesian
                    double* sphrgen = malloc(3 * sizeof(double));
                    sphrgen[0] = randbl(0.01, param[0]);
                    sphrgen[1] = randbl(0.0, PI);
                    sphrgen[2] = randbl(0.0, 2.0 * PI);
                    double* cartgen = sphr2cart(sphrgen);
                    stars[j]->coords[0] = cartgen[0];
                    stars[j]->coords[1] = cartgen[1];
                    stars[j]->coords[2] = cartgen[2];
                    free(cartgen);
                    free(sphrgen);
                    // generate selection factor
                    double sfac = randbl(0.0, 1.0);
                    // generate mass from selfac
                    stars[j]->mass = sfac2mass(sfac);
                    // generate lum from mass
                    stars[j]->luminosity = mass2lum(stars[j]->mass);
                    // increment counter
                    j++;
                }
                state = 3;
                break;
            case 3:
                // debug output
                for (unsigned short i = 0; i < param[1]; i++) {
                    printf("coords = (%.3f, %.3f, %.3f), mass = %.3f, luminosity = %.3f\n",
                    stars[i]->coords[0], stars[i]->coords[1], stars[i]->coords[2],
                    stars[i]->mass, stars[i]->luminosity);
                }
                state = 4;
                break;
            case 4:
                for (unsigned short i = 0; i < param[1]; i++) {
                    free(stars[i]);
                }
                free(stars);
                free(param);
                exit(0);
        }
    }
}