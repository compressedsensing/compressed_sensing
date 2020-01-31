
#include "contiki.h"
#include "./randomGenerator.h"
#include "./linalg.h"

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{
    /* Declare variables required */
    PROCESS_BEGIN();

    float hep = RANDOM.get_random_number();

    // Create Matrix
    Matrix mat;
    LINALG.make_sensing_matrix(&mat);

    // Print Matrix
    LINALG.print_sensing_matrix(&mat);

    /* Process End */
    PROCESS_END();
}