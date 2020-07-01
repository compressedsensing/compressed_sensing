
#include "contiki.h"
#include "./cs_config.h"
#include "./ec_scheme.h"
#include <stdio.h>
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"

#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
#define SEND_INTERVAL (10 * CLOCK_SECOND)

static struct simple_udp_connection udp_conn;
// static struct ctimer timer;
int16_t i;

static uint8_t signal_bytes[BLOCK_LEN] = {0};
static uip_ipaddr_t dest_ipaddr = {{0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x12, 0x74, 0x00, 0x1a, 0x45, 0xc9, 0x58}};


static void send_packets() {
  NETSTACK_RADIO.on();
  static uint8_t buf[128] = {0};
  // uint16_t j = 0;
  #if DEBUG
  LOG_INFO("Sending to receiver mote\n");
  #endif
  for (i = 0; i <= (BLOCK_LEN / 128); i++) {
    // LOG_INFO("%d\n", i == (BLOCK_LEN / 128) ? BLOCK_LEN % 128 : 128);
    // LOG_INFO("%d\n", (i * 128));
    memset(buf, 0, 128);
    memcpy(buf, signal_bytes + (i * 128), i == (BLOCK_LEN / 128) ? BLOCK_LEN % 128 : 128);
    simple_udp_sendto(&udp_conn, buf, i == (BLOCK_LEN / 128) ? BLOCK_LEN % 128 : 128, &dest_ipaddr);
  }
  NETSTACK_RADIO.off();
}

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{

    /* Declare variables required */
static int16_t signal[N_CS] = {  0, 948, 948, 948, 948, 948, 948, 948, 951, 951, 954, 951, 951, 952,
  957, 959, 961, 962, 963, 962, 958, 955, 956, 954, 951, 952, 948, 945,
  946, 947, 945, 943, 940, 939, 936, 936, 933, 933, 933, 935, 939, 939,
  940, 942, 943, 942, 940, 942, 943, 944, 943, 942, 944, 943, 947, 947,
  947, 947, 947, 945, 944, 946, 947, 948, 950, 954, 960, 968, 985,1006,
 1035,1071,1112,1153,1192,1225,1239,1235,1201,1145,1065, 973, 877, 795,
  739, 720, 737, 771, 814, 858, 890, 913, 930, 938, 941, 942, 940, 940,
  938, 941, 944, 949, 950, 952, 952, 953, 952, 951, 951, 953, 954, 958,
  963, 967, 968, 972, 969, 970, 968, 968, 967, 968, 968, 968, 970, 970,
  969, 968, 967, 967, 966, 966, 964, 966, 965, 968, 969, 970, 970, 970,
  974, 974, 975, 979, 980, 982, 988, 992, 996,1000,1005,1010,1012,1012,
 1016,1019,1020,1023,1025,1027,1030,1034,1035,1036,1034,1032,1028,1029,
 1027,1029,1026,1023,1022,1019,1015,1009,1004, 999, 995, 987, 984, 979,
  976, 973, 971, 968, 966, 963, 959, 958, 954, 950, 947, 946, 947, 945,
  945, 946, 946, 946, 945, 944, 944, 942, 941, 939, 941, 942, 944, 946,
  948, 948, 949, 946, 947, 945, 946, 946, 948, 951, 948, 950, 952, 951,
  954, 951, 949, 949, 950, 949, 951, 951, 952, 951, 950, 950, 949, 949,
  949, 946, 946, 945, 945, 945, 945, 945, 945, 946, 943, 941, 938, 938,
  934, 933, 937, 938 };

    PROCESS_BEGIN();

    /* Turn radio off */
    NETSTACK_RADIO.off();

    /* Test code */
    printf("Clock system time before Encryption: %u \n",(unsigned int)clock_time());
    EC.ec_transform(signal);
    printf("Clock system time after Encryption: %u \n",(unsigned int)clock_time());

    /* Transmission code */
    simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL,
                        UDP_SERVER_PORT, NULL);

    for (i = 0; i < BLOCK_LEN; i += 2)
    {
        signal_bytes[i + 0] = (uint8_t)((signal[i >> 1] & 0xFF00) >> 8);
        signal_bytes[i + 1] = (uint8_t)((signal[i >> 1] & 0x00FF) >> 0);
    }

    #if DEBUG
    LOG_INFO_("Byte data\n");
    for (i = 0; i < BLOCK_LEN; i++)
    {
      LOG_INFO_("%02x", signal_bytes[i]);
    }
    LOG_INFO_("\n");
    #endif

    send_packets();

    PROCESS_END();
}