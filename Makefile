TARGET_LIBFILES += -lm
CONTIKI = ../..

CONTIKI_PROJECT = compressed_sensing
all: $(CONTIKI_PROJECT)

PROJECT_SOURCEFILES += randomGenerator.c linalg.c fixedpoint.c ec_scheme.c
UIP_CONF_IPV6=1

#CONTIKI_WITH_RIME = 1
include $(CONTIKI)/Makefile.include