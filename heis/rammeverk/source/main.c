#include "elev.h"
#include "floor.h"
#include "FSM.h"
#include "door.h"
#include <stdio.h>
#include <time.h>

/**
* @file
* @brief The main file, it does what
* main files usually does
*/
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    init_FSM();
    FSM();
    return 0;
}
