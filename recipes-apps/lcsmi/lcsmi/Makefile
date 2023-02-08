MAKE_DIR = $(PWD)

APP = app
PICOUSBLIB = picousblib
UDPMRLIB = udputilslib
LCDCLILIB = lcdclilib
UTILDBGLIB = utildbglib
JTIMERLIB = jtimerlib
CABINETUTILSLIB = cabinetutilslib
#GPIOLIB = gpiolib
#TCPSERVERLIB = tcpserverlib
#UDPSOCKETLIB = udpsocketlib

APP_DIR := $(MAKE_DIR)/$(APP)
COMPAT_DIR := $(MAKE_DIR)/
PICOUSBLIB_DIR := $(MAKE_DIR)/$(PICOUSBLIB)
UDPMRLIB_DIR := $(MAKE_DIR)/$(UDPMRLIB)
LCDCLILIB_DIR := $(MAKE_DIR)/$(LCDCLILIB)
UTILDBGLIB_DIR := $(MAKE_DIR)/$(UTILDBGLIB)
JTIMERLIB_DIR := $(MAKE_DIR)/$(JTIMERLIB)
CABINETUTILSLIB_DIR := $(MAKE_DIR)/$(CABINETUTILSLIB)
#GPIOLIB_DIR := $(MAKE_DIR)/$(GPIOLIB)
#TCPSERVERLIB_DIR := $(MAKE_DIR)/$(TCPSERVERLIB)
#UDPSOCKETLIB_DIR := $(MAKE_DIR)/$(UDPSOCKETLIB)

INC_SRCH_PATH := -I$(MAKE_DIR)
INC_SRCH_PATH += -I$(MAKE_DIR)/recipe-sysroot/usr/include/SDL2/
INC_SRCH_PATH += -I$(MAKE_DIR)/recipe-sysroot/usr/include/libusb-1.0/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libavcodec/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libavdevice/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libavfilter/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libavformat/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libavutil/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libavresample/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libavpostproc/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libswresample/
INC_SRCH_PATH += -I$(MAKE_DIR)/include/libswscale/
INC_SRCH_PATH += -I$(COMPAT_DIR)
INC_SRCH_PATH += -I$(PICOUSBLIB_DIR)
INC_SRCH_PATH += -I$(UDPMRLIB_DIR)
INC_SRCH_PATH += -I$(LCDCLILIB_DIR)
INC_SRCH_PATH += -I$(UTILDBGLIB_DIR)
INC_SRCH_PATH += -I$(JTIMERLIB_DIR)
INC_SRCH_PATH += -I$(CABINETUTILSLIB_DIR)
#INC_SRCH_PATH += -I$(TCPSERVERLIB_DIR)
#INC_SRCH_PATH += -I$(UDPSOCKETLIB_DIR)

LIB_SRCH_PATH := -L$(MAKE_DIR)
LIB_SRCH_PATH += -L$(MAKE_DIR)/libs/

CFLAGS :=
CFLAGS += $(INC_SRCH_PATH) $(LIB_SRCH_PATH)
CFLAGS += -DDEBUG -D_REENTRANT
CFLAGS += -Wall 
CFLAGS += -D_GNU_SOURCE 

LDFLAGS :=
LDFLAGS += -lcabinetutils
LDFLAGS += -lpicousb
LDFLAGS += -ludputils
LDFLAGS += -llcdcli
LDFLAGS += -ljtimer
#LDFLAGS += -lgpio 
#LDFLAGS += -ltcpserver 
#LDFLAGS += -ludpsocket 
LDFLAGS += -lavdevice -lavfilter -lavresample -lpostproc -lswscale -lavformat -lavcodec -lswresample -lavutil -lpthread -lm -lrt -lSDL2 -lusb-1.0
LDFLAGS += -lutildbg

export MAKE_DIR CFLAGS LDFLAGS LIBS INC_SRCH_PATH LIB_SRCH_PATH

all: 
	echo $(CFLAGS)
	$(MAKE) -C $(CABINETUTILSLIB_DIR) -f $(CABINETUTILSLIB).mk
	$(MAKE) -C $(PICOUSBLIB_DIR) -f $(PICOUSBLIB).mk
	$(MAKE) -C $(UDPMRLIB_DIR) -f $(UDPMRLIB).mk
	$(MAKE) -C $(LCDCLILIB_DIR) -f $(LCDCLILIB).mk
	$(MAKE) -C $(UTILDBGLIB_DIR) -f $(UTILDBGLIB).mk
	$(MAKE) -C $(JTIMERLIB_DIR) -f $(JTIMERLIB).mk
#	$(MAKE) -C $(GPIOLIB_DIR) -f $(GPIOLIB).mk
#	$(MAKE) -C $(TCPSERVERLIB_DIR) -f $(TCPSERVERLIB).mk
#	$(MAKE) -C $(UDPSOCKETLIB_DIR) -f $(UDPSOCKETLIB).mk
	$(MAKE) -C $(APP_DIR) -f $(APP).mk
	
.PHONY: clean
clean:
	$(MAKE) -C $(PICOUSBLIB_DIR) -f $(PICOUSBLIB).mk clean
	$(MAKE) -C $(UDPMRLIB_DIR) -f $(UDPMRLIB).mk clean
	$(MAKE) -C $(UTILDBGLIB_DIR) -f $(UTILDBGLIB).mk clean
	$(MAKE) -C $(LCDCLILIB_DIR) -f $(LCDCLILIB).mk clean
	$(MAKE) -C $(JTIMERLIB_DIR) -f $(JTIMERLIB).mk clean
	$(MAKE) -C $(CABINETUTILSLIB_DIR) -f $(CABINETUTILSLIB).mk clean
#	$(MAKE) -C $(GPIOLIB_DIR) -f $(GPIOLIB).mk clean
#	$(MAKE) -C $(TCPSERVERLIB_DIR) -f $(TCPSERVERLIB).mk clean
#	$(MAKE) -C $(UDPSOCKETLIB_DIR) -f $(UDPSOCKETLIB).mk clean
	$(MAKE) -C $(APP_DIR) -f $(APP).mk clean
