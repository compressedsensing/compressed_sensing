TARGET_LIBFILES += -lm
CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"
CONTIKI = ../..

MAKE_NET = MAKE_NET_NULLNET

CONTIKI_PROJECT = compressed_sensing
all: $(CONTIKI_PROJECT)

PROJECT_SOURCEFILES += fixedpoint.c ec_scheme.c

include $(CONTIKI)/Makefile.include