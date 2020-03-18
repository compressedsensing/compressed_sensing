
#include "contiki.h"
// #include "net/rime/rime.h"
#include "fixedpoint.h"
#include "./randomGenerator.h"
#include "./linalg.h"
#include "./ec_scheme.h"
// #include <stddef.h>
#include <stdio.h>
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"

// #include "cc2420.h"

#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
#define SEND_INTERVAL (10 * CLOCK_SECOND)

// static struct simple_udp_connection udp_conn;
// static struct ctimer timer;
// static Vector_M ret;
// static Vector vec;
// static uint16_t i = 0;
// static uint8_t signal_bytes[M * 2] = {0};
// static uip_ipaddr_t dest_ipaddr = {{0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x12, 0x74, 0x00, 0x1a, 0x45, 0xa3, 0x30}};

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

// static void
// callback(void *ptr)
// {
//     LOG_INFO("Starting transmission loop\n");
//     LOG_INFO("Timer expired, check if receiver is reachable\n");
//     // if (NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr)) {
//     /* Send to DAG root */
//     uint8_t buf[128] = {0};
//     LOG_INFO("Sending to receiver mote\n");

//     // Fixed point to bytes
//     for (i = 0; i < M * 2; i += 2)
//     {
//         signal_bytes[i + 0] = (uint8_t)((ret.data[i >> 1] & 0xFF00) >> 8);
//         signal_bytes[i + 1] = (uint8_t)((ret.data[i >> 1] & 0x00FF) >> 0);
//     }

//     for (i = 0; i <= 2 * M / 128; i++)
//     {
//         memset(buf, 0, 128);
//         memcpy(buf, signal_bytes + (i * 128), i == 2 * M / 128 ? 2 * M % 128 : 128);
//         simple_udp_sendto(&udp_conn, buf, i == 2 * M / 128 ? 2 * M % 128 : 128, &dest_ipaddr);
//     }
//     // } else {
//     //   LOG_INFO("Not reachable yet\n");
//     // }
//     ctimer_reset(&timer);
// }

PROCESS_THREAD(comp_sensing, ev, data)
{
    // PROCESS_EXITHANDLER(unicast_close(&uc);)
    /* Declare variables required */
    // static int16_t signal_bytes[M] = {0};
    // static const int16_t sensor_data[N_CS] = {0, 242, 242, 242, 242, 242, 242, 242, 242, 243, 243, 244, 243, 243, 243, 244, 245, 246, 246,
    //                                           246, 246, 245, 244, 244, 244, 243, 243, 242, 241, 242, 242, 241, 241, 240, 240, 239, 239,
    //                                           238, 238, 238, 239, 240, 240, 240, 241, 241, 241, 240, 241, 241, 241, 241, 241, 241, 241,
    //                                           242, 242, 242, 242, 242, 241, 241, 242, 242, 242, 243, 244, 245, 247, 252, 257, 264, 274,
    //                                           284, 295, 305, 313, 317, 316, 307, 293, 272, 249, 224, 203, 189, 184, 188, 197, 208, 219,
    //                                           227, 233, 238, 240, 240, 241, 240, 240, 240, 240, 241, 242, 243, 243, 243, 243, 243, 243,
    //                                           243, 243, 244, 245, 246, 247, 247, 248, 248, 248, 247, 247, 247, 247, 247, 247, 248, 248,
    //                                           248, 247, 247, 247, 247, 247, 246, 247, 247, 247, 248, 248, 248, 248, 249, 249, 249, 250,
    //                                           250, 251, 252, 253, 254, 256, 257, 258, 259, 259, 260, 260, 261, 261, 262, 262, 263, 264,
    //                                           264, 265, 264, 264, 263, 263, 262, 263, 262, 261, 261, 260, 259, 258, 257, 255, 254, 252,
    //                                           251, 250, 249, 249, 248, 247, 247, 246, 245, 245, 244, 243, 242, 242, 242, 241, 241, 242,
    //                                           242, 242, 241, 241, 241, 241, 240, 240, 240, 241, 241, 242, 242, 242, 242, 242, 242, 241,
    //                                           242, 242, 242, 243, 242, 243, 243, 243, 244, 243, 242, 242, 243, 242, 243, 243, 243, 243,
    //                                           243, 243, 242, 242, 242, 242, 242, 241, 241, 241, 241, 241, 241, 242, 241, 240, 240, 240,
    //                                           239, 238, 239};
//     static Vector vec = {{0,469,469,470,471,471,471,470,471,471,472,471,471,472,471,473,473,473,473,
//  473,472,472,473,473,474,475,477,480,484,492,503,517,535,556,576,596,612,
//  619,617,600,572,532,486,438,397,369,360,368,385,407,429,445,456,465,469,
//  470,471,470,470,469,470,472,474,475,476,476,476,476,475,475,476,477,479,
//  481,483,484,486,484,485,484,484,483,484,484,484,485,485,484,484,483,483,
//  483,483,482,483,482,484,484,485,485,485,487,487,487,489,490,491,494,496,
//  498,500,502,505,506,506,508,509,510,511,512,513,515,517,517,518,517,516,
//  514,514,513,514,513,511,511,509,507,504,502,499,497,493,492,489,488,486,
//  485,484,483,481,479,479,477,475,473,473,473,472,472,473,473,473,472,472,
//  472,471,470,469,470,471,472,473,474,474,474,473,473,472,473,473,474,475,
//  474,475,476,475,477,475,474,474,475,474,475,475,476,475,475,475,474,474,
//  474,473,473,472,472,472,472,472,472,473,471,470,469,469,467,466,468,469,
//  469,470,470,470,469,468,467,466,466,466,466,467,467,466,467,467,466,465,
//  467,467,467,467,469,470,471,473,473,475,475,476,477,477,476,476,475,474,
//  472,472,473,472,472,470,469,467,465,464,463,463,463,463,462,461,458,458,
//  457,457,457,456,459,460,461,463,462,462,461,460,459,458,458,458,459,460,
//  460,462,462,462,461,461,461,461,460,460,462,464,467,473,482,496,510,531,
//  552,574,595,612,623,624,612,586,547,499,448,398,361,342,343,360,384,410,
//  432,452,462,470,472,472,472,470,469,468,470,473,474,476,477,478,479,479,
//  480,483,483,485,488,489,491,493,494,496,498,498,498,498,498,498,498,499,
//  499,500,501,501,501,501,500,500,501,502,504,505,508,509,511,513,513,514,
//  515,516,517,520,522,524,525,527,528,528,527,528,529,529,528,529,530,529,
//  529,530,530,530,530,528,527,526,525,524,523,520,520,516,516,515,511,507,
//  504,500,497,494,492,491,490,489,488,486,483,481,478,476,475,474,474,474,
//  474,473,473,473,473,471,470,471,470,470,471,470,470,472,473,472,472,470,
//  471,470,470,471,471,471,473,473,474,476,476,475,474,474,474,473,474,475,
//  475,476,476,476,474,474,473,471,470,469,470,469,470,470,469,468,468,465,
//  465,464,465,465,466,464,465,465,466,465,465,465,466,465,466,467,467,469,
//  473,474,477,478,479,480,481}};

    // static const int16_t somedata[51] = {0, 103, 197, 278, 337, 372, 380, 363, 325, 271, 207, 141, 81, 33,
    //                                  4, -4, 12, 48, 103, 170, 243, 313, 374, 418, 440, 437, 406, 350,
    //                                  273, 180, 79, -24, -118, -199, -259, -296, -306, -293, -258, -209, -150, -90,
    //                                  -36, 5, 27, 28, 5, -38, -101, -175, 0};
    PROCESS_BEGIN();

    NETSTACK_RADIO.off();

    printf("Here First\n");

    uint16_t i,j;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N_CS; j++)
        {        
        RANDOM.get_random_number();
        }
        // printf("%d,", RANDOM.get_random_number());
    }
    printf("Here");

    // static struct etimer periodic_timer;
    // uip_ipaddr_t dest_ipaddr;
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

    // static uint8_t mybool = 1;

    // int i;
    // for (i = 0; i < N_CS; i++)
    // {
    //     vec.data[i] = sensor_data[i];
    //     // printf("%.2f\t", FP.fixed_to_float16(vec.data[i]));
    //     // vec.data[i].part.integer = data[i];
    //     // vec.data[i].part.fraction = 0;
    // }

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
    // etimer_set(&periodic_timer, 5 * CLOCK_SECOND);
    // PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

    // LOG_INFO_("hello\n");

    // LOG_INFO_("hello\n");
    // etimer_set(&periodic_timer, 5 * CLOCK_SECOND);
    // PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

    /* Test code */
