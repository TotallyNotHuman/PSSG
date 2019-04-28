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
                for (unsigned short j = 0; j < param[1]; j++) {
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
                    // generate weighted B-V
                    double bvfac = randbl(0.0, 100.0);
                    double bv = 0.0;
                    if (bvfac <= 0.01) {
                        bv = randbl(-0.33, -0.3);
                    } else if ((bvfac >= 0.01) && (bvfac <= 0.13)) {
                        bv = randbl(-0.3, -0.02);
                    } else if ((bvfac >= 0.13) && (bvfac <= 0.73)) {
                        bv = randbl(-0.02, 0.3);
                    } else if ((bvfac >= 0.73) && (bvfac <= 3.73)) {
                        bv = randbl(0.3, 0.58);
                    } else if ((bvfac >= 3.73) && (bvfac <= 11.33)) {
                        bv = randbl(0.58, 0.81);
                    } else if ((bvfac >= 11.33) && (bvfac <= 23.43)) {
                        bv = randbl(0.81, 1.40);
                    } else if ((bvfac >= 23.43) && (bvfac <= 100.0)) {
                        bv = randbl(1.40, 3.17);
                    }
                    // generate parameters from B-V
                    stars[j]->temp = bv2temp(bv);
                    stars[j]->radius = bv2rad(bv);
                    stars[j]->luminosity = bv2lum(bv);
                    stars[j]->mass = lum2mass(stars[j]->luminosity);
                    // generate spectral class
                    char* specclass = malloc(4 * sizeof(char));
                    unsigned short temp = stars[j]->temp;
                    unsigned short subdiv = 0;
                    if ((temp >= 2300) && (temp <= 3700)) { // M-class stars
                        subdiv = 10 - (unsigned short) ceil(((double) (temp - 2300)) / 140.0);
                        sprintf(specclass, "M%d V", subdiv);
                    } else if ((temp >= 3700) && (temp <= 5200)) { // K-class stars
                        subdiv = 10 - (unsigned short) ceil(((double) (temp - 3700)) / 150.0);
                        sprintf(specclass, "K%d V", subdiv);
                    } else if ((temp >= 5200) && (temp <= 6000)) { // G-class stars
                        subdiv = 10 - (unsigned short) ceil(((double) (temp - 5200)) / 80.0);
                        sprintf(specclass, "G%d V", subdiv);
                    } else if ((temp >= 6000) && (temp <= 7500)) { // F-class stars
                        subdiv = 10 - (unsigned short) ceil(((double) (temp - 6000)) / 150.0);
                        sprintf(specclass, "F%d V", subdiv);
                    } else if ((temp >= 7500) && (temp <= 10000)) { // A-class stars
                        subdiv = 10 - (unsigned short) ceil(((double) (temp - 7500)) / 250.0);
                        sprintf(specclass, "A%d V", subdiv);
                    } else if ((temp >= 10000) && (temp <= 30000)) { // B-class stars
                        subdiv = 10 - (unsigned short) ceil(((double) (temp - 10000)) / 2000.0);
                        sprintf(specclass, "B%d V", subdiv);
                    } else if ((temp >= 30000) && (temp <= 55000)) { // O-class stars
                        subdiv = 10 - (unsigned short) ceil(((double) (temp - 30000)) / 2500.0);
                        sprintf(specclass, "O%d V", subdiv);
                    }
                    stars[j]->specclass = specclass;
                }
                state = 3;
                break;
            case 3:
                // debug output
                for (unsigned short i = 0; i < param[1]; i++) {
                    printf("coords = (%.3f, %.3f, %.3f), temp = %d K, rad = %f R_sol, lum = %f L_sol, mass = %f M_sol\n",
                    stars[i]->coords[0], stars[i]->coords[1], stars[i]->coords[2], stars[i]->temp, stars[i]->radius,
                    stars[i]->luminosity, stars[i]->mass);
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