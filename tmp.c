
#include "contiki.h"
// #include "DCT.h"
#include "math.h"
#include <stddef.h>
// #include <stdio.h> /* For printf() */

PROCESS(comp_sensing, "My_First_App");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{
    /* Declare variables required */
    PROCESS_BEGIN();

    /* LFSR register */
    char init_seed = 0b11001100;

    char xor = (init_seed & 0b01001010);
    char sum = 0x00;

    size_t i;

    unsigned int n;
    for (n = 0; xor ; n++)
    {
        xor &= xor-1;
    }
    switch (n%2)
    {
    case 0:
        printf("0");
        break;
    case 1:
        printf("1");
        break;    
    default:
        break;
    }

    printf("%d\n", n);

    /* Process End */
    PROCESS_END();
}


    // unsigned char in_s, cs, cp, p, nbit, s[STREAM];
    // int i, j, k = 0;

    // in_s = 0xb4; /* this can be any 8 bit value */
    // p = 0x71;    /* max length polynomial x^8+x^4+x^3+x^2+1 = 0b01110001 */

    // cs = in_s; /* copy initial state */

    // printf("\nByte values for lfsr with initial value of 0xb4, and bit mask 0x71.\n");
    // printf("Should correspond to primitive polynomial x^8+x^4+x^3+x^2+1.\n");

    // while (k < STREAM)
    // {
    //     for (j = 0; j < 8; j++, k++)
    //     {
    //         cp = nbit = cs & p;

    //         for (i = 1; i < 8; i++)
    //         { /* xor all bits together */
    //             nbit ^= (cp >> i);
    //         }
    //         s[k] = cs & 0x01;
    //         cs = (cs >> 1) | (nbit << 7); /*  rotate in new bit */
    //     }
    //     printf(" %02x ", cs);
    //     if (cs == in_s)
    //     {
    //         printf("\nreached duplicate at %d.\n", k);
    //     }
    // }