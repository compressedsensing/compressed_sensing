
#include "contiki.h"
// #include "net/rime/rime.h"
#include "fixedpoint.h"
#include "./randomGenerator.h"
#include "./linalg.h"
#include "./ec_scheme.h"
// #include <stddef.h>
// #include <stdio.h>
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "cc2420.h"

#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
#define SEND_INTERVAL (10 * CLOCK_SECOND)

static struct simple_udp_connection udp_conn;

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

// static void
// udp_rx_callback(struct simple_udp_connection *c,
//                 const uip_ipaddr_t *sender_addr,
//                 uint16_t sender_port,
//                 const uip_ipaddr_t *receiver_addr,
//                 uint16_t receiver_port,
//                 const uint8_t *data,
//                 uint16_t datalen)
// {
//     uint16_t i;
//     for (i = 0; i < datalen; i++)
//     {
//         LOG_INFO_("%02x", data[i]);
//     }
//     LOG_INFO_("\n");
// }


PROCESS_THREAD(comp_sensing, ev, data)
{
    // PROCESS_EXITHANDLER(unicast_close(&uc);)
    /* Declare variables required */
    static int16_t signal_bytes[M] = {0};
    static const int16_t sensor_data[N_CS] = {0, 242, 242, 242, 242, 242, 242, 242, 242, 243, 243, 244, 243, 243, 243, 244, 245, 246, 246,
                                              246, 246, 245, 244, 244, 244, 243, 243, 242, 241, 242, 242, 241, 241, 240, 240, 239, 239,
                                              238, 238, 238, 239, 240, 240, 240, 241, 241, 241, 240, 241, 241, 241, 241, 241, 241, 241,
                                              242, 242, 242, 242, 242, 241, 241, 242, 242, 242, 243, 244, 245, 247, 252, 257, 264, 274,
                                              284, 295, 305, 313, 317, 316, 307, 293, 272, 249, 224, 203, 189, 184, 188, 197, 208, 219,
                                              227, 233, 238, 240, 240, 241, 240, 240, 240, 240, 241, 242, 243, 243, 243, 243, 243, 243,
                                              243, 243, 244, 245, 246, 247, 247, 248, 248, 248, 247, 247, 247, 247, 247, 247, 248, 248,
                                              248};

    // static const int16_t somedata[51] = {0, 103, 197, 278, 337, 372, 380, 363, 325, 271, 207, 141, 81, 33,
    //                                  4, -4, 12, 48, 103, 170, 243, 313, 374, 418, 440, 437, 406, 350,
    //                                  273, 180, 79, -24, -118, -199, -259, -296, -306, -293, -258, -209, -150, -90,
    //                                  -36, 5, 27, 28, 5, -38, -101, -175, 0};
    PROCESS_BEGIN();

    static struct etimer periodic_timer;
    uip_ipaddr_t dest_ipaddr;
    // const uint32_t vec[100] = {1923, 1923, 1925, 1929, 1931, 1929, 1925, 1929, 1931, 1933, 1931, 1929, 1933, 1931,
    //                      1939, 1939, 1939, 1939, 1939, 1935, 1933, 1937, 1939, 1941, 1945, 1953, 1966, 1982,
    //                      2017, 2060, 2119, 2193, 2277, 2361, 2441, 2508, 2537, 2529, 2459, 2344, 2181, 1992,
    //                      1796, 1628, 1513, 1474, 1509, 1579, 1667, 1757, 1822, 1869, 1904, 1921, 1927, 1929,
    //                      1925, 1925, 1921, 1927, 1933, 1943, 1945, 1949, 1949, 1951, 1949, 1947, 1947, 1951,
    //                      1953, 1961, 1972, 1980, 1982, 1990, 1984, 1986, 1982, 1982, 1980, 1982, 1982, 1982,
    //                      1986, 1986, 1984, 1982, 1980, 1980, 1978, 1978, 1974, 1978, 1976, 1982, 1984, 1986,
    //                      1986, 0};

    // const uint32_t vec1[100] = {1923, 1923, 1925, 1929, 1931, 1929, 1925, 1929, 1931, 1933, 1931, 1929, 1933, 1931,
    //                      1939, 1939, 1939, 1939, 1939, 1935, 1933, 1937, 1939, 1941, 1945, 1953, 1966, 1982,
    //                      2017, 2060, 2119, 2193, 2277, 2361, 2441, 2508, 2537, 2529, 2459, 2344, 2181, 1992,
    //                      1796, 1628, 1513, 1474, 1509, 1579, 1667, 1757, 1822, 1869, 1904, 1921, 1927, 1929,
    //                      1925, 1925, 1921, 1927, 1933, 1943, 1945, 1949, 1949, 1951, 1949, 1947, 1947, 1951,
    //                      1953, 1961, 1972, 1980, 1982, 1990, 1984, 1986, 1982, 1982, 1980, 1982, 1982, 1982,
    //                      1986, 1986, 1984, 1982, 1980, 1980, 1978, 1978, 1974, 1978, 1976, 1982, 1984, 1986,
    //                      1986, 0};

    // Predefine return vector, and data vector :
    static Vector_M ret;
    static Vector vec;

    int i;
    for (i = 0; i < N_CS; i++)
    {
        vec.data[i] = sensor_data[i];
        // printf("%.2f\t", FP.fixed_to_float16(vec.data[i]));
        // vec.data[i].part.integer = data[i];
        // vec.data[i].part.fraction = 0;
    }

    // FIXED11_21 a

    // printf("\n");

    // for (i = 0; i < 64; i++)
    // {
    //     RANDOM.get_random_number();
    //     printf("%d\t", RANDOM.get_random_number());
    // }

    // printf("\n");

    // LINALG.print_vector(&vec);

    // LINALG.inner_product(&mat,&vec,&ret);

    // LINALG.print_vector(&ret);

    // FIXED11_21 a, b;
    // int a = 0;
    // while (1)
    // {
    //     // printf("%d\t",a);
    //     a = 1;
    // }

    // b.full = 144787;
   
            EC.ec_transform(&vec, &ret);
#if DEBUG
    EC.pprint(&ret);
#endif

    cc2420_set_txpower(31);

    for (i = 0; i < M; i++)
    {
        signal_bytes[i] = ret.data[i];
    }

    /* Transmission code */
    simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL,
                        UDP_SERVER_PORT, NULL);

    etimer_set(&periodic_timer, SEND_INTERVAL);
    while (1)
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));


        NETSTACK_RADIO.on();
        if (NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr))
        {
            /* Send to DAG root */
            simple_udp_sendto(&udp_conn, signal_bytes, M * 2, &dest_ipaddr);
        }
        else
        {
            LOG_INFO("Not reachable yet\n");
        }
        /* Add some jitter */
        // EC.ec_transform(&vec, &ret);

        etimer_set(&periodic_timer, 4* CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

        etimer_set(&periodic_timer, SEND_INTERVAL);
        NETSTACK_RADIO.off();
    }

    // printf("DONE\n\n");
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

    // int16_t a = 0x0000e0b4;
    // printf("VAR ! %.2f\n",FP.fixed_to_float16(a));
    // printf("VAR ! %.2f\n",FP.fixed_to_float16(0xffffe0b4));
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