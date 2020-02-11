
#include "contiki.h"
#include "fixedpoint.h"
#include "./randomGenerator.h"
#include "./linalg.h"
#include "./ec_scheme.h"
#include <stddef.h>
// #include <stdio.h>

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{
    /* Declare variables required */
    PROCESS_BEGIN();
    const int16_t data[51] = {0, 103, 197, 278, 337, 372, 380, 363, 325, 271, 207, 141, 81, 33,
                              4, -4, 12, 48, 103, 170, 243, 313, 374, 418, 440, 437, 406, 350,
                              273, 180, 79, -24, -118, -199, -259, -296, -306, -293, -258, -209, -150, -90,
                              -36, 5, 27, 28, 5, -38, -101, -175, 0};

    // Create Matrix
    // Matrix mat;
    // LINALG.make_sensing_matrix(&mat);

    // Print Matrix
    // LINALG.print_sensing_matrix(&mat);

    Vector_M ret;
    // // Vector vec = {FP.float_to_fixed(5.3), FP.float_to_fixed(9.2), FP.float_to_fixed(4.4)};
    Vector vec;

    int i;
    for (i = 0; i < N; i++)
    {
        vec.data[i].part.integer = data[i];
        vec.data[i].part.fraction = 0;
    }

    // for (i = 0; i < 64; i++)
    // {
    //     // RANDOM.get_random_number();
    //     printf("%d\t",RANDOM.get_random_number());
    // }

    // printf("\n");

    // LINALG.print_vector(&vec);

    // LINALG.inner_product(&mat,&vec,&ret);

    // LINALG.print_vector(&ret);

    // FIXED11_21 a;

    // a = FP.float_to_fixed(30.0);

    // printf("%.2f\n",FP.fixed_to_float(FP.fp_sqrt(a,20)));

    EC.ec_transform(&vec, &ret);
    printf("\n\n");
    EC.pprint(&ret);

    // for (i = 0; i < 6; i++)
    // {
    //     printf("%d\t", RANDOM.get_random_number());
    //     /* code */
    // }

    // printf("\n");

    /* Process End */
    // printf("helle!");
    PROCESS_END();
}