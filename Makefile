TARGET_LIBFILES += -lm

CONTIKI_PROJECT = compressed_sensing
all: $(CONTIKI_PROJECT)

PROJECT_SOURCEFILES += randomGenerator.c linalg.c
#UIP_CONF_IPV6=1

CONTIKI = ../..
include $(CONTIKI)/Makefile.include