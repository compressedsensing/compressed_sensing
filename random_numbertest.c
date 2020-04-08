#include "contiki.h"
#include "fixedpoint.h"
#include "./randomGenerator.h"
#include "./linalg.h"
#include "./ec_scheme.h"
#include <stdio.h>
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"

// #include "cc2420.h"

#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
#define SEND_INTERVAL (10 * CLOCK_SECOND)

// static struct simple_udp_connection udp_conn;
static struct ctimer timer;

static uint8_t signal_bytes[M * 2] = {0};
static uip_ipaddr_t dest_ipaddr = {{0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x12, 0x74, 0x00, 0x1a, 0x45, 0xa3, 0x30}};

static void
callback(void *prt)
{
    /* Det er vel bare det her ? */
    int16_t i, j;
    for (i = 0; i < M; i++)
    {
        // Prevent watchdog from restarting during this operation
        watchdog_periodic();
        for (j = 0; j < N_CS; j++)
        {
            RANDOM.get_random_number();
        }
    }
}

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{

    /* Declare variables required */

    static int16_t vec[N_CS] = {  0, 995, 995, 995, 995, 995, 995, 995,1000, 997, 995, 994, 992, 993,
  992, 989, 988, 987, 990, 993, 989, 988, 986, 988, 993, 997, 993, 986,
  983, 977, 979, 975, 974, 972, 969, 969, 969, 971, 973, 971, 969, 966,
  966, 966, 966, 967, 965, 963, 967, 969, 969, 968, 967, 963, 966, 964,
  968, 966, 964, 961, 960, 957, 952, 947, 947, 943, 933, 927, 927, 939,
  958, 980,1010,1048,1099,1148,1180,1192,1177,1128,1058, 991, 951, 937,
  939, 950, 958, 959, 957, 955, 958, 959, 961, 962, 960, 957, 956, 959,
  955, 957, 958, 957, 958, 959, 958, 958, 955, 953, 957, 959, 963, 960,
  960, 958, 956, 957, 956, 955, 953, 953, 956, 958, 958, 958, 956, 954,
  959, 959 };

    PROCESS_BEGIN();

    /* Turn radio off */
    NETSTACK_RADIO.off();

    /* Draw random numbers (N*M) */

    ctimer_set(&timer, 2 * CLOCK_SECOND, callback, NULL);

    PROCESS_END();
}