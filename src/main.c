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
     * 4 = cleanup
     */
    printf("Procedural Star Generator, version %s\n", VERSION);
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
                    sphrgen[1] = randbl(0, PI);
                    sphrgen[2] = randbl(0, 2 * PI);
                    double* cartgen = sphr2cart(sphrgen);
                    stars[j]->coords[0] = cartgen[0];
                    stars[j]->coords[1] = cartgen[1];
                    stars[j]->coords[2] = cartgen[2];
                    free(cartgen);
                    free(sphrgen);
                    // generate spectral type
                    unsigned long spectnum = (unsigned long) round(randbl(0.0, 1.0) * pow(10.0, 10.0)) - 1;
                    unsigned char ismains = 1;
                    char spect;
                    if ((spectnum >= 0) && (spectnum <= 866)) {
                        spect = 'W';
                        ismains = 0;
                    } else if ((spectnum >= 867) && (spectnum <= 131885)) {
                        spect = 'O';
                    } else if ((spectnum >= 131886) && (spectnum <= 6935751)) {
                        spect = 'N';
                        ismains = 0;
                    } else if ((spectnum >= 6935752) && (spectnum <= 19859904)) {
                        spect = 'B';
                    } else if ((spectnum >= 19859905) && (spectnum <= 35859904)) {
                        spect = 'D';
                        ismains = 0;
                    } else if ((spectnum >= 35859905) && (spectnum <= 95887923)) {
                        spect = 'A';
                    } else if ((spectnum >= 95887924) && (spectnum <= 395915942)) {
                        spect = 'F';
                    } else if ((spectnum >= 395915943) && (spectnum <= 1155943961)) {
                        spect = 'G';
                    } else if ((spectnum >= 1155943962) && (spectnum <= 2364831885)) {
                        spect = 'K';
                    } else if ((spectnum >= 2364831886) && (spectnum <= 9999999999)) {
                        spect = 'M';
                    }
                    stars[j]->spectype = spect;
                    // neutron/pulsar pass
                    if ((spect == 'N') && (rand() % 500 == 0)) {
                        stars[j]->spectype = 'P';
                    }
                    // generate subdivision
                    if (ismains) {
                        stars[j]->subdiv = rand() % 10;
                    }
                    // generate luminosity classes
                    if (ismains) {
                        unsigned short lunum = rand() % 10000;
                        if ((lunum >= 0) && (lunum <= 71)) {
                            stars[j]->lumtype = "Ia";
                        } else if ((lunum >= 72) && (lunum <= 220)) {
                            stars[j]->lumtype = "Ib";
                        } else if ((lunum >= 221) && (lunum <= 485)) {
                            stars[j]->lumtype = "II";
                        } else if ((lunum >= 486) && (lunum <= 1632)) {
                            stars[j]->lumtype = "III";
                        } else if ((lunum >= 1633) && (lunum <= 5579)) {
                            stars[j]->lumtype = "IV";
                        } else if ((lunum >= 5580) && (lunum <= 9999)) {
                            stars[j]->lumtype = "V";
                        }
                    }
                    // print status message
                    j++;
                }
                state = 3;
                break;
            case 3:
                for (unsigned short i = 0; i < param[1]; i++) {
                    char* starstr = star_tostring(stars[i]);
                    printf("%s\n", starstr);
                    free(starstr);
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