
#include "contiki.h"
// #include "net/rime/rime.h"
// #include "fixedpoint.h"
// #include "./randomGenerator.h"
// #include "./linalg.h"
// #include "./ec_scheme.h"
// #include <stddef.h>
// #include <stdio.h>

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);
// static void sent_uc(struct unicast_conn *c, int status, int num_tx)
// {
//     const linkaddr_t *dest = packetbuf_addr(PACKETBUF_ADDR_RECEIVER);
//     if (linkaddr_cmp(dest, &linkaddr_null))
//     {
//         return;
//     }
//     printf("unicast message sent to %d.%d: status %d num_tx %d\n",
//            dest->u8[0], dest->u8[1], status, num_tx);
// }

// static const struct unicast_callbacks unicast_callbacks = {sent_uc};
// static struct unicast_conn uc;

PROCESS_THREAD(comp_sensing, ev, data)
{
    // PROCESS_EXITHANDLER(unicast_close(&uc);)
    /* Declare variables required */
    PROCESS_BEGIN();
    // const int16_t data[51] = {0, 103, 197, 278, 337, 372, 380, 363, 325, 271, 207, 141, 81, 33,
    //                           4, -4, 12, 48, 103, 170, 243, 313, 374, 418, 440, 437, 406, 350,
    //                           273, 180, 79, -24, -118, -199, -259, -296, -306, -293, -258, -209, -150, -90,
    //                           -36, 5, 27, 28, 5, -38, -101, -175, 0};

    const uint32_t vec[100] = {1923, 1923, 1925, 1929, 1931, 1929, 1925, 1929, 1931, 1933, 1931, 1929, 1933, 1931,
                         1939, 1939, 1939, 1939, 1939, 1935, 1933, 1937, 1939, 1941, 1945, 1953, 1966, 1982,
                         2017, 2060, 2119, 2193, 2277, 2361, 2441, 2508, 2537, 2529, 2459, 2344, 2181, 1992,
                         1796, 1628, 1513, 1474, 1509, 1579, 1667, 1757, 1822, 1869, 1904, 1921, 1927, 1929,
                         1925, 1925, 1921, 1927, 1933, 1943, 1945, 1949, 1949, 1951, 1949, 1947, 1947, 1951,
                         1953, 1961, 1972, 1980, 1982, 1990, 1984, 1986, 1982, 1982, 1980, 1982, 1982, 1982,
                         1986, 1986, 1984, 1982, 1980, 1980, 1978, 1978, 1974, 1978, 1976, 1982, 1984, 1986,
                         1986, 0};
    const uint32_t vec1[100] = {1923, 1923, 1925, 1929, 1931, 1929, 1925, 1929, 1931, 1933, 1931, 1929, 1933, 1931,
                         1939, 1939, 1939, 1939, 1939, 1935, 1933, 1937, 1939, 1941, 1945, 1953, 1966, 1982,
                         2017, 2060, 2119, 2193, 2277, 2361, 2441, 2508, 2537, 2529, 2459, 2344, 2181, 1992,
                         1796, 1628, 1513, 1474, 1509, 1579, 1667, 1757, 1822, 1869, 1904, 1921, 1927, 1929,
                         1925, 1925, 1921, 1927, 1933, 1943, 1945, 1949, 1949, 1951, 1949, 1947, 1947, 1951,
                         1953, 1961, 1972, 1980, 1982, 1990, 1984, 1986, 1982, 1982, 1980, 1982, 1982, 1982,
                         1986, 1986, 1984, 1982, 1980, 1980, 1978, 1978, 1974, 1978, 1976, 1982, 1984, 1986,
                         1986, 0};

    // Predefine return vector, and data vector :
    // Vector_M ret;
    // Vector vec;

    // int i;
    // for (i = 0; i < N; i++)
    // {
    //     vec.data[i].full = data[i];
    //     printf("%.2f\t", FP.fixed_to_float(vec.data[i]));
    //     // vec.data[i].part.integer = data[i];
    //     // vec.data[i].part.fraction = 0;
    // }

    // FIXED11_21 a

    // for (i = 0; i < 64; i++)
    // {
    //     // RANDOM.get_random_number();
    //     printf("%d\t",RANDOM.get_random_number());
    // }

    // printf("\n");

    // LINALG.print_vector(&vec);

    // LINALG.inner_product(&mat,&vec,&ret);

    // LINALG.print_vector(&ret);

    // FIXED11_21 a, b;
    int a = 0;
    while (1)
    {
        // printf("%d\t",a);
        a = 1;
    }

    // b.full = 144787;
    // EC.ec_transform(&vec, &ret);
    // unicast_open(&uc, 146, &unicast_callbacks);

    // // char a[3] = "";
    // while (1)
    // {
    //     static struct etimer et;
    //     linkaddr_t addr;

    //     etimer_set(&et, CLOCK_SECOND);

    //     PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    //     packetbuf_copyfrom("ab", 2);
    //     //KASPER IS 12
    //     addr.u8[0] = 221;
    //     addr.u8[1] = 159;
    //     printf("Sending_data");
    //     if (!linkaddr_cmp(&addr, &linkaddr_node_addr))
    //     {
    //         unicast_send(&uc, &addr);
    //     }
    // }

    // printf("MyFixed: %2f\n", FP.fixed_to_float(b));
    // a = FP.float_to_fixed(30.0);

    // printf("%.2f\n",FP.fixed_to_float(FP.fp_sqrt(a,20)));
    // printf("\n\n");
    // EC.pprint(&ret);

    // FIXED11_21 a,b,c;

    // a = FP.float_to_fixed(500.0);
    // printf("%.2f",FP.fixed_to_float(FP.fp_pow(a,2)));

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