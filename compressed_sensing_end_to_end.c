
#include "contiki.h"
#include "./cs_config.h"
#include "./ec_scheme.h"
#include <stdio.h>
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

// Max size of 802.15.4 MAC when all address information is used
#define TX_BUFFER_SIZE 102

static uint16_t i = 0;
static uint8_t signal_bytes[BLOCK_LEN] = {0};

static int16_t signal[N_CS] = {  948, 948, 948, 948, 948, 948, 948, 948, 951, 951, 954, 951, 951, 952,
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

// static linkaddr_t receiver = {{0x30, 0xa3, 0x45, 0x1a, 0x00, 0x74, 0x12, 0x00}};

static void send_packets() {
  static uint8_t buf[TX_BUFFER_SIZE] = {0};
  nullnet_buf = buf;
  #if DEBUG
  LOG_INFO("Sending to receiver mote\n");
  #endif
  for (i = 0; i < CEIL_DIVIDE(BLOCK_LEN,TX_BUFFER_SIZE); i++) {
    memset(buf, 0, TX_BUFFER_SIZE);
    memcpy(buf, signal_bytes + (i * TX_BUFFER_SIZE), i == (BLOCK_LEN / TX_BUFFER_SIZE) ? BLOCK_LEN % TX_BUFFER_SIZE : TX_BUFFER_SIZE);
    nullnet_len = i == (BLOCK_LEN / TX_BUFFER_SIZE) ? BLOCK_LEN % TX_BUFFER_SIZE : TX_BUFFER_SIZE;
    NETSTACK_NETWORK.output(NULL);
  }
  NETSTACK_RADIO.off();
}

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{
    PROCESS_BEGIN();

    // Turn radio off while processing data 
    NETSTACK_RADIO.off();

    #if DEBUG
    printf("Clock system time before Encryption: %u \n",(unsigned int)clock_time());
    #endif

    // ---------------------- TEST CODE -------------------------------------
    // The signal needs to be scaled for big block sizes to prevent overflows
    for (i = 0; i < N_CS; i++) {
      signal[i] >>= 2;
    }
    ec_transform_blockwise(signal);
    // ----------------------------------------------------------------------

    #if DEBUG
    printf("Clock system time after Encryption: %u \n",(unsigned int)clock_time());
    #endif

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

    NETSTACK_RADIO.on();
    send_packets();    

    PROCESS_END();
}