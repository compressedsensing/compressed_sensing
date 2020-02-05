
#include "contiki.h"
#include "./randomGenerator.h"
#include "./linalg.h"
#include "fixedpoint.h"

#include <stddef.h>
#include <stdio.h>

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{
    /* Declare variables required */
    PROCESS_BEGIN();

    // Create Matrix
    Matrix mat;
    LINALG.make_sensing_matrix(&mat);

    // Print Matrix
    LINALG.print_sensing_matrix(&mat);

    Vector ret;

    Vector vec = {FP.float_to_fixed(0.8), FP.float_to_fixed(0.6), FP.float_to_fixed(0.4)};

    LINALG.print_vector(&vec);

    LINALG.inner_product(&mat,&vec,&ret);

    LINALG.print_vector(&ret);

    /* Process End */
    PROCESS_END();
}