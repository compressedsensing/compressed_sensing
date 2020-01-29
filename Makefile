TARGET_LIBFILES += -lm

CONTIKI_PROJECT = compressed_sensing
all: $(CONTIKI_PROJECT)

#UIP_CONF_IPV6=1

CONTIKI = ../..
include $(CONTIKI)/Makefile.include