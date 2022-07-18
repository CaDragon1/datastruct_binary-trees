/*
 * If you modify this file, replace this comment with your own
 * Otherwise, leave this file and this comment as-is
 */

#include "functions.h"

// do not modify this function
int random_range(int min, int max) {
    //returns a random number between min and max inclusive
    return (std::rand() % (max - min + 1)) +min;
}

// you may add more functions here if you need them