//     EC.ec_transform(&vec, &ret);

// #if DEBUG
//     EC.pprint(&ret);
// #endif

    //     /* Transmission code */
    //     simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL,
    //                         UDP_SERVER_PORT, NULL);

    //     for (i = 0; i < M * 2; i += 2)
    //     {
    //         signal_bytes[i + 0] = (uint8_t)((ret.data[i >> 1] & 0xFF00) >> 8);
    //         signal_bytes[i + 1] = (uint8_t)((ret.data[i >> 1] & 0x00FF) >> 0);
    //     }

    //     NETSTACK_RADIO.on();
    //     uint8_t buf[128] = {0};
    // #if DEBUG
    //     LOG_INFO("Sending to receiver mote\n");
    // #endif
    //     for (i = 0; i <= 2*M / 128; i++)
    //     {
    //         memset(buf, 0, 128);
    //         memcpy(buf, signal_bytes + (i * 128), i == 2*M / 128 ? 2*M % 128 : 128);
    //         simple_udp_sendto(&udp_conn, buf, i == 2*M / 128 ? 2*M % 128 : 128, &dest_ipaddr);
    //     }
    //     NETSTACK_RADIO.off();

    // ctimer_set(&timer, 5 * CLOCK_SECOND, callback, NULL);

    // etimer_set(&periodic_timer, SEND_INTERVAL);
    // while (1)
    // {
    //     PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    //     LOG_INFO("Radio on!\n");
    //     NETSTACK_RADIO.on();

    //     // if (mybool)
    //     // {
    //     //     EC.ec_transform(&vec, &ret);
    //     //     EC.pprint(&ret);

    //     //     for (i = 0; i < M; i++)
    //     //     {
    //     //         signal_bytes[i] = ret.data[i];
    //     //     }

    //     //     mybool = 0;
    //     // }

    //     if (NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr))
    //     {
    //         /* Send to DAG root */
    //         LOG_INFO("Sending!\n");
    //         simple_udp_sendto(&udp_conn, signal_bytes, M * 2, &dest_ipaddr);

    //         LOG_INFO("Shuting off radio!\n");
    //         NETSTACK_RADIO.off();
    //         // mybool = 1;
    //         // etimer_set(&periodic_timer, SEND_INTERVAL);
    //     }
    //     else
    //     {
    //         LOG_INFO("Not reachable yet\n");
    //     }

    //     etimer_reset(&periodic_timer);
    //     /* Add some jitter */
    //     // EC.ec_transform(&vec, &ret);

    //     // etimer_set(&periodic_timer, 4* CLOCK_SECOND);
    //     // PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    // }

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